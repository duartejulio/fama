#include "validadorkdobras.h"

ValidadorKDobras::ValidadorKDobras( Avaliador &avaliador, int dobras ) :
Validador( avaliador, dobras )
{
    srand( time( NULL ) );
}

ValidadorKDobras::~ValidadorKDobras()
{
    //dtor
}

vector< vector< float > > ValidadorKDobras::executarExperimento( Treinador &treinador, Corpus &corpus, int atributoTreino, int atributoTeste )
{
    int qtd_sentencas = corpus.pegarQtdSentencas();
    vector< int> vetDobras;
    vector< vector< float > > resultado;
    vector< Corpus* > vetCorpus;
    vector< bool > vetMascara(qtd_sentencas);

    for( int i = 0; i < numeroIteracoes; ++i )
        vetDobras.assign(qtd_sentencas/numeroIteracoes, i);

    vetDobras.resize(qtd_sentencas, -1);
    random_shuffle( vetDobras.begin(), vetDobras.end() );

    for( int i = 0; i < numeroIteracoes; ++i )
    {
        for( int j = 0; j < qtd_sentencas; ++j )
            if( vetDobras[j] == i ) vetMascara[j] = true;
            else vetMascara[j] = false;

        vetCorpus = corpus.splitCorpus( vetMascara );
        treinador.executarTreinamento( *vetCorpus[0], atributoTreino )->executarClassificacao( *vetCorpus[1], atributoTeste );
        resultado.push_back( avaliador->calcularDesempenho( *vetCorpus[1], atributoTreino, atributoTeste ) );
        delete vetCorpus[0];
        delete vetCorpus[1];
    }
    return resultado;
}
