#include "c50treinador.h"
#include "../classificador/c50classificador.h"
#include <fstream>

extern "C" int c50train(char* baseFileName, float cfvalue);

C50Treinador::C50Treinador(float cf, vector<string> atributos, vector<string> classes)
{
    this->cf = cf;
    this->atributos = atributos;
    this->classes = classes;
}

C50Treinador::~C50Treinador()
{
    //dtor
}

Classificador *C50Treinador::executarTreinamento( Corpus &corpus, int atributo )
{
    int c, a, numeroClasses, numeroAtributos, e;
    ofstream names, data;
    ifstream tree;
    vector<int> indexes;
    vector<string> linhasArquivo;
    string linha;

    //gera arquivo .names
    names.open("c50temp.names");

    numeroClasses = classes.size();
    for (c=0;c<numeroClasses;c++){
        names << classes[c];
        if (c!=numeroClasses-1)
            names << ", ";
        else
            names << "." << endl << endl;
    }

    numeroAtributos = atributos.size();
    for (a=0;a<numeroAtributos;a++){
        names << atributos[a];
        names << ": continuous." << endl;
        indexes.push_back(corpus.pegarPosAtributo(atributos[a]));
    }

    names.close();

    //gera data
    data.open("c50temp.data");
    for (c=0;c<corpus.pegarQtdConjExemplos();c++)
        for (e=0;e<corpus.pegarQtdExemplos(c);e++){
            for (a=0;a<numeroAtributos;a++)
                data << corpus(c,e,a) << ", ";
            data << corpus(c,e,atributo) << endl;
        }
    data.close();

    //chama função
    c50train("c50temp", cf);

    //carrega .tree
    tree.open("c50temp.tree");
    while (!tree.eof()){
        getline(tree,linha);
        linhasArquivo.push_back(linha);
        //cout << linha << endl;
    }
    tree.close();

    C50Classificador *cl = new C50Classificador();
    cl->linhasArquivo = linhasArquivo;
    cl->atributos = atributos;
    cl->classes = classes;

    return cl;
}
