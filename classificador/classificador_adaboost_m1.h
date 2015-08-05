#include "classificador.h"
#include "treinador/treinador.h"
#include "treinador/treinador_adaboost_m1.h"

#ifndef CLASSIFICADORADABOOSTM1_H
#define CLASSIFICADORADABOOSTM1_H

class ClassificadorAdaboostM1 : public Classificador
{
protected:
    vector<string> valores;
    vector<Classificador*> classificadores;
    vector<double> betas;
public:
    ClassificadorAdaboostM1(vector<string> valores, vector<Classificador*> classificadores, vector<double> betas)
        : valores(valores), classificadores(classificadores), betas(betas) {}
    virtual ~ClassificadorAdaboostM1();
    virtual bool executarClassificacao( Corpus &corpusProva, int atributo );
    virtual bool gravarConhecimento( string arquivo );
    virtual bool carregarConhecimento( string arquivo );
    virtual string descricaoConhecimento ();
};

#endif // CLASSIFICADORADABOOSTM1_H
