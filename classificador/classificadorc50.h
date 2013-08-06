#ifndef CLASSIFICADORC50_H
#define CLASSIFICADORC50_H

#include "classificador.h"
#include "../C50/c50.h"
#include <fstream>

class ClassificadorC50 : public Classificador
{
        vector<string> atributos;
		vector<string> classes;
		string classeNome;
		vector< vector<string> > attValName;
    public:
        ClassificadorC50( vector<string> atributos, vector<string> classes, vector< vector<string> > attValName);
        ClassificadorC50();
        ClassificadorC50( string arquivo );
        virtual bool executarClassificacao( Corpus &corpusProva, int atributo, C50 &objc50 );        
        virtual bool executarClassificacao( Corpus &corpusProva, int atributo){
            return true;
        }
        virtual bool gravarConhecimento( string arquivo );
        virtual bool carregarConhecimento( string arquivo );
        string descricaoConhecimento(){return "Mais Provavel";}
};

#endif // CLASSIFICADORC50_H