#ifndef TREINADOR_STUMP_H
#define TREINADOR_STUMP_H

#include "treinador/treinador_distribuicao.h"
#include <set>

class DecisionStump : public TreinadorDistribuicao {
    protected:
		string positivo, negativo;
		double Entropia(double mais, double menos);
        set<string> desconsiderar;
    public:
        DecisionStump(vector<double> *dist = NULL, set<string> desconsiderar = set<string>())
            : TreinadorDistribuicao(dist), desconsiderar(desconsiderar) {}
        DecisionStump(string positivo, string negativo, vector<double> *dist = NULL, set<string> desconsiderar = set<string>())
            : TreinadorDistribuicao(dist), positivo(positivo), negativo(negativo), desconsiderar(desconsiderar) {}
		Classificador* executarTreinamento(Corpus &corpus, int atributo);
};

#endif
