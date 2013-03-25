#include "tblui.h"

TBLUI::TBLUI( Classificador* classInicial, string arqMoldeRegras, string atributoChute, int toleranciaScore )
    : TBL( classInicial, arqMoldeRegras, atributoChute, toleranciaScore )
{

}

Treinador* TBLUI::construirJanela( void *popUp, Corpus &corpus )
{
    Param *popUpPointer = ( Param * )popUp;
    ModeloParam model;
    int ok;



    return this;
}
