#ifndef KNN_H
#define KNN_H

#include "treinador.h"
#include "../classificador/classificadorknn.h"

class TreinadorKNN : public Treinador
{
    vector<string> atributos;
    vector<string> classes;
    bool usarPesos;
    int K;
    int removerExemplosCorretos;
    int NATTRS;
public:
    TreinadorKNN(vector<string> atributos, vector<string> classes, bool usarPesos = false, int K = 5, int removerExemplosCorretos = 2):
     atributos(atributos), classes(classes), usarPesos(usarPesos), K(K), removerExemplosCorretos(removerExemplosCorretos), NATTRS(NATTRS){
        NATTRS = atributos.size();
    }

    virtual ~TreinadorKNN(){}
    Classificador* executarTreinamento( Corpus &corpus, int atributo );
};

#endif // KNN_H
