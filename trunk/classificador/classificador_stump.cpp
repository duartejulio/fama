#include "classificador_stump.h"
#include <fstream>

bool ClassificadorStump::executarClassificacao(Corpus &corpusProva, int atributo) {
    int atrBase = corpusProva.pegarPosAtributo(this->atrResposta);
    if (atrBase == atributo) {
		cout << "ERRO! Não pode ser igual";
		return false;
    }
    string valor;
    map<string, int>::iterator it;
	for (int i = 0; i < corpusProva.pegarQtdSentencas(); i++) {
		for (int j = 0; j < corpusProva.pegarQtdTokens(i); j++) {
			valor = corpusProva(i, j, atrBase);
			it = values.find(valor);
            int atr;
            if (it == values.end()) {
                atr = padrao;
			} else {
                atr = it->second;
			}
            corpusProva.ajustarValor(i, j, atributo, corpusProva.pegarIndice((atr == 1) ? positivo : negativo));
		}
    }
	return true;
}

vector<vector<int> > ClassificadorStump::executarAlgoritmo(Corpus &corpus)
{
    vector<vector<int> > valores(corpus.pegarQtdTotalExemplos());
    int atrBase = corpus.pegarPosAtributo(this->atrResposta);

    string valor;
    map<string, int>::iterator it;

    for (int i = 0; i < corpus.pegarQtdSentencas(); i++) {
        valores[i] = vector<int>(corpus.pegarQtdTokens(i));
        for (int j = 0; j < corpus.pegarQtdTokens(i); j++) {
            valor = corpus(i, j, atrBase);
            it = values.find(valor);
            if (it == values.end()) {
                valores[i][j] = padrao;
            } else {
                valores[i][j] = it->second;
            }
        }
    }

    return valores;
}

bool ClassificadorStump::carregarConhecimento(string arquivo) {
    std::ifstream entrada(arquivo.c_str());

    if (!entrada.is_open())
        return false;

    string valor; int sinal;

    entrada >> padrao >> atrResposta >> positivo >> negativo;

    entrada >> valor >> sinal;

    while (!entrada.eof()) {
        values[valor] = sinal;
        entrada >> valor >> sinal;
    }

    entrada.close();
    return true;
}

bool ClassificadorStump::gravarConhecimento(string arquivo) {
    ofstream saida(arquivo.c_str());

    if (!saida.is_open())
        return false;

    saida << padrao << ' ' << atrResposta << ' ' << positivo << ' ' << negativo << endl;

    for (map<string, int>::iterator it = values.begin(); it != values.end(); ++it) {
        saida << it->first << ' ' << it->second << endl;
    }

    saida.close();

    return true;
}

string ClassificadorStump::descricaoConhecimento() {
    return "Toco de Decisao";
}
