#ifndef MAISPROVAVELUI_H
#define MAISPROVAVELUI_H

#include "maisprovavel.h"
#include <QComboBox>
#include "../Interface/InterfaceFAMA/modeloparam.h"
#include "../Interface/InterfaceFAMA/param.h"

class MaisProvavelUI : public MaisProvavel
{
    public:
        MaisProvavelUI( string atributoBase = "word", int toleranciaUnknow = 2 );
        Treinador* construirJanela( void *popUp, Corpus &corpus );
};

#endif // MAISPROVAVELUI_H
