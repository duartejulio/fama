#include "classificadornb.h"

#include <cmath>
#include <sstream>
#include <iomanip>
#include <iostream>

#define PI 4*atan(1)

ClassificadorNB::ClassificadorNB(vector<string> clas, vector<string> atr,
                                 vector< vector < float > > medi, vector< vector < float > > desv,
                                 vector < int > coun):Classificador(){
    //guarda parametros
    classes = clas;
    atributos = atr;
    medias = medi;
    desvio = desv;
    count = coun;
}

bool ClassificadorNB::executarClassificacao( Corpus &corpus, int atributo ){
    int a, e, c, cl, nExemplos, nConjExemplos, nAtributos, gcl = 0, nClasses, i, v, iClasse;
    map <int, int> mapaClasses;
    float prod, maxprod, val;

    //determina tamanho do conjunto
    nConjExemplos = corpus.pegarQtdConjExemplos();
    nAtributos = atributos.size();
    nClasses = classes.size();

    //varre os exemplos
    for (c=0; c < nConjExemplos; c++){
        nExemplos = corpus.pegarQtdExemplos(c);
        for (e = 0; e < nExemplos; e++){
            maxprod = -1;
            for (cl=0; cl < nClasses;cl++){

                prod = count[cl];
                for (a=0; a < nAtributos; a++){
                    i = corpus.pegarPosAtributo(atributos[a]);
                    v = corpus.pegarValor(c, e, i);
                    (std::istringstream)(corpus.pegarSimbolo(v)) >> val >> std::dec;//converte para float
                    prod *= (1.0/(desvio[cl][a]*sqrt(2*PI)))*
                            exp(-(val-medias[cl][a])*(val-medias[cl][a])/(2*desvio[cl][a]*desvio[cl][a]));
                }
               // cout << "P:" << maxprod << " " << prod << endl;
                if (prod > maxprod){
                    maxprod = prod;
                    gcl = cl;
                }
            }

            iClasse = corpus.pegarIndice(classes[gcl]);
            corpus.ajustarValor(c,e,atributo,iClasse);
            //cout << gcl << " " << iClasse << " " << classes[gcl] << "\n";
        }
    }
    return true;
}

string ClassificadorNB::descricaoConhecimento(){
    ostringstream ret;
    int c, a, nAtributos, nClasses, soma;
    vector <float> priori;

    nClasses = classes.size();
    nAtributos = atributos.size();

    priori.resize(nClasses);

    for (soma = 0, c = 0; c < nClasses; c++)
        soma += count[c];

    for (c = 0; c < nClasses; c++)
        priori[c] = count[c]/(float)soma;

    ret << setprecision(4);
    ret << "---------------------------------------------------------------" << endl;
    ret << "| " << setiosflags(ios::left) << setw(15) << "Classe/Priori";
    ret << "| " << setiosflags(ios::left) << setw(15) << "Atributo";
    ret << "| " << setiosflags(ios::left) << setw(10) << "Média";
    ret << "| " << setiosflags(ios::left) << setw(14) << "Desvio Padrão" << "| " << endl;

    ret << "---------------------------------------------------------------" << endl;
    for (c = 0; c < nClasses; c++){
        for (a=0; a < nAtributos; a++){
            if (a)
                ret << "| " << setiosflags(ios::left) << setw(15) << " ";
            else
                ret << "| " << setiosflags(ios::left) << setw(9) <<
                 classes[c] << setw(6) << priori[c];
            ret << "| " << setiosflags(ios::left) << setw(15) << atributos[a];
            ret << "| " << setiosflags(ios::left) << setw(10) << medias[c][a];
            ret << "| " << setiosflags(ios::left) << setw(14) << desvio[c][a];
            ret << "| " << setiosflags(ios::left) << endl;
        }
    }
    ret << "---------------------------------------------------------------" << endl;

    return ret.str();
}
