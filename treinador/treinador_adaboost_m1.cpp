#include "treinador_adaboost_m1.h"
#include "treinador.h"
#include "classificador/classificador_adaboost_m1.h"

TreinadorAdaboostM1::TreinadorAdaboostM1(Treinador *weak, bool aceitaDist, int it, string atributo, string unknown)
{
    iterations = it;
    novoAtributo = -1;
    atributoTeste = atributo;
    desconhecido = unknown;
    if (aceitaDist)
        base = new AcessoAoTreinador(dynamic_cast<TreinadorDistribuicao*>(weak));
    else
        base = new AcessoAoTreinadorProxy(weak);
}

Classificador* TreinadorAdaboostM1::executarTreinamento( Corpus &corpus, int atributo ) {
    vector<double> *dist; //Distribuição e distribuição anterior
    vector<double> betas; double ultimoBeta;
    vector<bool>* ultimoResultado;
    vector<Classificador*> classificadores;

    for (int i = 0; i < corpus.pegarQtdSentencas(); i++) {
        for (int j = 0; j < corpus.pegarQtdExemplos(i); j++) {
            valores.insert(corpus(i, j, atributo));
        }
    }
    valores.insert(desconhecido);

    base->atualizarDistribuicao(NULL);

    //Preparar corpus
    try {
        novoAtributo = corpus.pegarPosAtributo(atributoTeste);
    } catch (...) {
        novoAtributo = corpus.criarAtributo(atributoTeste, desconhecido);
    }

    //Itera
    for (int z = 0; z < iterations; z++) {
        classificadores.push_back(base->treinar(corpus, atributo));
        dist = base->pegarDistribuicao();
        ultimoResultado = calcularVetorErro(classificadores.back(), corpus, atributo);
        ultimoBeta = calcularBeta(ultimoResultado, dist);
        betas.push_back(ultimoBeta);
        if (betas.back() > 1.0d) {
            delete ultimoResultado;
            break;
        }
        //Atualizar distribuição
        double norm = 0.0d;
        for (int k = 0; k < dist->size(); k++) {
            if (ultimoResultado->at(k)) {
                dist->at(k) *= ultimoBeta;
            }
            norm += dist->at(k);
        }
        for (int k = 0; k < dist->size(); k++) {
            dist->at(k) /= norm;
        }
        //base->atualizarDistribuicao(dist);
        delete ultimoResultado;
    }

    base->atualizarDistribuicao(NULL);

    return new ClassificadorAdaboostM1(vector<string>(valores.begin(), valores.end()), classificadores, betas);
}

vector<bool>* TreinadorAdaboostM1::calcularVetorErro(Classificador* classificador, Corpus& corpus, int atributo) {
    vector<bool>* resultados = new vector<bool>(corpus.pegarQtdTotalExemplos(), false);
    classificador->executarClassificacao(corpus, novoAtributo);
    int k = 0;
    for (int i = 0; i < corpus.pegarQtdSentencas(); i++) {
        for (int j = 0; j < corpus.pegarQtdExemplos(i); j++) {
            if (corpus(i, j, atributo) == corpus(i, j, novoAtributo))
                resultados->at(k++) = true;
            else
                resultados->at(k++) = false;
        }
    }
    return resultados;
}

double TreinadorAdaboostM1::calcularBeta(vector<bool> *acertos, vector<double> *dist) {
    double acerto = 0.0d, erro = 0.0d;
    for (int k = 0; k < dist->size(); k++) {
        if (acertos->at(k))
            acerto += dist->at(k);
        else
            erro += dist->at(k);
    }
    return erro/acerto;
}
