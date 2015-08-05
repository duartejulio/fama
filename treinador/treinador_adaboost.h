#ifndef TREINADOR_ADABOOST_H
#define TREINADOR_ADABOOST_H

#include "treinador/treinador.h"
#include "treinador/treinador_distribuicao.h"
#include "avaliador/avaliador_ce.h"
#include "classificador/classificador.h"
#include "classificador/classificador_duasclasses.h"
#include "corpus/corpus.h"
#include <cmath>

class TreinadorAdaBoost : public Treinador {
protected:
    TreinadorDistribuicao *weakTrainner;
    int iterations;
    double littleAlpha;
    double calcularErro(Corpus& corpus, int atributo, vector<vector<int> > &classificacao, vector<double> *dist);
    string positivo, negativo;
public:
    ///
    /// \brief Construtor do AdaBoost.
    /// \param weak Weak Learner associado ao AdaBoost.
    /// \param it Número de iterações.
    ///
    TreinadorAdaBoost(TreinadorDistribuicao *weak, int it = 10, double littleAlpha = 0.1e-100d)
        : Treinador(), weakTrainner(weak), iterations(it), littleAlpha(littleAlpha) {}
    virtual ~TreinadorAdaBoost() {delete weakTrainner;}
    virtual Classificador *executarTreinamento( Corpus &corpus, int atributo );

};
#endif
