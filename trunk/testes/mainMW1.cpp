#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <iomanip>

#include "../id3/dtree.h"
#include "../corpus/corpusmatriz.h"
#include "../avaliador/avaliador_acuracia.h"
#include "../avaliador/avaliadormatrizconfusao.h"
#include "../validador/validadorkdobras.h"
#include "../stump/stump.h"
#include "../treinador/c50treinador.h"

#define NFOLDS 10

using namespace std;

int main()
{
    vector<string> atributos, classes, atributosTreino;
    int nConjExemplos, e, c0, c1, c2, c, iResposta, iSaida, total;
    char escolha;

    //carrega conjunto de dados
    CorpusMatriz objCorpus(atributos, ';', true,true);
    objCorpus.carregarArquivo( "../inputs/malware5.dat" );

    //quantidade de conjuntos de exemplos
    cout << (nConjExemplos = objCorpus.pegarQtdConjExemplos()) << " exemplos\n";
/*
    for (c = 0; c < nConjExemplos; c++)
        for (e = 0; e < objCorpus.pegarQtdExemplos(c); e++)
            for (int a = 0; a < 82; a++)
                cout  << objCorpus(c, e, a) << endl;

    return 1;
*/
    //indice do atributo a aprender
    iResposta = objCorpus.pegarPosAtributo("Malware");

    //indica classes alvo
    classes.push_back("maligno");
    classes.push_back("benigno");

    //calcula priori das classes
    c2 = c0 = c1 = total = 0;
    for (c = 0; c < nConjExemplos; c++){
        for (e = 0; e < objCorpus.pegarQtdExemplos(c); e++){
            if (objCorpus.pegarIndice(classes[0]) == objCorpus.pegarValor(c, e, iResposta))
                c0++;
            else
            if (objCorpus.pegarIndice(classes[1]) == objCorpus.pegarValor(c, e, iResposta))
                c1++;
            else{
                c2++;
            }
            total++;
        }
    }
    cout << 100.*c0/total << " / " << 100.*c1/total << " / " << 100.*c2/total << endl;
    //cout << c0 << " / " << c1 << " / " << c2 << endl;
    atributos = objCorpus.pegarAtributos();

    cout << "(e) para estático, (d) para dinâmico, ou todos:";
    escolha='e';
    cin >> escolha;
    if (escolha>'Z')
        escolha -= 'a' - 'A';

    //remove atributos que nao devem ser utilizados pelo treinamento
    for (unsigned int i=0; i < atributos.size(); i++)
        if (((int)i)!=iResposta){
            if (escolha=='D' && atributos[i][0]=='D')
                atributosTreino.push_back(atributos[i]);
            else
            if (escolha=='E' && atributos[i][0]=='E')
                atributosTreino.push_back(atributos[i]);
            else
            if (escolha!='E' && escolha!='D')
                atributosTreino.push_back(atributos[i]);
        }

    //cout << "\nAtributos:";
    //for (unsigned int i=0; i < atributosTreino.size(); i++)
    //    cout << atributosTreino[i] << " ";
    //cout << endl;

    Treinador* treinador;
    C50Treinador objC50(25, atributosTreino, classes);
    DecisionStump objStump(atributosTreino, classes);
    AvaliadorAcuracia objAvalAcur;
    AvaliadorMatrizConfusao objAvalMatrizConfusao(classes);
    ValidadorKDobras objValidador(objAvalAcur, NFOLDS);
    iSaida = objCorpus.criarAtributo("saida", "0");

    RandomForest objForest(&objC50, atributosTreino, 101, 5);//número de árvores, quantidade de atributos

    //treinador = &objC50;
    treinador = &objStump;
    //treinador = &objForest;


    vector< vector< float > > v = objValidador.executarExperimento(*treinador, objCorpus, iResposta, iSaida);

    float media = 0;
    for (c=0;c<NFOLDS;c++){
        cout << c << " - " << 100.*v[c][0] << endl;
        media +=v[c][0];
    }
    cout << "Media: " << 100.*media/NFOLDS << endl;
//    return 0;
/*
    Classificador *objClass = treinador->executarTreinamento(objCorpus, iResposta);
    cout << "Treinou\n";
    objClass->executarClassificacao(objCorpus, iSaida);
    printf( "Acuracia: %.2f%%\n", 100 * objAvalAcur.calcularDesempenho( objCorpus,
     iResposta, iSaida)[0]);
    cout << objClass->descricaoConhecimento();
    delete objClass;
*/
    objCorpus.gravarArquivo("#temp.txt");
    //cout << objClass->descricaoConhecimento();
    objAvalMatrizConfusao.calcularDesempenho(objCorpus, iResposta, iSaida);
    objAvalMatrizConfusao.imprimirMatrizConfusao();


    //imprime matriz


  return 0;
}
