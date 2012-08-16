#include "validadortreino.h"

ValidadorTreino::ValidadorTreino( Avaliador &avaliador ) : Validador( avaliador, 1 )
{
    //ctor
}

ValidadorTreino::~ValidadorTreino()
{
    //dtor
}

vector< vector< float > > ValidadorTreino::executarExperimento( Treinador &treinador, Corpus &corpus, int atributoTreino, int atributoTeste )
{
    vector< vector< float > > resultado;
    treinador.executarTreinamento( corpus, atributoTreino )->executarClassificacao( corpus, atributoTeste );
    resultado.push_back( avaliador->calcularDesempenho( corpus, atributoTreino, atributoTeste ) );
    return resultado;
}
