#include "../treinador/treinador.h"
#include "../classificador/classificadornb.h"

//prototipo do treinador
class NaiveBayes:public Treinador{
    vector <string> atributos, classes;
    public:
        NaiveBayes(vector<string>, vector<string>);
        Classificador* executarTreinamento( Corpus &corpus, int atributo );
};
