#include "naivebayes.h"

#include <cmath>
#include <sstream>

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
    int a, e, c, cl, nExemplos, nConjExemplos, nAtributos, gcl, nClasses, i, v, iClasse;
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

//    ret << "Se " << atributo << " = " << valor << " então " << classe << endl;
//    ret << "Caso contrário então " << ((classe==classes[0])?classes[1]:classes[0]) << endl;
    return ret.str();
}


NaiveBayes::NaiveBayes(vector<string> atr, vector<string> cla):Treinador(){
    //guarda parametros
    atributos = atr;
    classes = cla;
}

Classificador* NaiveBayes::executarTreinamento( Corpus &corpus, int atributo ){
    unsigned int nExemplos, nConjExemplos, nAtributos,
     i, a, e, c, v, iClasse;

    vector<int> indices, count;
    vector< vector < float > > medias, desvio;
    map <int, int> mapaClasses;
    float val;

    //determina números de conjuntos de exemplos e atributos
    nConjExemplos = corpus.pegarQtdConjExemplos();
    nAtributos = atributos.size();

    medias.resize(classes.size());
    desvio.resize(classes.size());
    //determina valores das classes no dicionario
    for (i=0; i<classes.size();i++){
        mapaClasses[corpus.pegarIndice(classes[i])] = i;
        count.push_back(0);
        for (a=0; a<nAtributos;a++){
            medias[i].push_back(0.0);
            desvio[i].push_back(0.0);
        }
    }


    for (c=0; c < nConjExemplos; c++){
        nExemplos = corpus.pegarQtdExemplos(c);
        for (e=0; e < nExemplos; e++){
            iClasse = mapaClasses[corpus.pegarValor(c, e, atributo)];
            count[iClasse]++;
            for (a=0; a<nAtributos;a++){
                i = corpus.pegarPosAtributo(atributos[a]);
                v = corpus.pegarValor(c, e, i);
                (std::istringstream)(corpus.pegarSimbolo(v)) >> val >> std::dec;//converte para float
                //cout << "E:" << iClasse << " " << a << " " << val << "\n";
                //cout << "A:" << medias[iClasse][a] << "\n";
                medias[iClasse][a] += val;
                //cout << "A:" << medias[iClasse][a] << "\n";
            }
        }
    }

    for (i=0; i<classes.size();i++){
        for (a=0; a<nAtributos;a++){
            //cout << "M*:" << medias[i][a] << " " << count[i] <<"\n";
            medias[i][a] /= count[i];
            //cout << "M:" << medias[i][a] << "\n";
        }
        //cout << "\n";
    }

    for (c=0; c < nConjExemplos; c++){
        nExemplos = corpus.pegarQtdExemplos(c);
        for (e=0; e < nExemplos; e++){
            iClasse = mapaClasses[corpus.pegarValor(c, e, atributo)];
            count[iClasse]++;
            for (a=0; a<nAtributos;a++){
                i = corpus.pegarPosAtributo(atributos[a]);
                v = corpus.pegarValor(c, e, i);
                (std::istringstream)(corpus.pegarSimbolo(v)) >> val >> std::dec;//converte para float
                //cout << "E:" << iClasse << " " << a << " " << val << "\n";
                //cout << "A:" << medias[iClasse][a] << "\n";
                desvio[iClasse][a] += (val - medias[iClasse][a])*(val - medias[iClasse][a]);
                //cout << "A:" << medias[iClasse][a] << "\n";
            }
        }
    }

    for (i=0; i<classes.size();i++){
        for (a=0; a<nAtributos;a++){
            //cout << "M*:" << medias[i][a] << " " << count[i] <<"\n";
            desvio[i][a] /= count[i];
            desvio[i][a] = sqrt(desvio[i][a]);
            //cout << "D:" << desvio[i][a] << "\n";
        }
        //cout << "\n";
    }

    return new ClassificadorNB(classes, atributos, medias, desvio, count);
}
