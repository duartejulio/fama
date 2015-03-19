#ifndef TREINADOR_STUMP_H
#define TREINADOR_STUMP_H

#include "treinador/treinador_distribuicao.h"

class DecisionStump : public TreinadorDistribuicao {
    protected:
		string positivo, negativo;
		double Entropia(double mais, double menos);
	public:
        DecisionStump(vector<double> *dist = NULL) : TreinadorDistribuicao(dist) {}
        DecisionStump(string positivo, string negativo, vector<double> *dist = NULL) :
            TreinadorDistribuicao(dist), positivo(positivo), negativo(negativo) {}
		Classificador* executarTreinamento(Corpus &corpus, int atributo);
};

#endif
