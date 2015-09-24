#ifndef CLASSIFICADORKNN_H
#define CLASSIFICADORKNN_H

#include "../treinador/treinador.h"
#include "../classificador/classificador.h"

#define MAXNATTRS 100

struct svector {
    double attributes[MAXNATTRS];
    double classlabel;
};
struct item {
    double distance;
    double classlabel;
};

class ClassificadorKNN : public Classificador{
protected:
    vector<string> atributos;
    vector<string> classes;
    bool usarPesos;
    int K, NATTRS, MAXSZ, MAXVALUE;
    svector *trSet;
    item *knn;
    int curTSize;
public:
    int max(item knn[]);
    int AddtoTSet(svector v);
    double Classify(svector v);
    double Distance(svector v1, svector v2);
    bool inicializarDados(int qtdExemplos);

    ClassificadorKNN(vector<string> atributos, vector<string> classes, bool usarPesos = false, int K = 5, int MAXVALUE = 10000.0):
     atributos(atributos), classes(classes), usarPesos(usarPesos), K(K), NATTRS(NATTRS), MAXVALUE(MAXVALUE){
        NATTRS = atributos.size();
        knn = new item[K];
        trSet = NULL;
        curTSize = 0;
     }
    virtual ~ClassificadorKNN(){
        delete []knn;
        if (trSet)
            delete []trSet;
    }
    bool executarClassificacao( Corpus &corpusProva, int atributo );
    bool gravarConhecimento( string arquivo ){return false;}
    bool carregarConhecimento( string arquivo ){return false;}
    string descricaoConhecimento (){return "Não IMP";}
};

#endif // CLASSIFICADORKNN_H
