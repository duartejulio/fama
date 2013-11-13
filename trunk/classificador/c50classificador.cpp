#include "c50classificador.h"

#include <fstream>
#include <sstream>

extern "C" int c50classif(char* baseFileName);
extern "C" void printTree(char* baseFileName);

string removeVirgula(string val){
    int i, tam;
    bool vazio = true;
    string retorno = val;

    tam = retorno.size();

    for (i=0;i<tam;i++){
        if (retorno[i]==',')
            retorno[i] = ';';
        if (retorno[i]=='.')
            retorno[i] = '!';
        if (retorno[i]==':')
            retorno[i] = '{';

        if (retorno[i]!=' ')
            vazio = false;
    }
    if (vazio)
        for (i=0;i<tam;i++)
            retorno[i] = '?';
    return retorno;

}

C50Classificador::C50Classificador()
{
}

bool C50Classificador::executarClassificacao( Corpus &corpus, int atributo)
{
    //gerar .data e .names
    ofstream names, data;
    ifstream tree, out;
    vector<int> indexes;
    vector<string> linhasArquivo, valores;
    string linha,val;
    int c, a, numeroClasses, numeroAtributos, e, v, numeroValores;

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
        else
            names << "continuous." << endl;
        indexes.push_back(corpus.pegarPosAtributo(atributos[a]));
    }

    names.close();

    //gera cases
    data.open("c50temp.cases");
    for (c=0;c<corpus.pegarQtdConjExemplos();c++)
        for (e=0;e<corpus.pegarQtdExemplos(c);e++){
            for (a=0;a<numeroAtributos;a++){
                val = corpus(c,e,indexes[a]);
                if (val=="")
                    data << "?, ";
                else
                    data << removeVirgula(val) << ", ";
            }
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
            getline(out,linha);
            corpus(c,e,atributo, linha);
        }
    out.close();

    return true;
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

string C50Classificador::descricaoConhecimento(){
    stringstream tree;
    int tam, i;

    tam = linhasArquivo.size();
    for (i=1; i<tam; i++)
        tree << linhasArquivo[i] << endl;

    return tree.str();
}
