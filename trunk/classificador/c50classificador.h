#ifndef C50CLASSIFICADOR_H
#define C50CLASSIFICADOR_H

#include "classificador.h"
#include "../treinador/c50treinador.h"

string removeVirgula(string val);

class C50Classificador : public Classificador
{
        vector<string> linhasArquivo;
        vector< vector<string> > valoresPossiveis;
        vector<string> atributos, classes;
        bool gravarArvore(string arquivo);
    public:
        friend class C50Treinador;
        C50Classificador();
        virtual bool executarClassificacao( Corpus &corpusProva, int atributo);
        virtual bool gravarConhecimento( string arquivo );
        virtual bool carregarConhecimento( string arquivo );
        virtual string descricaoConhecimento();
};

#endif // C50CLASSIFICADOR_H
