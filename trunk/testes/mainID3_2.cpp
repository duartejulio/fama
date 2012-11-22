#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <conio.h>

#include "dtree.h"
#include "../corpus/corpusmatriz.h"
#include "../avaliador/avaliador_acuracia.h"

using namespace std;

int main()
{
    vector<string> atributos, classes, atributosTreino;
    int nExemplos, i, c, nConjExemplos, e, c0, c1, iResposta, nTotalExemplos;

    //carrega conjunto de dados
    CorpusMatriz objCorpus(vector<string>(), ',', true, true);
    objCorpus.carregarArquivo( "../inputs/treinamento.data" );
    iResposta = objCorpus.pegarPosAtributo("Classe");

    cout << "atributo alvo: " << iResposta << endl;
    cout << (nTotalExemplos = objCorpus.pegarQtdTotalExemplos()) << " exemplos\n";

    //indica classes alvo
    classes.push_back("maligno");
    classes.push_back("benigno");
    c0 = c1 = 0;

    nConjExemplos = objCorpus.pegarQtdConjExemplos();
    for (c=0; c<nConjExemplos; c++){
        nExemplos = objCorpus.pegarQtdExemplos(c);
        for (e=0; e < nExemplos; e++){
            if (objCorpus.pegarIndice(classes[0]) == objCorpus.pegarValor(c, e, iResposta))
                c0++;
            else
                c1++;
        }
    }

//    cout << c0 << " won't buy / " << c1 << " will buy / " <<endl;
    cout << c0 << "maligno / " << c1 << " benigno / " <<endl;

    cout << 100.*c0/nTotalExemplos << " / " << 100.*c1/nTotalExemplos << endl;

    atributos = objCorpus.pegarAtributos();

    for (unsigned int i=0; i < (int)atributos.size(); i++) {
        cout << "\n Atributo " << i << ":  " << atributos[i];
        // if(atributos[i]!="Purchase")
            atributosTreino.push_back(atributos[i]);
    }

    DecisionTree objTree(atributosTreino, classes);
    DecisionTree objTree2(vector<string>(), classes);
    RandomForest objForest(&objTree2, atributosTreino, 1, 19);
    
    //Classificador *objClass = objTree.executarTreinamento(objCorpus, iResposta);
    Classificador *objClass = objForest.executarTreinamento(objCorpus, iResposta);
    cout << "OK";
//    objCorpus.criarAtributo("algoritmo", "O");
    objClass->executarClassificacao(objCorpus, iResposta+1);

    AvaliadorAcuracia objAvalAcur;
    printf( "\nAcuracia: %.2f%%\n", 100 * objAvalAcur.calcularDesempenho( objCorpus,
     iResposta, iResposta + 1)[0] );

    objCorpus.gravarArquivo( "../inputs/data.gravar" );
    
  	cout << endl << "Press any key to quit..." << endl;
	getch();


    delete objClass;

    return 0;
}
