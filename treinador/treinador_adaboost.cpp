#include "treinador/treinador_adaboost.h"
#include "classificador/classificador_adaboost.h"
#include <vector>

Classificador* TreinadorAdaBoost::executarTreinamento(Corpus &corpus, int atributo)
{
    vector<double> *dist, *anterior; //Distribuição e distribuição anterior
    vector<double> alpha;
    int qtdExemplos = corpus.pegarQtdTotalExemplos();
    vector<ClassificadorDuasClasses*> classificadores;
    ClassificadorDuasClasses *last = (ClassificadorDuasClasses*)weakTrainner->executarTreinamento(corpus, atributo);
    dist = weakTrainner->pegarDistribuicao();

    positivo = last->pegarPositivo();
    negativo = last->pegarNegativo();

    classificadores.push_back(last);
    //AvaliadorCE avaliador;
    {
    vector<vector<int> > classi = last->executarAlgoritmo(corpus);
    alpha.push_back(calcularErro(corpus, atributo, classi, dist));
    }
    cout << "Tudo pronto for now!" << endl;

    //Now for the main loop
    double pesoMedio, Z;
    int i;
    for (i = 0; i < iterations-1; i++) {
        cout << "Alpha[" << i << "] = " << alpha[i] << std::endl;
        anterior = dist;
        dist = new vector<double>(qtdExemplos, 0.0);
        int k = 0, sinal;
        vector<vector<int> > ref = last->executarAlgoritmo(corpus);

        pesoMedio = 0.0;
        for (int a = 0; a < corpus.pegarQtdSentencas(); a++) {
            for (int b = 0; b < corpus.pegarQtdExemplos(a); b++) {
                sinal = (corpus(a, b, atributo) == positivo) ? 1 : -1;
                dist->at(k) = log(anterior->at(k));
                dist->at(k) -= (alpha[i]) * sinal * (ref[a][b]);
                Z += exp(dist->at(k));
                pesoMedio += dist->at(k++);
            }
        }
        pesoMedio /= (double)k;

        k = 0;
        Z = 0.0;
        for (int a = 0; a < corpus.pegarQtdSentencas(); a++) {
            for (int b = 0; b < corpus.pegarQtdExemplos(a); b++) {
                dist->at(k) -= pesoMedio;
                Z += exp(dist->at(k));
                k++;
            }
        }

        k = 0;
        for (int a = 0; a < corpus.pegarQtdSentencas(); a++) {
            for (int b = 0; b < corpus.pegarQtdExemplos(a); b++) {
                dist->at(k) = exp(dist->at(k))/Z;
                k++;
            }
        }
        //delete anterior;

        //Gerar novo classificador e calcular o alpha
        weakTrainner->setarDistribuicao(dist);
        last = (ClassificadorDuasClasses*)weakTrainner->executarTreinamento(corpus, atributo);
        classificadores.push_back(last);
        alpha.push_back(calcularErro(corpus, atributo, ref, dist));
        //Se o delta for muito pequeno, para
        /*if (alpha[i+1] <= littleAlpha) {
            cout << "Broke on " << i << ", alpha = " << alpha[i+1] << endl;
            classificadores.pop_back();
            alpha.pop_back();
            break;
        }*/
    }
    weakTrainner->setarDistribuicao(NULL);
    return new ClassificadorAdaBoost(classificadores, alpha, positivo, negativo);
}

double TreinadorAdaBoost::calcularErro(Corpus& corpus, int atributo, vector<vector<int> > &classificacao, vector<double> *dist)
{
    double certo = 0, errado = 0; int k = 0;
    for (int i = 0; i < corpus.pegarQtdSentencas(); i++)
    {
        for (int j = 0; j < corpus.pegarQtdTokens(i); j++)
        {
            int sinal = (corpus(i, j, atributo) == positivo) ? 1 : -1;
            if (sinal == classificacao[i][j])
                certo += dist->at(k++);
            else
                errado += dist->at(k++);
        }
    }

    return 0.5*log(certo/errado);
}
