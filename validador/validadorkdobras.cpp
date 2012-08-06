#include "validadorkdobras.h"

ValidadorKDobras::ValidadorKDobras( int dobras )
{
    this->dobras = dobras;
}

ValidadorKDobras::~ValidadorKDobras()
{
    //dtor
}

vector< vector< float > > ValidadorKDobras::executarExperimento( Treinador &treinador, Corpus &corpus )
{
    vector< vector< float > > resultado;
    vector< Corpus* > vetCorpus;
    Corpus *acumulador = corpus.clone();
    acumulador->limpaFrases();

    vetCorpus = corpus.splitCorpus( dobras );
    for( int i = 0; i < dobras; ++i )
    {
        for( register int j = 0; j < dobras; ++j )
            if( j != i ) *acumulador += *vetCorpus[j];
        treinador.executarTreinamento( *acumulador, ATRBT_ANALISADO )->executarClassificacao( *vetCorpus[i], ATRBT_CLASSIFICADO );
        resultado.push_back( avaliador->calcularDesempenho( *vetCorpus[i], ATRBT_ANALISADO, corpus.pegarQtdAtributos() - 1 ) );
        acumulador->limpaFrases();
    }
    vetCorpus.clear();
    return resultado;
}
