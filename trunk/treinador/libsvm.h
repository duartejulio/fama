#include "../treinador/treinador.h"
#include "../classificador/classificadorlibsvm.h"
#include "../libsvm/svm.h"

//prototipo do treinador
class LibSvm:public Treinador{
        vector <string> atributos, classes;
        struct svm_parameter param;

        bool verificarParametros(svm_parameter param);
        svm_problem* gerarClasseProblemaSvm(Corpus &corpus, int atributo, int nTotalExemplos, unsigned int nAtributos, unsigned int nConjExemplos);

    public:
        LibSvm(vector<string>, vector<string>, svm_parameter);
        Classificador* executarTreinamento( Corpus &corpus, int atributo );
};
