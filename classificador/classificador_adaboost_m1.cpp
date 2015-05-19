#include "classificador_adaboost_m1.h"
#include <cmath>


ClassificadorAdaboostM1::~ClassificadorAdaboostM1()
{
    for (int i = 0; i < classificadores.size(); i++)
        delete classificadores[i];
}

bool ClassificadorAdaboostM1::executarClassificacao( Corpus &corpusProva, int atributo ) {
    vector<vector<double> > exemplos(corpusProva.pegarQtdTotalExemplos(), vector<double>(valores.size(), 0.0d));
    int k, indice;
    for (int t = 0; t < classificadores.size(); t++) {
        (classificadores[t])->executarClassificacao(corpusProva, atributo);
        k = 0;
        for (int i = 0; i < corpusProva.pegarQtdSentencas(); i++) {
            for (int j = 0; j < corpusProva.pegarQtdExemplos(i); j++) {
                indice = -1;
                for (int a = 0; a < valores.size() - 1; a++)
                    if (valores[a] == corpusProva(i, j, atributo)) {
                        indice = a;
                        a = valores.size();
                    }
                if (indice == -1)
                    indice = valores.size() - 1;
                exemplos[k][indice] -= log(betas[t]);
                k++;
            }
        }
    }
    double maxBeta; int maxAtr;
    k = 0;
    for (int i = 0; i < corpusProva.pegarQtdSentencas(); i++) {
        for (int j = 0; j < corpusProva.pegarQtdExemplos(i); j++) {
            maxBeta = exemplos[k][valores.size()-1];
            maxAtr = valores.size() - 1;
            for (int a = 0; a < valores.size() - 1; a++) {
                if (maxBeta <= exemplos[k][a]) {
                    maxBeta = exemplos[k][a];
                    maxAtr = a;
                }
            }
            corpusProva(i, j, atributo, valores[maxAtr]);
            k++;
        }
    }
}

bool ClassificadorAdaboostM1::gravarConhecimento( string arquivo ) {
    return false;
}

bool ClassificadorAdaboostM1::carregarConhecimento( string arquivo ) {
    return false;
}

string ClassificadorAdaboostM1::descricaoConhecimento () {
    return "Classificador com base no meta-algoritmo AdaBoost M1";
}
