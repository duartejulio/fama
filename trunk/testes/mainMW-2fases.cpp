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

#define FASE 2

using namespace std;

int main()
{
    vector<string> atributos, classes, classesDeMalware, atributosTreino;
    int nConjExemplos, c, iResposta, iRespostaFase2, iSaidaFase1, iSaidaFase2;
    char escolha;

    //carrega conjunto de dados
    CorpusMatriz objCorpus(atributos, ';', true, true);
    if (FASE==1)
        objCorpus.carregarArquivo( "../inputs/experimento.dat" );
    else
        objCorpus.carregarArquivo( "#experimento_fase1.txt");

    atributos = objCorpus.pegarAtributos();

    //quantidade de atributos
    cout << (atributos.size()) << " atributos\n";

    //quantidade de conjuntos de exemplos
    cout << (nConjExemplos = objCorpus.pegarQtdConjExemplos()) << " exemplos\n";

    //indice do atributo a aprender
    iResposta = objCorpus.pegarPosAtributo("Malware");
    iRespostaFase2 = objCorpus.pegarPosAtributo("ClassesMal");
    if (FASE==1)
        iSaidaFase1 = objCorpus.criarAtributo("saida", "O");
    else
        iSaidaFase1 = objCorpus.pegarPosAtributo("saida");


    //indica classes alvo
    classes.push_back("maligno");
    classes.push_back("benigno");

    //indica classes alvo - fase 2
    classesDeMalware.push_back("benigno");
    classesDeMalware.push_back("trojan");
    classesDeMalware.push_back("virus");
    classesDeMalware.push_back("worm");
    classesDeMalware.push_back("backdoor");
    classesDeMalware.push_back("rootkit");
    classesDeMalware.push_back("bot");
    classesDeMalware.push_back("spyware");

    //cout << c0 << " / " << c1 << " / " << c2 << endl;

    cout << "(e) para estático, (d) para dinâmico, ou todos:";
    escolha='e';
    cin >> escolha;
    if (escolha>'Z')
        escolha -= 'a' - 'A';

    //remove atributos que nao devem ser utilizados pelo treinamento
    for (unsigned int i=0; i < atributos.size(); i++)
        if (((int)i)!=iResposta && ((int)i)!=iRespostaFase2 && ((int)i)!=iSaidaFase1){
            if (escolha=='D' && atributos[i][0]=='D')
                atributosTreino.push_back(atributos[i]);
            else
            if (escolha=='E' && atributos[i][0]=='E')
                atributosTreino.push_back(atributos[i]);
            else
            if (escolha!='E' && escolha!='D')
                atributosTreino.push_back(atributos[i]);
        }

    AvaliadorAcuracia objAvalAcur;
    Treinador* treinador;

if (FASE==1){
    //Fase 1

    DecisionStump objStump(atributosTreino, classes);
    C50Treinador objC50(60, atributosTreino, classes);
    RandomForest objForest(&objC50, atributosTreino, 10, 6);//número de árvores, quantidade de atributos

    AvaliadorMatrizConfusao objAvalMatrizConfusao(classes);
    ValidadorKDobras objValidador(objAvalAcur, NFOLDS);

    //treinador = &objStump;
    treinador = &objC50;
    //treinador = &objForest;

    vector< vector< float > > v = objValidador.executarExperimento(*treinador, objCorpus, iResposta, iSaidaFase1);

    float media = 0;
    for (c=0;c<NFOLDS;c++){
        cout << c << " - " << 100.*v[c][0] << "; ";
        media +=v[c][0];
    }
    cout << endl << "Media: " << 100.*media/NFOLDS << endl;

    objCorpus.gravarArquivo("#experimento_fase1.txt");
    objAvalMatrizConfusao.calcularDesempenho(objCorpus, iResposta, iSaidaFase1);
    objAvalMatrizConfusao.imprimirMatrizConfusao();
}
else{
    //Fase 2
    cout << "Fase 2\n";
    atributosTreino.push_back("saida");

    DecisionStump objStump2(atributosTreino, classesDeMalware);
    C50Treinador objC502(25, atributosTreino, classesDeMalware);
    RandomForest objForest2(&objC502, atributosTreino, 101, 5);//número de árvores, quantidade de atributos

    AvaliadorMatrizConfusao objAvalMatrizConfusaoFase2(classesDeMalware);
    ValidadorKDobras objValidador2(objAvalAcur, NFOLDS);
    iSaidaFase2 = objCorpus.criarAtributo("saidaFase2", "0");

    //treinador = &objStump2;
    treinador = &objC502;
    //treinador = &objForest2;

    vector< vector< float > > v2 = objValidador2.executarExperimento(*treinador, objCorpus, iRespostaFase2, iSaidaFase2);

    float media = 0;
    for (c=0;c<NFOLDS;c++){
        cout << c << " - " << 100.*v2[c][0] << "; ";
        media +=v2[c][0];
    }
    cout << endl << "Media: " << 100.*media/NFOLDS << endl;

    objAvalMatrizConfusaoFase2.calcularDesempenho(objCorpus, iRespostaFase2, iSaidaFase2);
    objAvalMatrizConfusaoFase2.imprimirMatrizConfusao();
}

  return 0;
}
