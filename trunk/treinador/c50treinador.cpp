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
    string linha,val;
    ifstream tree;
    ofstream names, data;
    vector<int> indexes;
    vector<string> linhasArquivo, valores;
    vector< vector<string> > valoresPossiveis;
    int c, a, numeroClasses, numeroAtributos, e, v, numeroValores;

    //gera arquivo .names
    names.open("c50tempT.names");

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
        names << atributos[a] << ": ";
        if (corpus.discreto(atributos[a],valores)){
            numeroValores = valores.size();
            for (v=0;v<numeroValores;v++){
                if (valores[v]=="")
                    names << "?";
                else
                    names << removeVirgula(valores[v]);
                if (v!=numeroValores-1)
                    names << ", ";
                else
                    names << "." << endl;
            }
        }
        else{
            names << "continuous." << endl;
            valores.clear();
            valores.push_back("continuous");
        }
        valoresPossiveis.push_back(valores);
        indexes.push_back(corpus.pegarPosAtributo(atributos[a]));
    }
    names.close();

    //gera data
    data.open("c50tempT.data");
    for (c=0;c<corpus.pegarQtdConjExemplos();c++)
        for (e=0;e<corpus.pegarQtdExemplos(c);e++){
            for (a=0;a<numeroAtributos;a++){
                val = corpus(c,e,indexes[a]);
                if (val=="")
                    data << "?, ";
                else
                    data << removeVirgula(val) << ", ";
            }
            data << corpus(c,e,atributo) << endl;
        }
    data.close();
    //chama função
    c50train("c50tempT", cf);

    //carrega .tree
    tree.open("c50tempT.tree");
    while (!tree.eof()){
        getline(tree,linha);
        linhasArquivo.push_back(linha);

    }
    tree.close();

    C50Classificador *cl = new C50Classificador();
    cl->linhasArquivo = linhasArquivo;
    cl->atributos = atributos;
    cl->valoresPossiveis = valoresPossiveis;
    cl->classes = classes;

    return cl;
}
