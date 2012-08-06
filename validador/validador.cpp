#include "validador.h"

Validador::Validador()
{
    //ctor
}

Validador::~Validador()
{
    //dtor
}

bool Validador::ajustarAvaliador( Avaliador &avaliador )
{
    if( &avaliador == NULL )
    {
        cout << "Erro: ajustarAvaliador!\nAjuste cancelado: avaliador nulo!" << endl;
        return false;
    }
    this->avaliador = &avaliador;
    return true;
}
