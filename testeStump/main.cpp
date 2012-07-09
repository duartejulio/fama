#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>

#include "corpusmatriz.h"
#include "avaliador_acuracia.h"
#include "stump.h"

using namespace std;

int main()
{
    vector<string> atributos, classes, atributosTreino;
    int nExemplos, e, c0, c1, iResposta;

    //carrega conjunto de dados
    CorpusMatriz objCorpus;
    objCorpus.ajustarSeparador(',');
    objCorpus.carregarArquivo( "../inputs/adult.data" );
    iResposta = objCorpus.pegarPosAtributo("resposta");

    cout << (nExemplos = objCorpus.pegarQtdTokens(0)) << " exemplos\n";

    //indica classes alvo
    classes.push_back(" <=50K");
    classes.push_back(" >50K");
    c0 = c1 = 0;
    for (e=0; e < nExemplos; e++){
        if (objCorpus.pegarIndice(classes[0]) == objCorpus.pegarValor(0, e, iResposta))
            c0++;
        else
            c1++;
    }
    cout << 100.*c0/nExemplos << " / " << 100.*c1/nExemplos << endl;

    atributos = objCorpus.pegarAtributos();
    for (unsigned int i=0; i < atributos.size(); i++)
        if (atributos[i]!="resposta" && atributos[i]!="workclass" && atributos[i]!="fnlwgt")
            atributosTreino.push_back(atributos[i]);

    DecisionStump objStump(atributosTreino, classes);
    Classificador *objClass = objStump.executarTreinamento(objCorpus, iResposta);

    objCorpus.criarAtributo("algoritmo", "O");
    objClass->executarClassificacao( objCorpus, iResposta + 1);

    AvaliadorAcuracia objAvalAcur;
    printf( "Acuracia: %.2f%%\n", 100 * objAvalAcur.calcularDesempenho( objCorpus,
     iResposta, iResposta + 1)[0] );

    delete objClass;
    return 0;
}
