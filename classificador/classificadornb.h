#include "../classificador/classificador.h"

//prototipo do classificador
class ClassificadorNB:public Classificador{
    private:
        vector <string> classes, atributos;
        vector< vector < float > > medias, desvio;
        vector < int > count;
    public:
        ClassificadorNB(vector<string> clas, vector<string> atr,
                        vector< vector < float > > medi,
                        vector< vector < float > > desv,
                        vector<  int >);
        bool executarClassificacao( Corpus &corpusProva, int atributo );
        bool gravarConhecimento( string arquivo ){return true;}
        bool carregarConhecimento( string arquivo ){return true;}
        string descricaoConhecimento();
};

