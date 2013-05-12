#include "processadorattdisc.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <cstring>


using namespace std;

ProcessadorAttDisc::ProcessadorAttDisc(vector<string> atr){
    numatributos = atr.size();
   atributo = atr;
}

ProcessadorAttDisc::~ProcessadorAttDisc(){
}


void ProcessadorAttDisc::criarAtributos(Corpus &objCorpus){

    for(int i=0; i< numatributos; i++)
    {
        objCorpus.criarAtributo("New"+atributo[i],"0");
    }

}


bool ProcessadorAttDisc::processarCorpus(Corpus &objCorpus)
{

    int totlinhas, qtdConjExemplos,c;
    int  idCol, linha;
    int *indices;
    indices = new int[numatributos];

    for(int i=0; i<numatributos; i++)
    {
            indices[i] = objCorpus.pegarPosAtributo(atributo[i]);
    }

    criarAtributos(objCorpus);

    idCol = objCorpus.pegarPosAtributo("New"+atributo[0]);

    qtdConjExemplos = objCorpus.pegarQtdConjExemplos();
    for (c=0; c<qtdConjExemplos; c++){
        totlinhas = objCorpus.pegarQtdExemplos(c);

        for (linha=0; linha < totlinhas; linha++){

                for( int i=0; i<numatributos; i++)
                {
                        int  vatual= objCorpus.pegarValor(c,linha,indices[i]);
                        string valor_atual = objCorpus.pegarSimbolo(vatual);
                       int logatual=0;
                        if(valor_atual == "VERDADEIRO" )
                        logatual = 1;
                        std::stringstream out2;
                        out2 << setprecision(0) << setiosflags(ios::fixed);
                        out2 << logatual;
                        objCorpus.ajustarValor(c, linha, idCol+i, objCorpus.pegarIndice(out2.str()));


                }


            }
        }


    return true;

}
