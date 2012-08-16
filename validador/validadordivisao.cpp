#include "validadordivisao.h"

ValidadorDivisao::ValidadorDivisao( Avaliador &avaliador, int numeroIteracoes, float percTeste ) :
Validador( avaliador, numeroIteracoes )
{
    this->percTeste = percTeste;
}

ValidadorDivisao::~ValidadorDivisao()
{
    //dtor
}

vector< vector< float > > ValidadorDivisao::executarExperimento( Treinador &treinador, Corpus &corpus, int atributoTreino, int atributoTeste )
{
    double contador;
    int qtd_sentencas = corpus.pegarQtdSentencas(), aux;
    vector< vector< float > > resultado;
    vector< Corpus* > vetCorpus;

    srand( time( NULL ) );
    for( int i = 0; i < numeroIteracoes; ++i )
    {
        vector< int > vetMascara( qtd_sentencas );
        for( contador = .0; contador <= percTeste*qtd_sentencas; ++contador )
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
        vetCorpus.clear(); ///se o clear não der delete no conteudo esta ocorrendo memory leak
    }
    return resultado;
}
