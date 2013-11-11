#include "c50classificador.h"

#include <fstream>

extern "C" int c50classif(char* baseFileName);

C50Classificador::C50Classificador()
{
}

bool C50Classificador::executarClassificacao( Corpus &corpus, int atributo)
{
    //gerar .data e .names
    int c, a, numeroClasses, numeroAtributos, e;
    ofstream names, data;
    ifstream tree, out;
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

    //gera cases
    data.open("c50temp.cases");
    for (c=0;c<corpus.pegarQtdConjExemplos();c++)
        for (e=0;e<corpus.pegarQtdExemplos(c);e++){
            for (a=0;a<numeroAtributos;a++)
                data << corpus(c,e,a) << ", ";
            data << "?" << endl;
        }
    data.close();

    //grava arvore
    gravarConhecimento("c50temp.tree");

    //chamar funcao see
    c50classif("c50temp");

    //carregar valores encontrados
    out.open("c50temp.out");

    for (c=0;c<corpus.pegarQtdConjExemplos();c++)
        for (e=0;e<corpus.pegarQtdExemplos(c);e++){
            out >> linha;
            corpus(c,e,atributo, linha);
            //cout << linha << endl;
        }
    out.close();

}

bool C50Classificador::gravarConhecimento( string arquivo )
{
    ofstream tree;
    int tam, i;


    tree.open(arquivo.c_str());

    tam = linhasArquivo.size();
    for (i=0; i<tam; i++)
        tree << linhasArquivo[i] << endl;

    tree.close();

    return true;
}

bool C50Classificador::carregarConhecimento( string arquivo )
{
    ifstream tree;
    string linha;

    linhasArquivo.clear();

    tree.open(arquivo.c_str());
    while (!tree.eof()){
        getline(tree,linha);
        linhasArquivo.push_back(linha);
    }
    tree.close();

    return true;
}
