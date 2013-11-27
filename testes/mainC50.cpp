#include <iostream>
#include <sstream>

#include "../corpus/corpusmatriz.h"
#include "../treinador/c50treinador.h"
#include "../avaliador/avaliador_acuracia.h"
#include "../classificador/c50classificador.h"

int main()
{
    vector<string> classes, atributos, v;

    CorpusMatriz objCorpus(vector<string>(), ',', true, true);
    objCorpus.carregarArquivo("../inputs/golf.data");

    classes.push_back("Play");
    classes.push_back("Don't Play");

    atributos = objCorpus.pegarAtributos();
    atributos.erase(atributos.end());
    //atributos.erase(atributos.begin());//testando a remoção de um atributo

    C50Treinador objTreinador(100, atributos, classes);
    int at = objCorpus.pegarPosAtributo("play");
    int x = objCorpus.criarAtributo("classe");

    Classificador *objClass;

    objClass = objTreinador.executarTreinamento(objCorpus, at);
    objClass->gravarConhecimento("#kno.txt");
    cout<<"construiu o classificador"<<endl;

    objClass->executarClassificacao(objCorpus,x);
    cout<<"terminou a classificacao"<<endl;

    objCorpus.gravarArquivo("#corpusGravado4.txt");

	AvaliadorAcuracia objAvalAc;
	cout << "Acuracia:   " << 100*objAvalAc.calcularDesempenho(objCorpus, at, x)[0] << " %" <<endl << endl;


    return 0;
}
