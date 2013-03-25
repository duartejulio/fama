#include "hmmui.h"

HMMUI::HMMUI( string atributoBase ) : HMM( atributoBase )
{
}

Treinador* HMMUI::construirJanela( void *popUp, Corpus &corpus )
{
    Param *popUpPointer = ( Param * )popUp;
    ModeloParam model;
    QStringList sList;
    vector< string > atributos = corpus.pegarAtributos();
    int ok, qtdAtributos = atributos.size();

    model.inserirDados(0,0,"Atributo base:");

    popUpPointer->ajustarModelo( model );

    //inserção Widgets
    QComboBox *comboBox = new QComboBox();
    for( register int i = 0; i < qtdAtributos; ++i ) sList << QString::fromStdString( atributos[i] );
    comboBox->insertItems( 0, sList );
    model.inserirDados( 0, 1, *popUpPointer, comboBox );

    ok = popUpPointer->iniciarDialog();


    if( ok )
    {
        Treinador *treinador = new HMMUI( comboBox->currentText().toStdString() );
        return treinador;
    }
    return this;
}
