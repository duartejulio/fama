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
    Classificador *classificador;
    int i, j, qtd_sentencas = corpus.pegarQtdSentencas();
    vector< int> vetDobras;
    vector< vector< float > > resultado;
    vector< Corpus* > vetCorpus;
    vector< bool > vetMascara(qtd_sentencas);

    for( i = 0; i < qtd_sentencas; ++i )
        vetDobras.push_back(i%numeroIteracoes);

    random_shuffle( vetDobras.begin(), vetDobras.end() );

    for( i = 0; i < numeroIteracoes; ++i )
    {
        for( j = 0; j < qtd_sentencas; ++j )
            vetMascara[j] = (vetDobras[j] == i);

        vetCorpus = corpus.splitCorpus( vetMascara );
        classificador = treinador.executarTreinamento( *vetCorpus[0], atributoTreino );
        classificador->executarClassificacao( *vetCorpus[1], atributoTeste );
        resultado.push_back( avaliador->calcularDesempenho( *vetCorpus[1], atributoTreino, atributoTeste ) );

        delete vetCorpus[0];
        delete vetCorpus[1];
        delete classificador;
    }
    return resultado;
}
