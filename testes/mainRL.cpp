#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>

#include "../corpus/corpusmatriz.h"
#include "../treinador/regressaolinear.h"
#include "../avaliador/avaliador_diferenca.h"

using namespace std;

int main()
{
    int atributo;
    vector<string> atributos;
    atributos.push_back("v1");
    atributos.push_back("v2");
    Classificador *objClass;
    AvaliadorDiferenca objAval;
    CorpusMatriz objCorpus( atributos, ',', true );

    objCorpus.carregarArquivo( "../inputs/ex1data1.txt" );// CORPUS COMPLETO
    //std::cout << objCorpus.pegarQtdConjExemplos() << " " << objCorpus.pegarQtdExemplos(0) << "\n";
    RegressaoLinear objRLin;
    objClass = objRLin.executarTreinamento( objCorpus, 1 );
    objCorpus.criarAtributo("resp", "");
    atributo = objCorpus.pegarPosAtributo("resp");
    objClass->executarClassificacao(objCorpus, atributo);
    cout << objAval.calcularDesempenho(objCorpus, atributo-1, atributo)[0];
    /*
    for (int i =0; i < objCorpus.pegarQtdConjExemplos(); i++)
        for (int j =0; j < objCorpus.pegarQtdExemplos(i); j++){
            int v = objCorpus.pegarValor(i, j, 0);
            cout << objCorpus.pegarSimbolo(v) << " ";
            v = objCorpus.pegarValor(i, j, atributo - 1);
            cout << objCorpus.pegarSimbolo(v) << " ";
            v = objCorpus.pegarValor(i, j, atributo);
            cout << objCorpus.pegarSimbolo(v) << "\n";
        }
    */
    return 1;
}
