#ifndef CLASSIFICADOR_STUMP_H
#define CLASSIFICADOR_STUMP_H

#include "classificador/classificador.h"
#include "classificador/classificador_duasclasses.h"

class ClassificadorStump : public ClassificadorDuasClasses {
protected:
    map<string, int> values;
    string atrResposta;
    int padrao;
public:
    ClassificadorStump(map<string, int> values = map<string, int>(), string pos = "", string neg = "", string atributo = "", int def = 1) :
        ClassificadorDuasClasses(pos, neg), values(values), atrResposta(atributo), padrao(def) {}
    ~ClassificadorStump() {}
	virtual bool executarClassificacao( Corpus &corpusProva, int atributo );
    virtual vector<vector<int> > executarAlgoritmo (Corpus &corpus);
    virtual bool gravarConhecimento( string arquivo );
    virtual bool carregarConhecimento( string arquivo );
    virtual string descricaoConhecimento ();
};

#endif // CLASSIFICADOR_STUMP_H
