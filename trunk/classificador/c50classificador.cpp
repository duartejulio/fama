#include "c50classificador.h"

#include <fstream>
#include <sstream>

extern "C" int c50classif(char* baseFileName);
extern "C" void printTree(char* baseFileName);

string removeVirgula(string val){
    int i, tam;
    string retorno = "";

    tam = val.size();

    for (i=0;i<tam;i++){
        if (val[i]==',')
            retorno += "\\,";
        else
        if (val[i]==':')
            retorno += "\\:";
        else
        if (val[i]==' ')
            retorno += "?";
        else
            retorno += val[i];
    }

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
    vector<string> valores;
    string linha,val;
    int c, a, numeroClasses, numeroAtributos, e, v, numeroValores;

    //gera arquivo .names
    names.open("c50temp.names");

    numeroClasses = classes.size();
    for (c=0; c<numeroClasses; c++){
        names << classes[c];
        if (c!=numeroClasses-1)
            names << ", ";
        else
            names << "." << endl << endl;
    }

    numeroAtributos = atributos.size();
    for (a=0; a < numeroAtributos; a++){
        names << atributos[a] << ": ";

        valores = valoresPossiveis[a];

        numeroValores = valores.size();
        for (v=0; v < numeroValores; v++){
            if (valores[v]=="")
                names << "?";
            else
                names << removeVirgula(valores[v]);
            if (v!=numeroValores-1)
                names << ", ";
            else
                names << "." << endl;
        }

        indexes.push_back(corpus.pegarPosAtributo(atributos[a]));
    }
    names.close();

    //gera cases
    data.open("c50temp.cases");
    for (c=0; c<corpus.pegarQtdConjExemplos(); c++)
        for (e=0; e<corpus.pegarQtdExemplos(c); e++){
            for (a=0; a<numeroAtributos; a++){
                val = corpus(c, e, indexes[a]);
                if (val=="")
                    data << "?, ";
                else
                    data << removeVirgula(val) << ", ";
            }
            data << "?" << endl;
        }
    data.close();

    //grava arvore
    gravarArvore("c50temp.tree");

    //chamar funcao see
    c50classif("c50temp");

    //carregar valores encontrados
    out.open("c50temp.out");

    for (c=0; c<corpus.pegarQtdConjExemplos(); c++)
        for (e=0; e<corpus.pegarQtdExemplos(c); e++){
            getline(out, linha);
            corpus(c, e, atributo, linha);
        }

    out.close();

    return true;
}

bool C50Classificador::gravarConhecimento( string arquivo )
{
    ofstream arq;
    int tam, i, j, tam2;

    arq.open(arquivo.c_str());

    tam = classes.size();
    arq << tam << endl;
    for (i=0; i<tam; i++)
        arq << classes[i] << endl;

    tam = atributos.size();
    arq << tam << endl;
    for (i=0; i<tam; i++){
        arq << atributos[i] << endl;
        tam2 = valoresPossiveis[i].size();
        arq << tam2 << endl;
        for (j=0; j<tam2; j++)
            arq << valoresPossiveis[i][j] << endl;
    }

    tam = linhasArquivo.size();
    for (i=0; i<tam; i++)
        arq << linhasArquivo[i] << endl;

    arq.close();

    return true;

}

bool C50Classificador::gravarArvore( string arquivo )
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
    ifstream arq;
    string linha;
    int i, j, tam, tam2;

    linhasArquivo.clear();

    arq.open(arquivo.c_str());

    classes.clear();
    arq >> tam;getline(arq,linha);

    for (i=0; i<tam; i++){
        getline(arq,linha);
        classes.push_back(linha);
    }

    atributos.clear();
    valoresPossiveis.clear();
    arq >> tam;getline(arq,linha);

    for (i=0; i<tam; i++){
        getline(arq,linha);
        atributos.push_back(linha);
        arq >> tam2;getline(arq,linha);

        valoresPossiveis.push_back(vector<string>());
        for (j=0; j<tam2; j++){
            getline(arq,linha);
            valoresPossiveis[i].push_back(linha);
        }
    }

    while (!arq.eof()){
        getline(arq,linha);
        linhasArquivo.push_back(linha);
    }
    arq.close();

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
