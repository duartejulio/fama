#include "avaliadormatrizconfusao.h"

#include <iomanip>

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
                cout << "Classe não encontrada, uma exceção será gerada.";
                throw "Classe não encontrada pela matriz de confusão";
            }

            vectorMatriz[posVerdadeiro*numeroClasses+posResposta]++;
        }
    }

    ultimaMatriz = vectorMatriz;
    return vectorMatriz;
}

bool AvaliadorMatrizConfusao::imprimirMatrizConfusao(){
    cout << "========= Matriz de Confusão =========" << endl << endl;
    if (!ultimaMatriz.size()){
        cout << "Não há matriz de confusão calculada" << endl;
        return false;
    }

    string header = "Vrd\\Rsp";
    unsigned int numeroClasses = classes.size(), v, r,
     tamanho = header.length();

    for (v=0; v<numeroClasses; v++)
        if (classes[v].length() > tamanho)
            tamanho = classes[v].length();

    cout << setw(tamanho) << header;
    for (v=0; v<numeroClasses; v++)
        cout  << " | " << setw(tamanho) << classes[v];
    cout << endl;

    for (v=0; v<tamanho*3+6; v++)
        cout << "-";
    cout << endl;

    for (v=0; v<numeroClasses; v++){
        cout << setw(tamanho) << classes[v];
        for (r=0; r<numeroClasses; r++)
            cout  << " | " << setw(tamanho) << ultimaMatriz[v*numeroClasses+r];
        cout << endl;
    }
    for (v=0; v<tamanho*3+6; v++)
        cout << "-";
    cout << endl;

    return true;
}
