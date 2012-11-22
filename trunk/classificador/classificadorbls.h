#ifndef CLASSIFICADORBLS_H
#define CLASSIFICADORBLS_H

#include "../classificador/classificador.h"

class ClassificadorBLS:public Classificador
{
    vector<string> classes;
    string nomeAtributo;

public:
    ClassificadorBLS(vector<string> classes, string nomeAtributo = "valor");
    virtual ~ClassificadorBLS();

    virtual bool executarClassificacao(Corpus&, int);
    void ajustarClasses(vector<string> classes);
    bool gravarConhecimento(string)
    {
        throw "N�o Implementado";
    }
    bool carregarConhecimento(string)
    {
        throw "N�o Implementado";
    }

};


#endif //CLASSIFICADORBLS_H
