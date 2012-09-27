#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>

#include "../corpus/corpusmatriz.h"
#include "../avaliador/avaliador_acuracia.h"
#include "../validador/validadorkdobras.h"
#include "stump.h"



using namespace std;

int main()
{
    vector<string> atributos, classes, atributosTreino;
    int nConjExemplos, e, c0, c1, c, iResposta, iSaida, total;

    //carrega conjunto de dados
    CorpusMatriz objCorpus(atributos, ',', true, true);
    objCorpus.carregarArquivo( "../inputs/adult.data" );

    //indice do atributo a aprender
    iResposta = objCorpus.pegarPosAtributo("resposta");

    //quantidade de conjuntos de exemplos
    cout << (nConjExemplos = objCorpus.pegarQtdConjExemplos()) << " exemplos\n";

    //indica classes alvo
    classes.push_back("<=50K");
    classes.push_back(">50K");

    //calcula priori das classes
    c0 = c1 = total = 0;
    for (c = 0; c < nConjExemplos; c++)
        for (e = 0; e < objCorpus.pegarQtdExemplos(c); e++){
            if (objCorpus.pegarIndice(classes[0]) == objCorpus.pegarValor(c, e, iResposta))
                c0++;
            else
                c1++;
            total++;
        }

    cout << 100.*c0/total << " / " << 100.*c1/total << endl;
    atributos = objCorpus.pegarAtributos();

    //remove atributos que nao devem ser utilizados pelo treinamento
    for (unsigned int i=0; i < atributos.size(); i++)
        if (atributos[i]!="resposta" && atributos[i]!="workclass" && atributos[i]!="fnlwgt")
            atributosTreino.push_back(atributos[i]);

    DecisionStump objStump(atributosTreino, classes);
    AvaliadorAcuracia objAvalAcur;
    ValidadorKDobras objValidador(objAvalAcur, 10);
    iSaida = objCorpus.criarAtributo("saida", "O");


/*
    vector< vector< float > > v = objValidador.executarExperimento(objStump, objCorpus, iResposta, iSaida);
    float media = 0;
    for (c=0;c<10;c++){
        cout << c << " - " << v[c][0] << endl;
        media +=v[c][0];
    }
    cout << "*" << media/10 << endl;
*/

    Classificador *objClass = objStump.executarTreinamento(objCorpus, iResposta);
    objClass->executarClassificacao(objCorpus, iSaida);
    cout << objClass->descricaoConhecimento();
    printf( "Acuracia: %.2f%%\n", 100 * objAvalAcur.calcularDesempenho( objCorpus,
     iResposta, iSaida)[0]);

    delete objClass;
    return 0;
}
