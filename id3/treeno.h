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
        string pegarValorMaiorFreq (Corpus &corpus, int atributo);
        int pegarValorFreq (Corpus &corpus, int atributo );
        double entropia (Corpus &corpus, int atributo);
        double ganho (Corpus &corpus, int atributo, int atributoAlvo);
        string escolherAtributoNo (Corpus &subcorpus, vector<string> atr, int atributoAlvo);
        void pegarValoresNo (Corpus &corpus, int atributo, int iRespostaNo);
        void imprimirNo();
        string nomeNo;
        map <string, int> mapaValoresNo;
        map <string, TreeNo*> mapaValoresEndNo;
};

