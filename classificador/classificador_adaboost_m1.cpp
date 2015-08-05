#include "classificador_adaboost_m1.h"
#include "classificador/classificador_stump.h"
#include <cmath>
#include <typeinfo>
#include <fstream>
#include <sstream>

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
    //return false;
    ofstream saida(arquivo.c_str());

    if(!saida.is_open()) {
        return false;
    }

    for (int i = 0; i < valores.size() - 1; i++)
        saida << '"' << valores[i] << "\" ";
    saida << '"' << valores[valores.size() - 1] << '"' << endl;

    int iteracoes = betas.size();

    saida << iteracoes << ' ';
    for (int i = 0; i < iteracoes - 1; i++) {
        saida << betas[i] << ' ';
    }

    saida << betas[iteracoes-1] << endl;

    saida << typeid(*(classificadores[0])).name();

    string extensao = arquivo.substr(arquivo.rfind("."),arquivo.length());
    arquivo = arquivo.substr(0, arquivo.rfind("."));

    for (int i = 0; i < iteracoes; i++) {
        ostringstream os;
        os << arquivo << i << extensao;
        classificadores[i]->gravarConhecimento(os.str());
    }

    return true;
}

bool ClassificadorAdaboostM1::carregarConhecimento( string arquivo ) {
    //return false;
    ifstream entrada(arquivo.c_str());

    if(!entrada.is_open()) {
        return false;
    }

    string valor = "";
    char ch;
    bool continua = false;

    while ((ch = entrada.get()) != '\n') {
        if (ch == '"') {
            continua = !continua;
            if (!valor.empty())
                valores.push_back(valor);
            valor = "";
        } else {
            if (continua) {
                valor += ch;
            }
        }
    }

    int iteracoes = betas.size();

    entrada >> iteracoes;
    betas.resize(iteracoes, 0);
    classificadores.resize(iteracoes, NULL);
    for (int i = 1; i < iteracoes; i++) {
        entrada >> betas[i];
    }

    string tipo;

    entrada >> tipo;

    string extensao = arquivo.substr(arquivo.rfind("."),arquivo.length());
    arquivo = arquivo.substr(0, arquivo.rfind("."));

    for (int i = 0; i < iteracoes; i++) {
        ostringstream os;
        os << arquivo << i << extensao;
        if (tipo.find("ClassificadorStump"))
            classificadores[i] = new ClassificadorStump();
        (classificadores[i])->carregarConhecimento(os.str());
    }

    return true;
}

string ClassificadorAdaboostM1::descricaoConhecimento () {
    return "Classificador com base no meta-algoritmo AdaBoost M1";
}
