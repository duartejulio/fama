#ifndef KNN_H
#define KNN_H

#include "treinador.h"
#include "../classificador/classificadorknn.h"

class TreinadorKNN : public Treinador
{
    vector<string> atributos;
    vector<string> classes;
    bool usarPesos;
    int K, NATTRS, MAXVALUE;

public:
    TreinadorKNN(vector<string> atributos, vector<string> classes, bool usarPesos = false, int K = 5, int MAXVALUE = 10000.0):
     atributos(atributos), classes(classes), usarPesos(usarPesos), K(K), NATTRS(NATTRS), MAXVALUE(MAXVALUE){
        NATTRS = atributos.size();
    }

    virtual ~TreinadorKNN(){}
    Classificador* executarTreinamento( Corpus &corpus, int atributo );
};

#endif // KNN_H
