#include "validador.h"

Validador::Validador( Avaliador &avaliador, int numeroIteracoes )
{
    this->avaliador = &avaliador;
    this->numeroIteracoes = numeroIteracoes;
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

bool Validador::ajustarNumeroIteracoes( int numeroIteracoes )
{
    if( numeroIteracoes <= 0 ) return false;
    this->numeroIteracoes = numeroIteracoes;
    return true;
}
