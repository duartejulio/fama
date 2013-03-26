#include "processadorlog.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include<cmath>

using namespace std;

ProcessadorLogaritmo::ProcessadorLogaritmo(vector<string> atr,int b){
    numatributos = atr.size();

   atributo = atr;

    this->b=b;
}

ProcessadorLogaritmo::~ProcessadorLogaritmo(){
}

void ProcessadorLogaritmo::criarAtributos(Corpus &objCorpus){
    novosAtributos.clear();
    for(int i=0; i< numatributos; i++)
    {

        objCorpus.criarAtributo("log"+atributo[i],"0");
        novosAtributos.push_back("log"+atributo[i]);
    }

}

vector<string> ProcessadorLogaritmo::processarCorpus(Corpus &objCorpus)
{

    int totlinhas, qtdConjExemplos,c;
    int  idCol, linha;
    int *indices;
    indices = new int[numatributos];

    for(int i=0; i<numatributos; i++)
        indices[i] = objCorpus.pegarPosAtributo(atributo[i]);

    criarAtributos(objCorpus);

    idCol = objCorpus.pegarPosAtributo("log"+atributo[0]);

    qtdConjExemplos = objCorpus.pegarQtdConjExemplos();
    for (c=0; c<qtdConjExemplos; c++){
        totlinhas = objCorpus.pegarQtdExemplos(c);

        for (linha=0; linha < totlinhas; linha++){

                for( int i=0; i<numatributos; i++)
                {
                        int  vatual= objCorpus.pegarValor(c,linha,indices[i]);
                        float valor_atual;
                        (std::istringstream)(objCorpus.pegarSimbolo(vatual)) >> valor_atual >> std::dec;
                        float logatual = log(valor_atual)/log(b);
                        std::stringstream out2;
                        out2 << setprecision(3) << setiosflags(ios::fixed);
                        out2 << logatual;
                        objCorpus.ajustarValor(c, linha, idCol+i, objCorpus.pegarIndice(out2.str()));
                }


            }
        }


    return novosAtributos;

}
