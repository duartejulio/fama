#include "../treinador/treinador.h"
#include "../classificador/classificador.h"

//prototipo do classificador
class ClassificadorStump:public Classificador{
    private:
        vector <string> classes;
        string atributo, valor, classe;
    public:
        ClassificadorStump(vector<string>, string, string, string);
        bool executarClassificacao( Corpus &corpusProva, int atributo );
        bool gravarConhecimento( string arquivo ){return true;}
        bool carregarConhecimento( string arquivo ){return true;}
        string descricaoConhecimento();
};

//prototipo do treinador
class DecisionStump:public Treinador{
    vector <string> atributos, classes;
    public:
        DecisionStump(vector<string>, vector<string>);
        Classificador* executarTreinamento( Corpus &corpus, int atributo );
};
