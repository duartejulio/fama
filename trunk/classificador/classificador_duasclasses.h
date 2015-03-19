#ifndef CLASSIFICADORDUASCLASSES_H
#define CLASSIFICADORDUASCLASSES_H

#include "classificador/classificador.h"

class ClassificadorDuasClasses : public Classificador {
protected:
    string positivo, negativo;
public:
    ClassificadorDuasClasses();
    ClassificadorDuasClasses(string pos, string neg) : positivo(pos), negativo(neg) {}
    ~ClassificadorDuasClasses();
    virtual vector<vector<int> > executarAlgoritmo (Corpus &corpus) = 0;
    string pegarPositivo() {return positivo;}
    string pegarNegativo() {return negativo;}
};

#endif // CLASSIFICADORDUASCLASSES_H
