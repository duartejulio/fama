#include "janela.h"
#include "ui_janela.h"

Janela::Janela(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Janela)
{
    ui->setupUi(this);
    corpus = NULL;

    ui->comboBox_corpus->addItem( "CorpusMatriz" );

    ui->tableWidget_atributos->setHorizontalHeaderLabels( QStringList() << "Ordem" << "Nome" );
}

Janela::~Janela()
{
    delete ui;
    if( corpus != NULL ) delete corpus;
}

void Janela::abrirArquivo()
{
    if( s == "" ) s = QFileDialog::getOpenFileName( this, "Abrir","","Documentos de texto (*.txt);;Todos os arquivos (*.*)" );
    if( s != "" )
    {
        string a = s.toStdString();
        stringstream ss, st;
        int n, posBarra;

        corpus->carregarArquivo( a );

        if( (unsigned)( posBarra = a.rfind( '/' ) ) != string::npos)
            a = a.substr( posBarra + 1 );

        ui->lineEdit_relatorio->setText( QString::fromStdString( a ) );
        ss << ( n = corpus->pegarQtdAtributos() );
        ui->lineEdit_atributos->setText( QString::fromStdString( ss.str() ) );
        st << corpus->pegarQtdSentencas();
        ui->lineEdit_instancias->setText( QString::fromStdString( st.str() ) );

        //limpador da janela de atributos
        for( int i = 0; i < ui->tableWidget_atributos->rowCount(); ++i )
        {
            delete ui->tableWidget_atributos->item( i, 0 );
            delete ui->tableWidget_atributos->item( i, 1 );
        }

        ui->tableWidget_atributos->setRowCount( n );
        QTableWidgetItem *item;
        for( int i = 0; i < n; ++i )
        {
            item = new QTableWidgetItem( QString( "%1" ).arg( i ) );
            ui->tableWidget_atributos->setItem( i, 0, item );
            item = new QTableWidgetItem( QString( "%1" ).arg( QString::fromStdString(corpus->pegarAtributo(i)) ) );
            ui->tableWidget_atributos->setItem( i, 1, item );
        }
    }
}

void Janela::habilitarBotao(int index)
{
    if( corpus != NULL ) delete corpus;
    indexCorpus = index;
    if( !index )
    {
        ui->pushButton_abrir->setEnabled( false );
        ui->toolButton_construtor->setEnabled( false );
    }
    else
    {
        ui->pushButton_abrir->setEnabled( true );
        ui->toolButton_construtor->setEnabled( true );
    }
    switch( index )
    {
        case 0 :
            corpus = NULL;
            break;
        case 1 :
            corpus = new CorpusMatriz();
            break;
    }
}

void Janela::atributoSelecionado( int row, int column )
{
    int atributo = ui->tableWidget_atributos->item( row, 0 )->text().toInt();

    ui->lineEdit_nome->setText( ui->tableWidget_atributos->item( row, 1 )->text() );
}

void Janela::definirParametros()
{
    switch( indexCorpus )
    {
        case 1 :
            ModeloParam model;
            int ok;
            //coluna 0 é de nomes e coluna 1 de valores ou widgets

            //inserção de textos
            model.inserirDados(0,0,"Separador:");
            model.inserirDados(1,0,"Dividir Exemplos:");
            model.inserirDados(0,1,"_");
            model.inserirDados(2,0,"Atributos automaticos:");
            model.inserirDados(3,0,"Nº atributos:");

            popUp.ajustarModelo( model );

            //inserção Widgets
            QCheckBox *cbox = new QCheckBox();
            model.inserirDados(1,1,popUp,cbox);
            QCheckBox *cbox2 = new QCheckBox();
            cbox2->setChecked( true );
            model.inserirDados(2,1,popUp,cbox2);
            QSpinBox *sbox = new QSpinBox();
            sbox->setValue( 1 );
            sbox->setMaximum( 99 );
            sbox->setMinimum( 1 );
            sbox->setEnabled( false );
            model.inserirDados(3,1,popUp,sbox);

            //inserção de Evento(slot deve estar no Widget ou na class Param
            QObject::connect( cbox2, SIGNAL( clicked(bool) ), &popUp, SLOT( escolherAtributos(bool) ) );
            QObject::connect( sbox, SIGNAL( valueChanged(int)), &popUp, SLOT( redimensionarAtributos(int) ) );
            QMetaObject::connectSlotsByName( &popUp );

            //inicia Dialog
            ok = popUp.iniciarDialog();

            if( ok )
            {
                delete corpus;
                QCheckBox *geral;
                bool dividirExemplos;
                dividirExemplos = (( QCheckBox* )popUp.pegarWidget( 1 ))->isChecked();
                geral = ( QCheckBox* )popUp.pegarWidget( 2 );
                if( geral->isChecked() )
                    corpus = new CorpusMatriz( vector<string>(), popUp.pegarString(0)[0], dividirExemplos );
                else
                {
                    int i, tam;
                    vector< string > atributos( tam = (( QSpinBox* )popUp.pegarWidget( 3 ))->value() );
                    for( i = 0; i < tam; ++i ) atributos[i] = popUp.pegarString(i+4);
                    corpus = new CorpusMatriz( atributos, popUp.pegarString(0)[0], dividirExemplos );
                }
                if( s != "" ) abrirArquivo();
            }
            break;
    }
}
