#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>

#include "../corpus/corpusmatriz.h"
#include "../avaliador/avaliador_acuracia.h"
#include "../validador/validadorkdobras.h"
#include "../treinador/naivebayes.h"

using namespace std;

int main()
{
    vector<string> atributos, classes, atributosTreino;
    unsigned int nConjExemplos, e, c0, c1, c, u, iResposta, iSaida, total, dobras = 10;

    //carrega conjunto de dados
    CorpusMatriz objCorpus(atributos, ',', true);
    objCorpus.carregarArquivo( "../inputs/breast-cancer-wisconsin" );

    //indice do atributo a aprender
    iResposta = objCorpus.pegarPosAtributo("Class");
    cout << "Classe:" << iResposta << endl;
    //quantidade de conjuntos de exemplos
    cout << (nConjExemplos = objCorpus.pegarQtdConjExemplos()) << " exemplos\n";

    //indica classes alvo
    classes.push_back("2");
    classes.push_back("4");

    //calcula priori das classes
    c0 = c1 = total = u = 0;
    for (c = 0; c < nConjExemplos; c++){
        for (e = 0; e < (unsigned)objCorpus.pegarQtdExemplos(c); e++){
            if (objCorpus.pegarIndice(classes[0]) == objCorpus.pegarValor(c, e, iResposta))
                c0++;
            else
            if (objCorpus.pegarIndice(classes[1]) == objCorpus.pegarValor(c, e, iResposta))
                c1++;
            else{
                cout << iResposta << " " << objCorpus.pegarSimbolo(objCorpus.pegarValor(c, e, iResposta)) << endl;
                u++;
            }
            total++;
        }
    }

    cout << 100.*c0/total << " / " << 100.*c1/total <<  " / " << 100.*u/total << endl;
    atributos = objCorpus.pegarAtributos();

    //remove atributos que nao devem ser utilizados pelo treinamento
    for (unsigned int i=0; i < atributos.size(); i++)
        if (i!=iResposta && i)//tira classe e serial
            atributosTreino.push_back(atributos[i]);

    NaiveBayes objNB(atributosTreino, classes);

    AvaliadorAcuracia objAvalAcur;
    ValidadorKDobras objValidador(objAvalAcur, dobras);
    iSaida = objCorpus.criarAtributo("saida", "O");

    vector< vector< float > > v = objValidador.executarExperimento(objNB, objCorpus, iResposta, iSaida);
    float media = 0;
    for (c=0;c<dobras;c++){
        cout << c << " - " << v[c][0] << endl;
        media += v[c][0];
    }
    cout << "*" << media/dobras << endl;

    return 0;
}
