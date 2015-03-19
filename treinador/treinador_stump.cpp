#include "treinador_stump.h"
#include "../corpus/corpus.h"
#include "../classificador/classificador_stump.h"

#include <cmath>

Classificador* DecisionStump::executarTreinamento(Corpus& corpus, int atributo)
{
    //z = numero de ajuste entre um vector bidimencional do corpus com uma distrubuicao unidimensional
    unsigned int z = 0, qtdeExemplos = corpus.pegarQtdTotalExemplos();
    if (distribuicao == NULL) {
        double defaultValue = (double)1.0/qtdeExemplos;
		distribuicao = new vector<double>(qtdeExemplos, defaultValue);
    }
	else
	{
		if (qtdeExemplos != distribuicao->size())
		{
			cout << "ERRO! O Vetor distribuição não tem o mesmo tamanho do que o conjunto de exemplos!" << endl;
			return NULL;
		}
	}
	double entrop = 0.0, pMais = 0.0, pMenos = 0.0;
	for(int i = 0; i < corpus.pegarQtdSentencas(); i++) {
        for (int j = 0; j < corpus.pegarQtdTokens(i); j++) {
            const string &str = corpus(i, j, atributo);
            if (positivo.empty()) {
                positivo = str;
            }
            else if (negativo.empty() && str != positivo) {
                negativo = str;
            }
            if (str == positivo) {
                pMais += distribuicao->at(z++);
            } else if (str == negativo) {
                pMenos += distribuicao->at(z++);
			} else {
                cout << "ERRO! A classe escolhida tem mais de dois atributos!" << endl
                     << "Terceiro atributo encontrado: " << str << endl;
				return NULL;
			}
		}
	}
    entrop = Entropia(pMais, pMenos);

	map<string, int> *values, *maxValues = NULL;
    vector<double> *pMaisV, *pMenosV, *maxMaisV, *maxMenosV;
    int maxAtr = 0, numAtr; double maxGanho = 0.0, ganho;
    for (int att = 0; att < corpus.pegarQtdAtributos(); att++) {
        if (att == atributo)
            continue;
        values = new map<string, int>;
        pMaisV = new vector<double>;
        pMenosV = new vector<double>;
		z = 0;
		for(int i = 0; i < corpus.pegarQtdSentencas(); i++) {
            for (int j = 0; j < corpus.pegarQtdTokens(i); j++) {
                map<string, int>::iterator it = values->find(corpus(i, j, att));
                if (it == values->end()) {
                    numAtr = values->size();
                    values->insert(pair<string, int>(corpus(i, j, att), numAtr));
					pMaisV->push_back(0.0);
					pMenosV->push_back(0.0);
                } else {
                    numAtr = it->second;
                }
                if(corpus(i, j, atributo) == positivo) {
                    pMaisV->at(numAtr) += distribuicao->at(z++);
				} else {
                    pMenosV->at(numAtr) += distribuicao->at(z++);
				}
			}
		}
        ganho = entrop;
        for(unsigned int i = 0; i < pMaisV->size(); i++) {
            ganho -= Entropia(pMaisV->at(i), pMenosV->at(i))*(pMaisV->at(i) + pMenosV->at(i));
		}
        if (ganho > maxGanho) {
			maxAtr = att;
			maxGanho = ganho;
			if (maxValues != NULL) {
				delete maxValues;
				delete maxMaisV;
				delete maxMenosV;
			}
			maxValues = values;
			maxMaisV = pMaisV;
			maxMenosV = pMenosV;
		} else {
            if (maxValues == NULL) {
                maxValues = values;
                maxMaisV = pMaisV;
                maxMenosV = pMenosV;
            }
            else {
                delete values;
                delete pMaisV;
                delete pMenosV;
            }
		}
    }
    map<string, int> resultado;
    for (map<string, int>::iterator it = maxValues->begin(); it != maxValues->end(); ++it) {
        resultado[it->first] = (maxMaisV->at(it->second) > maxMenosV->at(it->second)) ? 1 : -1;
    }

    //this->setarDistribuicao(NULL);

	//Construir o classificador agora
    return new ClassificadorStump(resultado, positivo, negativo, corpus.pegarAtributo(maxAtr), (pMais > pMenos) ? 1 : -1);
}

double DecisionStump::Entropia(double mais, double menos) {
    return -(mais*log2(mais) + menos*log2(menos));
}
