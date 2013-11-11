#ifndef C50CLASSIFICADOR_H
#define C50CLASSIFICADOR_H

#include "classificador.h"
#include "../treinador/c50treinador.h"

class C50Classificador : public Classificador
{
        vector<string> linhasArquivo;
        vector<string> atributos, classes;
    public:
        friend class C50Treinador;
        C50Classificador();
        virtual bool executarClassificacao( Corpus &corpusProva, int atributo);
        virtual bool gravarConhecimento( string arquivo );
        virtual bool carregarConhecimento( string arquivo );
        string descricaoConhecimento(){return "Não Implementado ainda";}
};

#endif // C50CLASSIFICADOR_H
