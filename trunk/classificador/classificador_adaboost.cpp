#include "classificador_adaboost.h"
#include "classificador/classificador_stump.h"
#include <sstream>
#include <fstream>
#include <string>
#include <typeinfo>

ClassificadorAdaBoost::~ClassificadorAdaBoost()
{
    for(int k = 0; k < baseClassifier.size(); k++)
        delete baseClassifier.at(k);
}

bool ClassificadorAdaBoost::executarClassificacao(Corpus &corpusProva, int atributo) {
    vector<double> valores(corpusProva.pegarQtdTotalExemplos(),0.0);
    int k;
    for (int t = 0; t < alpha.size(); t++) {
        vector<vector<int> > algoritmo = (baseClassifier[t])->executarAlgoritmo(corpusProva);
        k = 0;
        for (int i = 0; i < corpusProva.pegarQtdSentencas(); i++) {
            for (int j = 0; j < corpusProva.pegarQtdTokens(i); j++) {
                valores[k++] += alpha[t] * algoritmo[i][j];
            }
        }
    }

    k = 0;
    for (int i = 0; i < corpusProva.pegarQtdSentencas(); i++) {
        for (int j = 0; j < corpusProva.pegarQtdTokens(i); j++) {
            corpusProva(i, j, atributo, (valores[k++] > 0.0) ? positivo : negativo);
        }
    }

    return true;
}

/*vector<vector<string> > ClassificadorAdaBoost::executarAlgoritmo(Corpus &corpus) {
    vector<double> valores(corpus.pegarQtdTotalExemplos(),0.0);
    vector<vector<string> > resultado;

    int k;
    for (int t = 0; t < iteracoes; t++) {
        vector<vector<int> > algoritmo = (baseClassifier[t])->executarAlgoritmo2(corpus);
        k = 0;
        for (int i = 0; i < corpus.pegarQtdSentencas(); i++) {
            for (int j = 0; j < corpus.pegarQtdTokens(i); j++) {
                valores[k++] += alpha[t] * algoritmo[i][j];
            }
        }
    }

    k = 0;
    for (int i = 0; i < corpus.pegarQtdSentencas(); i++) {
        vector<string> linha;
        for (int j = 0; j < corpus.pegarQtdTokens(i); j++) {
            linha.push_back((valores[k++] > 0.0) ? positivo : negativo);
        }
        resultado.push_back(linha);
    }

    return resultado;
}*/

bool ClassificadorAdaBoost::gravarConhecimento(string arquivo) {
    ofstream saida(arquivo.c_str());

    if(!saida.is_open()) {
        return false;
    }

    int iteracoes = alpha.size();

    saida << iteracoes << ' ';
    for (int i = 0; i < iteracoes - 1; i++) {
        saida << alpha[i] << ' ';
    }

    saida << alpha[iteracoes-1] << endl;

    saida << typeid(*(baseClassifier[0])).name() << endl;

    string extensao = arquivo.substr(arquivo.rfind("."),arquivo.length());
    arquivo = arquivo.substr(0, arquivo.rfind("."));

    for (int i = 0; i < iteracoes; i++) {
        ostringstream os;
        os << arquivo << i << extensao;
        baseClassifier[i]->gravarConhecimento(os.str());
    }

    return true;
}

bool ClassificadorAdaBoost::carregarConhecimento(string arquivo) {
    ifstream entrada(arquivo.c_str());

    if(!entrada.is_open()) {
        return false;
    }

    int iteracoes = alpha.size();

    entrada >> iteracoes;
    alpha.resize(iteracoes, 0);
    baseClassifier.resize(iteracoes, NULL);
    for (int i = 0; i < iteracoes; i++) {
        entrada >> alpha[i];
    }

    string tipo;
    entrada >> tipo;

    string extensao = arquivo.substr(arquivo.rfind("."),arquivo.length());
    arquivo = arquivo.substr(0, arquivo.rfind("."));

    for (int i = 0; i < iteracoes; i++) {
        ostringstream os;
        os << arquivo << i << extensao;
        if (tipo.find("ClassificadorStump"))
            baseClassifier[i] = new ClassificadorStump();
        (baseClassifier[i])->carregarConhecimento(os.str());
    }

    return true;
}
