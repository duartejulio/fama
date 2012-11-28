#include "../classificador/classificador.h"
#include "../libsvm/svm.h"

class ClassificadorLibSvm:public Classificador{
    private:
        vector<string> classes;
        vector<string> atributos;
        struct svm_problem problema;
        struct svm_model modelo;
        string nomeAtributo;

    public:
        ClassificadorLibSvm(vector<string> classes,
                            vector<string> atributos,
                            struct svm_problem problema,
                            struct svm_model modelo,
                            string nomeAtributo = "valor");

        bool executarClassificacao(Corpus&, int);
        void ajustarClasses(vector<string> classes);
        string descricaoConhecimento();
        bool gravarConhecimento(string)
        {
            cout << "Desnecessário";
            return true;
        }
        bool carregarConhecimento(string)
        {
            cout << "Desnecessário";
            return true;
        }

};


