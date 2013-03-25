#ifndef CORPUSMATRIZUI_H
#define CORPUSMATRIZUI_H

#include "corpusmatriz.h"
#include <QCheckBox>
#include "../Interface/InterfaceFAMA/modeloparam.h"
#include "../Interface/InterfaceFAMA/param.h"

class CorpusMatrizUI : public CorpusMatriz
{
    public:
        CorpusMatrizUI( vector<string> atributos = vector<string>(),
                      char separador = '_', bool dividirExemplos = false,
                      bool apararValores = false);
        Corpus* construirJanela( void *popUp );
        Corpus* clone();
};

#endif // CORPUSMATRIZUI_H
