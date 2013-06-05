#include "validadordivisao.h"

ValidadorDivisao::ValidadorDivisao( Avaliador &avaliador, int numeroIteracoes, float percTeste ) :
Validador( avaliador, numeroIteracoes )
{
    this->percTeste = percTeste;
    srand( time( NULL ) );
}

ValidadorDivisao::~ValidadorDivisao()
{
    //dtor
}

vector< vector< float > > ValidadorDivisao::executarExperimento( Treinador &treinador, Corpus &corpus, int atributoTreino, int atributoTeste )
{
    int qtd_sentencas = corpus.pegarQtdSentencas();
    vector< vector< float > > resultado;
    vector< Corpus* > vetCorpus;
    vector< bool > vetMascara( ( int )( percTeste*qtd_sentencas ), true );
    vetMascara.resize( qtd_sentencas );

    for( int i = 0; i < numeroIteracoes; ++i )
    {
        random_shuffle( vetMascara.begin(), vetMascara.end() );
        vetCorpus = corpus.splitCorpus( vetMascara );
        treinador.executarTreinamento( *vetCorpus[0], atributoTreino )->executarClassificacao( *vetCorpus[1], atributoTeste );
        resultado.push_back( avaliador->calcularDesempenho( *vetCorpus[1], atributoTreino, atributoTeste ) );
        delete vetCorpus[0];
        delete vetCorpus[1];
    }
    return resultado;
}
