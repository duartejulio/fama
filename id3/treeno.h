#include "../corpus/corpusmatriz.h"

#include "../treinador/treinador.h"
#include "../classificador/classificador.h"

///prototipo do treeno


class TreeNo {
    public:
        TreeNo();
        TreeNo(string nome);
        void adicionarNo(string nome);
        float Entropia(Corpus &corpus, int atributo);
        void pegarValorMaiorFreq (Corpus &corpus, int atributo);
        double entropia (Corpus &corpus, int atributo);
        double ganho (Corpus &corpus, int atributo, int atributoAlvo);
        string escolherAtributoNo (Corpus &subcorpus, vector<string> atr, int atributoAlvo);
        void pegarValoresNo (Corpus &corpus, int atributo, int iRespostaNo);
        void imprimirNo();
        string nomeNo;
        string melhorAttrNo;
        int    maiorFreq;
        struct freqEnd {
               int freqNo;
               TreeNo* endNo;
        };
        map <string, freqEnd> mapaValoresNo;
                
};

