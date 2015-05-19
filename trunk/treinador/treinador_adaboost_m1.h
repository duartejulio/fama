#ifndef TREINADORADABOOSTM1_H
#define TREINADORADABOOSTM1_H

#include "treinador.h"
#include "treinador/treinador_distribuicao.h"
#include <set>

class TreinadorAdaboostM1 : public Treinador
{
    //Classe auxiliar para acesso ao treinar base, caso esse suporte distribuição
    class AcessoAoTreinador {
        TreinadorDistribuicao *weak;
    public:
        AcessoAoTreinador() {}
        explicit AcessoAoTreinador(TreinadorDistribuicao *weak) : weak(weak) {}
        virtual ~AcessoAoTreinador() {delete weak;}
        virtual Classificador* treinar(Corpus &corpus, int atributo) {
            return weak->executarTreinamento(corpus, atributo);
        }
        virtual void atualizarDistribuicao(vector<double> *dist) {
            vector<double>* dist2 = weak->pegarDistribuicao();
            if (dist2 != NULL)
                delete dist2;
            weak->setarDistribuicao(dist);
        }
        virtual vector<double> *pegarDistribuicao() {
            return weak->pegarDistribuicao();
        }
    };

    class AcessoAoTreinadorProxy : public AcessoAoTreinador {
        Treinador *weak;
        vector<double> *distribuicao;
    public:
        explicit AcessoAoTreinadorProxy(Treinador *weak) : weak(weak), distribuicao(NULL) {}
        virtual ~AcessoAoTreinadorProxy() {delete weak;}
        virtual Classificador* treinar(Corpus &corpus, int atributo) {
            Corpus *redistribuicao = corpus.reamostrar(distribuicao, true);
            Classificador *retorno = weak->executarTreinamento(*redistribuicao, atributo);
            if (distribuicao == NULL)
                distribuicao = new vector<double>(redistribuicao->pegarQtdTotalExemplos(), 1.0d/(double)redistribuicao->pegarQtdTotalExemplos());
            delete redistribuicao;
            return retorno;
        }
        virtual void atualizarDistribuicao(vector<double> *dist) {
            if (distribuicao == NULL)
                delete distribuicao;
            distribuicao = dist;
        }
        virtual vector<double> *pegarDistribuicao() {
            return distribuicao;
        }
    };

    vector<bool> *calcularVetorErro(Classificador* classificador, Corpus& corpus, int atributo);
    double calcularBeta(vector<bool> *acertos, vector<double> *dist);

    AcessoAoTreinador *base;
    int novoAtributo;
    int iterations;
    string atributoTeste;
    set<string> valores;
    string desconhecido;
public:
    TreinadorAdaboostM1(Treinador *weak, bool aceitaDist, int it = 10, string atributo = "resposta", string unknown = "desconhecido");
    virtual ~TreinadorAdaboostM1() {delete base;}
    virtual Classificador *executarTreinamento( Corpus &corpus, int atributo );
};

#endif // TREINADORADABOOSTM1_H
