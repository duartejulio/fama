#include "janela.h"
#include "ui_janela.h"

Janela::Janela(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Janela)
{
    ui->setupUi(this);
}

Janela::~Janela()
{
    delete ui;
}

void Janela::abrirArquivo()
{
    QString s = QFileDialog::getOpenFileName( this, "Abrir","","Documentos de texto (*.txt);;Todos os arquivos (*.*)" );
    if( s != "" )
    {
        string a = "";
        stringstream ss, st;
        int n;
        vector<string> atributos;
        atributos.push_back("word");
        atributos.push_back("tpos");
        atributos.push_back("adpos");

        Corpus *corpus = new CorpusMatriz( atributos );
        corpus->carregarArquivo( s.toStdString() );
        ss << ( n = corpus->pegarQtdAtributos() );
        ui->lineEdit_atributos->setText( QString::fromStdString( ss.str() ) );
        st << corpus->pegarQtdSentencas();
        ui->lineEdit_instancias->setText( QString::fromStdString( st.str() ) );

        for( int i = 0; i < n; ++i )
        {
            a += corpus->pegarAtributo( i );
            a += '\n';
        }
        ui->lineEdit_todosAtributos->setText( QString::fromStdString( a ) );
    }
}
