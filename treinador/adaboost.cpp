
#include <cmath>
#include "adaboost.h"
#include "../classificador/classificadoradaboost.h"

TreinadorAdaboost::TreinadorAdaboost(TreinadorDistribuicao &base, vector<string> classes, unsigned iterations, double minalpha):base(base),classes(classes),iterations(iterations),minalpha(minalpha){
}

Classificador* TreinadorAdaboost::executarTreinamento( Corpus &corpus, int atributo ){

    Classificador *cl;
    double beta, acertos, erros, sumdist;
    vector <double> alphas;
    vector<Classificador*> classificadores;

    unsigned i, atributoTemporario, c, e, nConjExemplos = corpus.pegarQtdTotalExemplos(), nExemplos;
    vector<double> dist(nConjExemplos, 1.0/nConjExemplos);
    vector<bool> errado(nConjExemplos);

    atributoTemporario = corpus.criarAtributo("adab");

    for (i = 0; i < iterations; i++){
        fill_n(errado.begin(), nConjExemplos, false);

        base.ajustarDistribuicao(dist);
        cl = base.executarTreinamento(corpus, atributo);
        cl->executarClassificacao(corpus, atributoTemporario);

        //calcula erro, generalizar para vários exemplos por conjunto de exemplo
        acertos = erros = 0;
        for (c=0;c<nConjExemplos;c++){
            nExemplos = corpus.pegarQtdExemplos(c);
            for (e=0; e<nExemplos; e++){
                if ((corpus.pegarValor(c,e,atributo)!=corpus.pegarValor(c,e,atributoTemporario))){
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

