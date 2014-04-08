#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>

#include "../corpus/corpusmatriz.h"
#include "../avaliador/avaliador_acuracia.h"
#include "../validador/validadorkdobras.h"
#include "../stump/stump.h"
#include "../treinador/c50treinador.h"

#define NFOLDS 10

using namespace std;

int main()
{
    vector<string> atributos, classes, atributosTreino;
    int nConjExemplos, e, c0, c1, c2, c, iResposta, iSaida, total;

    //carrega conjunto de dados
    CorpusMatriz objCorpus(atributos, ';', true,true);
    objCorpus.carregarArquivo( "../inputs/malware2.dat" );

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

    //remove atributos que nao devem ser utilizados pelo treinamento
    for (unsigned int i=0; i < atributos.size(); i++)
        if (i!=iResposta)
            atributosTreino.push_back(atributos[i]);

    Treinador* treinador;
    C50Treinador objC50(75, atributosTreino, classes);
    DecisionStump objStump(atributosTreino, classes);
    AvaliadorAcuracia objAvalAcur;
    ValidadorKDobras objValidador(objAvalAcur, NFOLDS);
    iSaida = objCorpus.criarAtributo("saida", "0");

    treinador = &objC50;
    //treinador = &objStump;


    vector< vector< float > > v = objValidador.executarExperimento(*treinador, objCorpus, iResposta, iSaida);

    float media = 0;
    for (c=0;c<NFOLDS;c++){
        cout << c << " - " << 100.*v[c][0] << endl;
        media +=v[c][0];
    }
    cout << "Media: " << 100.*media/NFOLDS << endl;


    Classificador *objClass = treinador->executarTreinamento(objCorpus, iResposta);
    objClass->executarClassificacao(objCorpus, iSaida);
    printf( "Acuracia: %.2f%%\n", 100 * objAvalAcur.calcularDesempenho( objCorpus,
     iResposta, iSaida)[0]);
    //cout << objClass->descricaoConhecimento();
    delete objClass;
    return 0;
}
