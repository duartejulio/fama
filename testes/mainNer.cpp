#include <iostream>
#include <vector>
#include <map>
#include <iterator>
#include <cstdio>
#include <cstdlib>

#include "../corpus/corpusmatriz.h"
#include "../treinador/hmm.h"

#include "../avaliador/avaliador_acuracia.h"
#include "../avaliador/avaliador_entidade.h"
#include "../avaliador/avaliadormatrizconfusao.h"
#include "../classificador/classificadorhmm.h"
#include "../validador/validadorkdobras.h"
#include "../processador/processadorJanela.h"

using namespace std;

int main()
{
    int n, n1, atributo, novoAtributo;
    vector<string> atributos, atributosTeste, classes;
    atributos.push_back("word");
    atributos.push_back("ner");

    CorpusMatriz objCorpus(atributos, '\t', false);
    objCorpus.carregarArquivo( "../inputs/ner.txt");
    atributo = objCorpus.pegarPosAtributo("ner");
    novoAtributo = objCorpus.criarAtributo("novoner");

    ProcessadorJanela proc(1, "word", true);

    string agregado = proc.processarCorpus(objCorpus)[2];
    objCorpus.gravarArquivo("#temp.txt");

    //cout << objCorpus.pegarQtdConjExemplos() << endl;
    //cout << objCorpus.pegarQtdExemplos(0) << endl;

    //descobre classes
    map<string,int> classesDict;
    n = objCorpus.pegarQtdConjExemplos();
    for (int i=0;i<n;i++){
        n1 = objCorpus.pegarQtdExemplos(i);
        for (int j=0;j<n1;j++)
             classesDict[objCorpus(i,j,atributo)] = 1;
    }
    for (map<string,int>::iterator it = classesDict.begin(); it != classesDict.end() ;it++)
            classes.push_back(it->first);

//    cout << classes.size() << endl;
//    for (int i=0;i<classes.size();i++)
//        cout << classes[i] << endl;

    HMM objHMM("word");
/*
    Classificador *objClass;
    cout << "Treinando...\n";
    objClass = objHMM.executarTreinamento( objCorpus, atributo );

    cout << "Classificando...\n";
    objClass->executarClassificacao( objCorpus, novoAtributo );

*/
    int NFOLDS=10;
    cout << "Validacao...\n";
    AvaliadorAcuracia objAvalAcur;
    AvaliadorEntidade objAvalEnt;
//    objAvalEnt.calcularDesempenho(objCorpus, atributo, novoAtributo);
    ValidadorKDobras objValidador(objAvalEnt, NFOLDS, false);

    vector< vector< float > > v = objValidador.executarExperimento(
                                    objHMM, objCorpus, atributo, novoAtributo);

    float media = 0;
    for (int c=0;c<NFOLDS;c++){
        cout << c << " - " << 100.*v[c][0] << endl;
        media +=v[c][0];
    }
    cout << "Media: " << 100.*media/NFOLDS << endl;

    printf( "\nAcuracia: %.2f%%\n", 100 * objAvalAcur.calcularDesempenho( objCorpus, atributo, novoAtributo )[ 0 ] );
    objCorpus.gravarArquivo( "../outputs/corpusGravado.txt" );
//    objClass->gravarConhecimento( "../outputs/conhecimentoHMM.txt" );

    AvaliadorMatrizConfusao objAvalMatrizConfusao(classes);
    objAvalMatrizConfusao.calcularDesempenho(objCorpus, atributo, novoAtributo);
    //objAvalMatrizConfusao.imprimirMatrizConfusao();

    char c;
    cin >> c;
}
