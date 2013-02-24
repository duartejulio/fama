#include "janela.h"
#include "ui_janela.h"

Janela::Janela(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Janela)
{
    ui->setupUi(this);
    corpus = NULL;

    //a adição de novos tipos de Corpus deve ser feita identicamente ao modelo abaixo
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
    if( ( s = QFileDialog::getOpenFileName( this, "Abrir","","Documentos de texto (*.txt);;Todos os arquivos (*.*)" ) ) != "" )
        logicaDeAbertura();
}

void Janela::logicaDeAbertura()
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

void Janela::habilitarBotao(int index)
{
    if( corpus != NULL ) delete corpus;
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
    //Janela construida na classe Corpus por um método virtual
    Corpus *temp = &( corpus->construirJanela( popUp ) );
    if( temp != corpus )
    {
        delete corpus;
        corpus = temp;
        if( s != "" ) logicaDeAbertura();
    }
}
