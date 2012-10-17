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
    int nExemplos, e, c0, c1, iResposta;

    //carrega conjunto de dados
    CorpusMatriz objCorpus;
    objCorpus.ajustarSeparador(',');
    objCorpus.carregarArquivo( "../inputs/treinamento.data" );
    iResposta = objCorpus.pegarPosAtributo("Classe");
    
    system("cls");
    cout << "atributo alvo: " << iResposta << endl;
    cout << (nExemplos = objCorpus.pegarQtdTokens(0)) << " exemplos\n";

    //indica classes alvo
    classes.push_back("maligno");
    classes.push_back("benigno");
    c0 = c1 = 0;
        
    for (e=0; e < nExemplos; e++){
        if (objCorpus.pegarIndice(classes[0]) == objCorpus.pegarValor(0, e, iResposta))
            c0++;
        else
            c1++;
    }

    cout << c0 << "maligno / " << c1 << " benigno / " <<endl;
    
    cout << 100.*c0/nExemplos << " / " << 100.*c1/nExemplos << endl;
 
    atributos = objCorpus.pegarAtributos();

    for (unsigned int i=0; i < atributos.size(); i++) {
        cout << "\n Atributo " << i << ":  " << atributos[i];
        // (atributos[i]!="Purchase")
            atributosTreino.push_back(atributos[i]);
    }

    DecisionTree objTree(atributosTreino, classes);
 
    Classificador *objClass = objTree.executarTreinamento(objCorpus, iResposta);

    objCorpus.criarAtributo("algoritmo", "O");
    objClass->executarClassificacao(objCorpus, iResposta+1);
   
	cout << endl << "Press any key to quit..." << endl;
	getch();

    AvaliadorAcuracia objAvalAcur;
    printf( "Acuracia: %.2f%%\n", 100 * objAvalAcur.calcularDesempenho( objCorpus,
     iResposta, iResposta + 1)[0] );

    //objCorpus.gravarArquivo( "../inputs/data.gravar" );

	cout << endl << "Press any key to quit..." << endl;
	getch();
   
    delete objClass;

    return 0;
}
