#include "../corpus/corpusmatriz.h"

#include "../treinador/treinador.h"
#include "../classificador/classificador.h"
#include "treeno.h"

///prototipo do classificador
class ClassificadorTree:public Classificador{
        vector <string> classes;
        TreeNo Raiz, *Endteste;
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
        void ajustarAtributos(vector<string> atr){atributos = atr;}
        void ajustarClasses(vector<string> cla){classes = cla;}
        void pegarEndNoRaiz(TreeNo* EndNoRaiz);
        void printDTree();
        Classificador* executarTreinamento( Corpus &corpus, int atributo );
};

class RandomForest:public Treinador{
        DecisionTree *arvoreBase;
        vector <string> atributos;
        unsigned int quantidadeMembros, numeroAtributos;
    public:
        RandomForest(DecisionTree*, vector <string>, unsigned int, unsigned int);
        Classificador* executarTreinamento( Corpus &corpus, int atributo );
};

class ComiteClassificador:public Classificador{
        vector <Classificador*> comite;
    public:
        ComiteClassificador(vector<Classificador*>);
        bool executarClassificacao( Corpus &corpusProva, int atributo);
        bool gravarConhecimento( string arquivo ){return true;}
        bool carregarConhecimento( string arquivo ){return true;}
};
