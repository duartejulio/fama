#include "corpusmatrizui.h"

CorpusMatrizUI::CorpusMatrizUI( vector<string> atributos, char separador, bool dividirExemplos, bool apararValores )
    :CorpusMatriz( atributos, separador, dividirExemplos, apararValores)
{   
}

Corpus* CorpusMatrizUI::construirJanela( void *popUp )
{
    Param *popUpPointer = ( Param * )popUp;
    ModeloParam model;
    int ok;
    //coluna 0 é de nomes e coluna 1 de valores ou widgets

    //inserção de textos
    model.inserirDados(0,0,"Separador:");
    model.inserirDados(1,0,"Dividir Exemplos:");
    model.inserirDados(0,1,"_");
    model.inserirDados(2,0,"Atributos automaticos:");
    model.inserirDados(3,0,"Nº atributos:");

    //O modelo tem que ser inserido no Param antes de definir os Widgets
    popUpPointer->ajustarModelo( model );

    //inserção Widgets
    QCheckBox *cbox = new QCheckBox();
    model.inserirDados(1,1,*popUpPointer,cbox);
    QCheckBox *cbox2 = new QCheckBox();
    cbox2->setChecked( true );
    model.inserirDados(2,1,*popUpPointer,cbox2);
    QSpinBox *sbox = new QSpinBox();
    sbox->setValue( 1 );
    sbox->setMaximum( 99 );
    sbox->setMinimum( 1 );
    sbox->setEnabled( false );
    model.inserirDados(3,1,*popUpPointer,sbox);

    //inserção de Evento(slot deve estar no Widget ou na classe Param)
    QObject::connect( cbox2, SIGNAL( clicked(bool) ), popUpPointer, SLOT( escolherAtributos(bool) ) );
    QObject::connect( sbox, SIGNAL( valueChanged(int)), popUpPointer, SLOT( redimensionarAtributos(int) ) );
    QMetaObject::connectSlotsByName( popUpPointer );

    //inicia Dialog
    ok = popUpPointer->iniciarDialog();

    if( ok )
    {
        Corpus *corpus;
        //QCheckBox *geral;
        bool dividirExemplos;
        //dividirExemplos = (( QCheckBox* )popUpPointer->pegarWidget( 1 ))->isChecked();
        //geral = ( QCheckBox* )popUpPointer->pegarWidget( 2 );
        dividirExemplos = cbox->isChecked();
        if( cbox2->isChecked() )
            corpus = new CorpusMatrizUI( vector<string>(), popUpPointer->pegarString(0)[0], dividirExemplos );
        else
        {
            int i, tam;
            vector< string > atributos( tam = (( QSpinBox* )popUpPointer->pegarWidget( 3 ))->value() );
            for( i = 0; i < tam; ++i ) atributos[i] = popUpPointer->pegarString(i+4);
            corpus = new CorpusMatrizUI( atributos, popUpPointer->pegarString(0)[0], dividirExemplos );
        }
        return corpus;
    }
    return this;
}

Corpus* CorpusMatrizUI::clone()
{
    return new CorpusMatrizUI( *this );
}
