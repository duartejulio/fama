#ifndef CLASSIFICADOR_ADABOST_H
#define CLASSIFICADOR_ADABOST_H

#include "classificador.h"

class ClassificadorAdaboost : public Classificador
{
protected:
    vector<string> classes;
    vector<Classificador*> classificadores;
    vector<double> alphas;
public:
    ClassificadorAdaboost(vector<string> classes, vector<Classificador*> classificadores, vector<double> alphas)
        : classes(classes), classificadores(classificadores), alphas(alphas) {}
    ~ClassificadorAdaboost(){
    }
    bool executarClassificacao( Corpus &corpusProva, int atributo );
    bool gravarConhecimento( string arquivo );
    bool carregarConhecimento( string arquivo );
    string descricaoConhecimento ();
};




#endif // CLASSIFICADOR_ADABOST_H
