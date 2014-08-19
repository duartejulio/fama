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
    int i, j, qtd_ConjExemplos = corpus.pegarQtdSentencas(), qtdExemplos, c, e;
    vector< int> vetDobras;
    vector< vector< float > > resultado;
    vector< Corpus* > vetCorpus;
    vector< bool > vetMascara(qtd_ConjExemplos);

    for( i = 0; i < qtd_ConjExemplos; ++i )
        vetDobras.push_back(i%numeroIteracoes);

    random_shuffle( vetDobras.begin(), vetDobras.end() );

    for( i = 0; i < numeroIteracoes; ++i )
    {
        //cria vetor de mascara
        for( j = 0; j < qtd_ConjExemplos; ++j )
            vetMascara[j] = (vetDobras[j] == i);

        //cria corpora em função da máscara
        vetCorpus = corpus.splitCorpus( vetMascara );

        //treina o classificador
        classificador = treinador.executarTreinamento( *vetCorpus[0], atributoTreino );

        //aplica classificador no corpus de teste
        classificador->executarClassificacao( *vetCorpus[1], atributoTeste );

        //armazena resultado
        resultado.push_back( avaliador->calcularDesempenho( *vetCorpus[1], atributoTreino, atributoTeste ) );

        //copia atributo teste para corpus original
        j = 0;
        for (c = 0; c < qtd_ConjExemplos; c++)
            if (vetMascara[c]){
                qtdExemplos = corpus.pegarQtdExemplos(c);
                for (e=0; e<qtdExemplos; e++)
                    corpus(c, e, atributoTeste, (*vetCorpus[1])(j, e, atributoTeste));
                j++;
            }

        delete vetCorpus[1];
        delete vetCorpus[0];
        delete classificador;
    }

    return resultado;
}
