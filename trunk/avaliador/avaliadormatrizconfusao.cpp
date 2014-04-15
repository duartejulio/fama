#include "avaliadormatrizconfusao.h"

AvaliadorMatrizConfusao::AvaliadorMatrizConfusao(vector<string> classes):classes(classes)
{
    //ctor
}

AvaliadorMatrizConfusao::~AvaliadorMatrizConfusao()
{
    //dtor
}

vector<float> AvaliadorMatrizConfusao::calcularDesempenho( Corpus &corpus, int atributo_padrao, int atributo_teste )
{
    /**
    *
    *   Calcula somatorio de verdadeiros e negativos por classe
    *
    */
    vector<float> vectorMatriz;
    int row = corpus.pegarQtdSentencas(), column,
     numeroClasses = classes.size(), tam, posVerdadeiro, posResposta;
    string resposta, verdade;

    tam = numeroClasses*numeroClasses;

    vectorMatriz.resize(tam);
    for ( register int c = 0; c < tam; ++c )
        vectorMatriz[c] = 0.0;

    for ( register int i = 0; i < row; ++i )
    {
        column = corpus.pegarQtdTokens( i );

        for ( register int j = 0; j < column; ++j )
        {
            verdade = corpus(i,j,atributo_padrao);
            resposta = corpus(i,j,atributo_teste);

            posVerdadeiro = posResposta = -1;
            for ( register int c = 0; c < numeroClasses; ++c ){
                if (classes[c]==verdade)
                    posVerdadeiro = c;
                if (classes[c]==resposta)
                    posResposta = c;

            }
            if (posVerdadeiro == -1 || posResposta == -1 ){
                cout << "Classe não encontrada";
                throw "Classe não encontrada pela matriz de confusão";
            }

            vectorMatriz[posVerdadeiro*numeroClasses+posResposta]++;
        }
    }

    return vectorMatriz;
}

