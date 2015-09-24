#include "knn.h"

Classificador* TreinadorKNN::executarTreinamento( Corpus &corpus, int atributo ){
    float val;
    unsigned int nAtributos, nConjExemplos, nExemplos, a, i, c, e;
    struct svector trExmp;

    ClassificadorKNN *retorno = new ClassificadorKNN(atributos, classes, usarPesos, K, MAXVALUE);

    //determina números de conjuntos de exemplos e atributos
    nConjExemplos = corpus.pegarQtdConjExemplos();
    nAtributos = atributos.size();

    retorno->inicializarDados(nConjExemplos);

    map<int,int> mapaClasses;
    for (i=0; i<classes.size();i++)
        mapaClasses[corpus.pegarIndice(classes[i])] = i;

    //varre atributos
    for (c=0; c < nConjExemplos; c++){
        nExemplos = corpus.pegarQtdExemplos(c);
        for (e=0; e < nExemplos; e++){
            for (a=0; a<nAtributos;a++){
                (std::istringstream)(corpus(c, e, corpus.pegarPosAtributo(atributos[a]))) >> val >> std::dec;//converte para float
                trExmp.attributes[a] = val;
            }

            trExmp.classlabel = mapaClasses[corpus.pegarValor(c, e, atributo)];
            //cout << trExmp.classlabel;
            if(!retorno->AddtoTSet(trExmp)){
                ostringstream erro;
                erro << "Exemplo Invalido";
                throw erro.str();
            }
        }
    }
    return retorno;
}
