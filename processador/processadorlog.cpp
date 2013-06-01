#include "processadorlog.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include<cmath>

using namespace std;

ProcessadorLogaritmo::ProcessadorLogaritmo(vector<string> atr,int b, float normalizador){
    numatributos = atr.size();
   atributo = atr;
    this->b=b;
    this->normalizador = normalizador;
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


void ProcessadorLogaritmo::normalizarCorpus(Corpus &objCorpus)
{
    int qtdConjExemplos, totlinhas, linha, c, idCol;
    idCol = objCorpus.pegarPosAtributo("log"+atributo[0]);

    qtdConjExemplos = objCorpus.pegarQtdConjExemplos();

    cout<<maxvalor<<endl;
    cout<<minvalor<<endl;
    for (c=0; c<qtdConjExemplos; c++){
        totlinhas = objCorpus.pegarQtdExemplos(c);

        for (linha=0; linha < totlinhas; linha++){

                for( int i=0; i<numatributos; i++)
                {
                        int  vatual= objCorpus.pegarValor(c,linha,i+idCol);
                        float valor_atual;
                        (std::istringstream)(objCorpus.pegarSimbolo(vatual)) >> valor_atual>>std::dec;
                         cout<<valor_atual<<endl;
                        //para normalizar
                            valor_atual = normalizador *(valor_atual - minvalor)/(maxvalor - minvalor);

                        std::stringstream out2;
                        out2 << setprecision(0) << setiosflags(ios::fixed);

                        out2 << valor_atual;
                        objCorpus.ajustarValor(c, linha, idCol+i, objCorpus.pegarIndice(out2.str()));
                }


            }
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
                        float logatual=0;
                        if(valor_atual !=0 )
                        logatual = log(valor_atual)/log(b);
                        std::stringstream out2;
                        out2 << setprecision(0) << setiosflags(ios::fixed);
                        out2 << logatual;
                        objCorpus.ajustarValor(c, linha, idCol+i, objCorpus.pegarIndice(out2.str()));

                            //para normalizar
                            if(linha ==0 && c ==0 && i==0)
                            { minvalor = logatual;
                                maxvalor = logatual;
                            }
                            else{
                            if(logatual<minvalor)
                            minvalor = logatual;
                            if(logatual> maxvalor)
                            maxvalor = logatual;
                            }

                }


            }
        }

    return novosAtributos;

}
