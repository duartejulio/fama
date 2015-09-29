#ifndef CLASSIFICADORKNN_H
#define CLASSIFICADORKNN_H

#include "../treinador/treinador.h"
#include "../classificador/classificador.h"

#define MAXNATTRS 100
#define MAXVALUE 10000.0

struct svector {
    double attributes[MAXNATTRS];
    double classlabel;
};
struct item {
    double distance;
    double classlabel;
};

class ClassificadorKNN : public Classificador{
friend class TreinadorKNN;
protected:
    vector<string> atributos;
    vector<string> classes;
    bool usarPesos;
    int K, NATTRS, MAXSZ;
    svector *trSet;
    item *knn;
    int curTSize;
    svector getExmp(int i){
        return trSet[i];
    }
    void removerExmp(int i){
        trSet[i] = trSet[--curTSize];
    }
public:
    int max(item knn[]);
    int AddtoTSet(svector v);
    double Classify(svector v, int ignoreTrainElement = -1);
    double Distance(svector v1, svector v2);
    bool inicializarDados(int qtdExemplos);
    ClassificadorKNN(){
        trSet = NULL;
        knn = NULL;
    }

    ClassificadorKNN(vector<string> atributos, vector<string> classes, bool usarPesos = false, int K = 5):
     atributos(atributos), classes(classes), usarPesos(usarPesos), K(K), NATTRS(NATTRS){
        NATTRS = atributos.size();
        knn = new item[K];
        trSet = NULL;
        curTSize = 0;
     }
    virtual ~ClassificadorKNN(){
        if (knn)
            delete []knn;
        if (trSet)
            delete []trSet;
    }
    bool executarClassificacao( Corpus &corpusProva, int atributo );
    bool gravarConhecimento( string arquivo );
    bool carregarConhecimento( string arquivo );
    string descricaoConhecimento ();
};

#endif // CLASSIFICADORKNN_H
