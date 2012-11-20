#include "classificadorbls.h"

#include <cmath>
#include <sstream>
#include <iomanip>
#include <iostream>

ClassificadorBLS::ClassificadorBLS(vector<string> classes)
{
    this->classes = classes;
    //ctor
}

ClassificadorBLS::~ClassificadorBLS()
{
    //dtor
}

bool ClassificadorBLS::executarClassificacao(Corpus &corpus, int atributo)
{
    //recebe o corpus e o indice do atributo a ser comparado
	int  e, c, nExemplos, nConjExemplos, gcl, nClasses, v, ipreco, pos, neg;
    float val, val_ant;



    //determina tamanho do conjunto
    nConjExemplos = corpus.pegarQtdConjExemplos();
    nClasses = classes.size();
	val_ant = 0.0;
	ipreco = corpus.pegarPosAtributo("valor");


    pos = corpus.pegarIndice("+1");
    neg = corpus.pegarIndice("-1");

    gcl = pos; //aleatoriamente assume a tendencia de crescimento

    //i = corpus.pegarPosAtributo(atributo);

	//varre os exemplos
    for (c=0; c < nConjExemplos; c++){
        nExemplos = corpus.pegarQtdExemplos(c);
		for (e = 0; e < nExemplos; e++){

            corpus.ajustarValor(c,e,atributo,gcl);

            v = corpus.pegarValor(c, e, ipreco);
            (std::istringstream)(corpus.pegarSimbolo(v)) >> val >> std::dec;//converte para float
            if ((val - val_ant) > 0.0) {
                gcl = pos;
            }
            else
            {
                gcl = neg;
            }
            val_ant = val;
		}

	}

	return true;

}


void ClassificadorBLS::ajustarClasses(vector<string> classes)
{
    this->classes = classes;
}


