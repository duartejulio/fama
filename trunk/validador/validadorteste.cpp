#include "validadorteste.h"

ValidadorTeste::ValidadorTeste( Avaliador &avaliador, Corpus &corpusTeste ) :
Validador( avaliador, 1 )
{
    this->corpusTeste = &corpusTeste;
}

ValidadorTeste::~ValidadorTeste()
{
    //dtor
}

vector< vector< float > > ValidadorTeste::executarExperimento( Treinador &treinador, Corpus &corpus, int atributoTreino, int atributoTeste )
{
    vector< vector< float > > resultado;
    treinador.executarTreinamento( corpus, atributoTreino )->executarClassificacao( *corpusTeste, atributoTeste );
    resultado.push_back( avaliador->calcularDesempenho( *corpusTeste, corpusTeste->pegarPosAtributo( corpus.pegarAtributo( atributoTreino ) ), atributoTeste ) );
    return resultado;
}
