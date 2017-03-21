
#include <cmath>
#include "adaboost.h"
#include "../classificador/classificadoradaboost.h"

TreinadorAdaboost::TreinadorAdaboost(Treinador &base, vector<string> classes, unsigned iterations, double minalpha, bool aceitaDistribuicao):
 base(base),classes(classes),iterations(iterations),minalpha(minalpha),aceitaDistribuicao(aceitaDistribuicao){
}

void TreinadorAdaboost::ajustaDistribuicaoInicial(vector<double> distribuicaoInicial){
    this->distribuicaoInicial = distribuicaoInicial;
}

Classificador* TreinadorAdaboost::executarTreinamento( Corpus &corpus, int atributo ){

    Classificador *cl;
    double beta, acertos, erros, sumdist;
    vector <double> alphas;
    vector<Classificador*> classificadores;
    Corpus *corpusTrabalho = &corpus;

    unsigned i, atributoTemporario, c, e, nConjExemplos = corpus.pegarQtdTotalExemplos(), nExemplos;
    vector<double> dist(nConjExemplos);
    vector<bool> errado(nConjExemplos);

    //cout << "*" << distribuicaoInicial.size() << "," << nConjExemplos << "*\n";
    if (distribuicaoInicial.size())
        dist = distribuicaoInicial;
    else
        fill(dist.begin(), dist.end(), 1.0/nConjExemplos);

    if (dist.size()!=nConjExemplos){
        ostringstream erro;
        erro << "Distribuicao Inicial Invalida " << dist.size() << " != " << nConjExemplos;
        throw erro.str();
    }

    atributoTemporario = corpus.criarAtributo("adab");

    for (i = 0; i < iterations; i++){
        fill_n(errado.begin(), nConjExemplos, false);

        if (aceitaDistribuicao)
            ((TreinadorDistribuicao&)base).ajustarDistribuicao(dist);
        else
            corpusTrabalho = corpus.reamostrar(dist);

        cl = base.executarTreinamento(*corpusTrabalho, atributo);
        cl->executarClassificacao(*corpusTrabalho, atributoTemporario);

        //calcula erro, generalizar para vários exemplos por conjunto de exemplo
        acertos = erros = 0;
        for (c=0;c<nConjExemplos;c++){
            nExemplos = corpusTrabalho->pegarQtdExemplos(c);
            for (e=0; e<nExemplos; e++){
                if ((corpusTrabalho->pegarValor(c,e,atributo)!=corpusTrabalho->pegarValor(c,e,atributoTemporario))){
                    errado[c] = true;
                    break;
                }
            }
            if (errado[c])
                erros += dist[c];
            else
                acertos += dist[c];
        }
        beta = acertos/erros;

        //cout << i << "-" << beta << endl;

        sumdist = 0.0;
        for (c=0;c<nConjExemplos;c++){
            if (errado[c])
                dist[c] *= beta;
            sumdist += dist[c];
        }

        for (c=0;c<nConjExemplos;c++)
            dist[c] /= sumdist;

        classificadores.push_back(cl);
        alphas.push_back(.5*log(beta));

        if (alphas[i] < minalpha)
            break;
    }

    corpus.removerAtributo("adab");

    return new ClassificadorAdaboost(classes,classificadores,alphas);
}

