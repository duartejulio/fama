#include "janela.h"
#include "ui_janela.h"

Janela::Janela(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Janela)
{
    ui->setupUi(this);

    //ui->comboBox_corpus->addItem( "Escolha o Corpus" );
    //ui->comboBox_corpus->addItem( "CorpusMatriz" );

    //ui->tableWidget_atributos->setColumnCount( 2 );
    ui->tableWidget_atributos->setHorizontalHeaderLabels( QStringList() << "No." << "Nome" );
    //ui->tableWidget_atributos->verticalHeader()->setVisible( false ); // Deixa invisível o cabeçalho vertical
    //ui->tableWidget_atributos->horizontalHeader()->setStretchLastSection(true); // Alarga a última coluna conforme o tamanho do TableView
    //ui->tableWidget_atributos->setSelectionBehavior(QAbstractItemView::SelectRows);  // Seleciona toda a linha quando um item da linha é ativado
    //ui->tableWidget_atributos->setSelectionMode(QAbstractItemView::SingleSelection); // Permite selecionar apenas um item por vez
}

Janela::~Janela()
{
    delete ui;
    delete corpus;
}

void Janela::abrirArquivo()
{
    QString s = QFileDialog::getOpenFileName( this, "Abrir","","Documentos de texto (*.txt);;Todos os arquivos (*.*)" );
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
    if( index )
        ui->comboBox_corpus->removeItem( 0 );
    switch( index )
    {
        case 1 :
            delete corpus;
            ParamCorpus construtor;
            construtor.exec();
            corpus = new CorpusMatriz( construtor.atributos, construtor.separador, construtor.dividirExemplos );
            break;
    }
}

void Janela::atributoSelecionado( int row, int column )
{
    int atributo = ui->tableWidget_atributos->item( row, 0 )->text().toInt();

    ui->lineEdit_nome->setText( ui->tableWidget_atributos->item( row, 1 )->text() );
}
