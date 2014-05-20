#include "../corpus/corpusmatriz.h"

#include "../treinador/c50treinador.h"
#include "../treinador/treinador.h"
#include "../classificador/classificador.h"
#include "treeno.h"

///prototipo do classificador
class ClassificadorTree:public Classificador{
        vector <string> classes;
        TreeNo Raiz, *Endteste;
        string printDTree();
    public:
        ClassificadorTree(vector<string>, TreeNo &EndNoRaiz);
        bool executarClassificacao( Corpus &corpusProva, int atributo);
        bool gravarConhecimento( string arquivo ){return true;}
        bool carregarConhecimento( string arquivo ){return true;}
        string descricaoConhecimento ();
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
        Treinador *arvoreBase;
        vector <string> atributos;
        unsigned int quantidadeMembros, numeroAtributos, modo;
    public:
        RandomForest(DecisionTree*, vector <string>, unsigned int, unsigned int);
        RandomForest(C50Treinador*, vector <string>, unsigned int, unsigned int);
        Classificador* executarTreinamento( Corpus &corpus, int atributo );
};

class ComiteClassificador:public Classificador{
        vector <Classificador*> comite;
    public:
        ComiteClassificador(vector<Classificador*>);
        bool executarClassificacao( Corpus &corpusProva, int atributo);
        bool gravarConhecimento( string arquivo ){return true;}
        bool carregarConhecimento( string arquivo ){return true;}
        string descricaoConhecimento ();
};
