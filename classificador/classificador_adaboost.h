#ifndef CLASSIFICADORADABOOST_H
#define CLASSIFICADORADABOOST_H

#include "classificador.h"
#include "treinador/treinador_adaboost.h"
#include "classificador_duasclasses.h"

class ClassificadorAdaBoost : public Classificador {
protected:
    vector<ClassificadorDuasClasses*> baseClassifier;
    vector<double> alpha;
    string positivo, negativo;
public:
    ClassificadorAdaBoost(vector<ClassificadorDuasClasses*> classificadores, vector<double> alpha, string pos, string neg)
        : Classificador(), baseClassifier(classificadores), alpha(alpha), positivo(pos), negativo(neg) {}
    virtual ~ClassificadorAdaBoost();
    virtual bool executarClassificacao( Corpus &corpusProva, int atributo );
    //virtual vector<vector<string> > executarAlgoritmo (Corpus &corpus);
    virtual bool gravarConhecimento( string arquivo );
    virtual bool carregarConhecimento( string arquivo );
};

#endif // CLASSIFICADORADABOOST_H
