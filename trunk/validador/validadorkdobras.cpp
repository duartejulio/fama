#include "validadorkdobras.h"

ValidadorKDobras::ValidadorKDobras( Avaliador &avaliador, int dobras ) :
Validador( avaliador, dobras )
{

}

ValidadorKDobras::~ValidadorKDobras()
{
    //dtor
}

vector< vector< float > > ValidadorKDobras::executarExperimento( Treinador &treinador, Corpus &corpus, int atributoTreino, int atributoTeste )
{
    double contador;
    int qtd_sentencas, aux;
    vector< vector< float > > resultado;
    vector< Corpus* > vetCorpus;
    vector< int > vetMascara( qtd_sentencas = corpus.pegarQtdSentencas() );

    srand( time( NULL ) );
    for( int i = 0; i < numeroIteracoes; ++i )
    {
        //ineficiente qdo i grande
        for( contador = .0; contador*numeroIteracoes <= qtd_sentencas; ++contador )
            if( !vetMascara[aux = rand()%qtd_sentencas] )
                vetMascara[aux] = 1;
            else
            {
                while( !vetMascara[++aux%=qtd_sentencas] );
                vetMascara[aux] = 1;
            }

        vetCorpus = corpus.splitCorpus( vetMascara );
        treinador.executarTreinamento( *vetCorpus[0], atributoTreino )->executarClassificacao( *vetCorpus[1], atributoTeste );
        resultado.push_back( avaliador->calcularDesempenho( *vetCorpus[1], atributoTreino, atributoTeste ) );
        vetCorpus.clear(); ///mesmo problema do validadorDivisao
    }
    return resultado;
}
