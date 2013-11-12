#include <iostream>
#include <sstream>

#include "../corpus/corpusmatriz.h"
#include "../treinador/c50treinador.h"
#include "../avaliador/avaliador_acuracia.h"

int main()
{
    vector<string> classes, atributos, v;

    CorpusMatriz objCorpus(vector<string>(), ',', true, true);
    objCorpus.carregarArquivo("../inputs/golf.data");

    classes.push_back("Play");
    classes.push_back("Don't Play");

    atributos = objCorpus.pegarAtributos();
    atributos.erase(atributos.end());

    C50Treinador objTreinador(25, atributos, classes);
    int at = objCorpus.pegarPosAtributo("play");
    int x = objCorpus.criarAtributo("classe");

    Classificador *objClass;
/*
    cout << objCorpus.discreto(0, v);
    cout << "-" << v.size();
    cout << " (" << v[0] << ")";
    cout << " (" << v[1] << ")";
    cout << " (" << v[2] << ")";
    return -2;
*/
    objClass = objTreinador.executarTreinamento(objCorpus, at);

    cout<<"construiu o classificador"<<endl;
    objClass->executarClassificacao(objCorpus,x);

    cout<<"terminou a classificacao"<<endl;
    objCorpus.gravarArquivo("#corpusGravado4.txt");

	AvaliadorAcuracia objAvalAc;
	cout << "Acuracia:   " << 100*objAvalAc.calcularDesempenho(objCorpus, at, x)[0] << " %" <<endl << endl;

    return 0;
}
