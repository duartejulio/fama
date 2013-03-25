#ifndef TBLUI_H
#define TBLUI_H

#include "tbl.h"
#include "../Interface/InterfaceFAMA/modeloparam.h"
#include "../Interface/InterfaceFAMA/param.h"

class TBLUI : public TBL
{
    public:
        TBLUI( Classificador* classInicial = NULL, string arqMoldeRegras = "", string atributoChute = "tpos", int toleranciaScore = 5 );
        Treinador* construirJanela( void *popUp, Corpus &corpus );
};

#endif // TBLUI_H
