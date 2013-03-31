#ifndef CLASSIFICADORBLS_H
#define CLASSIFICADORBLS_H

#include "../classificador/classificador.h"

class ClassificadorBLS:public Classificador
{
    vector<string> classes;
    string nomeAtributo;

public:
    ClassificadorBLS(vector<string> classes);
    virtual ~ClassificadorBLS();

    virtual bool executarClassificacao(Corpus&, int);
    void ajustarClasses(vector<string> classes);
    string descricaoConhecimento();
    void atualizarValorEmD(string nomeAtributo);
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


#endif //CLASSIFICADORBLS_H
