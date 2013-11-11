#include <iostream>

#include "../corpus/corpusmatriz.h"
#include "../treinador/c50treinador.h"
#include "../avaliador/avaliador_acuracia.h"

int main()
{
    vector<string> classes, atributos;

    CorpusMatriz objCorpus(vector<string>(), ',', true, true);
    objCorpus.carregarArquivo("../inputs/iris");

    classes.push_back("Iris-setosa");
    classes.push_back("Iris-versicolor");
    classes.push_back("Iris-virginica");

    atributos = objCorpus.pegarAtributos();
    atributos.erase(atributos.end());

    C50Treinador objTreinador(25, atributos, classes);
    int at = objCorpus.pegarPosAtributo("class");
    int x = objCorpus.criarAtributo("Classificacao");

    Classificador *objClass;

    objClass = objTreinador.executarTreinamento(objCorpus, at);

    cout<<"construiu o classificador"<<endl;
    objClass->executarClassificacao(objCorpus,x);

    cout<<"terminou a classificacao"<<endl;
    objCorpus.gravarArquivo("#corpusGravado4.txt");

	AvaliadorAcuracia objAvalAc;
	cout << "Acuracia:   " << 100*objAvalAc.calcularDesempenho(objCorpus, at, x)[0] << " %" <<endl << endl;

    return 0;
}
