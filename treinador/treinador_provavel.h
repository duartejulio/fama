#ifndef TREINADOR_PROVAVEL_H
#define TREINADOR_PROVAVEL_H

#include "../corpus/corpus.h"
#include "treinador.h"
#include "../classificador/classificador_provavel.h"

#include <vector>
using namespace std;

class TreinadorProvavel: public Treinador {
	vector<bool> *considerar;
	string unknown;
public:
    TreinadorProvavel(string un = "Desconhecido"): considerar(0), unknown(un) {}
    TreinadorProvavel(vector<bool> *considerar, string un = "Desconhecido"): considerar(considerar), unknown(un){}
    ~TreinadorProvavel() {delete considerar;}
    Classificador* executarTreinamento(Corpus &corpus, int atributo);
};

#endif
