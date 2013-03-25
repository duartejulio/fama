#ifndef HMMUI_H
#define HMMUI_H

#include "hmm.h"
#include <QComboBox>
#include "../Interface/InterfaceFAMA/modeloparam.h"
#include "../Interface/InterfaceFAMA/param.h"

class HMMUI : public HMM
{
public:
    HMMUI( string atributoBase = "word" );
    Treinador* construirJanela( void *popUp, Corpus &corpus );
};

#endif // HMMUI_H
