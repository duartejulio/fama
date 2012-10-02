#include "../corpus/corpusmatriz.h"

#include "../treinador/treinador.h"
#include "../classificador/classificador.h"
#include "treeno.h"

///prototipo do classificador
class ClassificadorTree:public Classificador{
    private:
        vector <string> classes;
        TreeNo Raiz;
        TreeNo* Endteste;

    public:
        ClassificadorTree(vector<string>, TreeNo &EndNoRaiz);
        bool executarClassificacao( Corpus &corpusProva, int atributo);
        bool gravarConhecimento( string arquivo ){return true;}
        bool carregarConhecimento( string arquivo ){return true;}
};

//prototipo do treinador
class DecisionTree:public Treinador{
    vector <string> atributos, classes;
    TreeNo* NoRaiz;
    public:
        DecisionTree(vector<string>, vector<string>);
        void pegarEndNoRaiz(TreeNo* EndNoRaiz);
        void printDTree();
        Classificador* executarTreinamento( Corpus &corpus, int atributo );
};
