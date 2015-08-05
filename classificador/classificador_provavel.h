#ifndef CLASSIFICADOR_PROVAVEL_H
#define CLASSIFICADOR_PROVAVEL_H

#include "classificador.h"
#include "../corpus/corpus.h"

#include <map>

using namespace std;

class ClassificadorProvavel: public Classificador {
    map<string, map<string, float> > probabilidades;
    map<string, map<string, string> > candidatos;
    string unknown;
public:
    ClassificadorProvavel(const map<string, map<string, float> > &prob, map <string, map<string, string> > &cand, string &un) : probabilidades(prob), candidatos(cand), unknown(un){}
    ~ClassificadorProvavel() {}
	virtual bool executarClassificacao( Corpus &corpusProva, int atributo );
    //virtual vector<vector<string> > executarAlgoritmo (Corpus &corpus);
    virtual bool gravarConhecimento( string arquivo );
    virtual bool carregarConhecimento( string arquivo );
    virtual string descricaoConhecimento ();
};

#endif
