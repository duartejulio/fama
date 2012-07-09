#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>

#include "../corpus/corpusmatriz.h"
#include "../treinador/regressaolinear.h"

using namespace std;

int main()
{
    vector<string> atributos;
    atributos.push_back("v1");
    atributos.push_back("v2");
    Classificador *objClass;
    CorpusMatriz objCorpus( atributos );
    objCorpus.ajustarSeparador(',');

    objCorpus.carregarArquivo( "../inputs/ex1data1.txt" );// CORPUS COMPLETO

    RegressaoLinear objRLin;
    objClass = objRLin.executarTreinamento( objCorpus, 1 );
    system("pause");
    return 1;
}
