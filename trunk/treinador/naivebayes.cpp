#include "naivebayes.h"

#include <cmath>
#include <sstream>

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
