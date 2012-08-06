#include "validadordivisao.h"

ValidadorDivisao::ValidadorDivisao( float percTeste, int numeroIteracoes )
{
    this->percTeste = percTeste;
    this->numeroIteracoes = numeroIteracoes;
}

ValidadorDivisao::~ValidadorDivisao()
{
    //dtor
}

vector< vector< float > > ValidadorDivisao::executarExperimento( Treinador &treinador, Corpus &corpus )
{
    vector< vector< float > > resultado;
    vector< Corpus* > vetCorpus;
    for( int i = 0; i < numeroIteracoes; ++i )
    {
        vetCorpus = corpus.splitCorpus( percTeste );
        treinador.executarTreinamento( *vetCorpus[0], ATRBT_ANALISADO )->executarClassificacao( *vetCorpus[1], ATRBT_CLASSIFICADO );
        resultado.push_back( avaliador->calcularDesempenho( *vetCorpus[1], ATRBT_ANALISADO, corpus.pegarQtdAtributos() - 1 ) );
        vetCorpus.clear();
    }
    return resultado;
}
