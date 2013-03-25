#include "treinador.h"

Treinador::Treinador()
{

}

Treinador::~Treinador()
{
    //dtor
}

Treinador* Treinador::construirJanela( void *popUp, Corpus &corpus )
{
    ostringstream erro;
    erro << "Construtor de janela nao definido\n";
    throw erro.str();
    return this;
}
