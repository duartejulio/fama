#include "validadortreino.h"

ValidadorTreino::ValidadorTreino()
{
    //ctor
}

ValidadorTreino::~ValidadorTreino()
{
    //dtor
}

vector< vector< float > > ValidadorTreino::executarExperimento( Treinador &treinador, Corpus &corpus )
{
    vector< vector< float > > resultado;
    treinador.executarTreinamento( corpus, ATRBT_ANALISADO )->executarClassificacao( corpus, ATRBT_CLASSIFICADO );
    resultado.push_back( avaliador->calcularDesempenho( corpus, ATRBT_ANALISADO, corpus.pegarQtdAtributos() - 1 ) );
    return resultado;
}
