#include "classificadorlibsvm.h"
#include "../libsvm/svm.h"
#include <cmath>
#include <sstream>
#include <iomanip>
#include <iostream>

ClassificadorLibSvm::ClassificadorLibSvm(vector<string> classes,
                                         vector<string> atributos,
                                         svm_problem problema,
                                         svm_model* modelo )
{
    this->classes = classes;
    this->atributos = atributos;
    this->problema = problema;
    this->modelo = modelo;


}

bool ClassificadorLibSvm::executarClassificacao(Corpus &corpus, int atributo)
{

    double predict_label; //alvo e encontrada
    int i, a, e, c, pos, neg, out, nExemplos, nConjExemplos, nAtributos, nClasses, v;
    //struct svm_problem prob;
    struct svm_model* mod;
    struct svm_node *x_node; //n� atributos

    float val;


    //prob = this->problema; a principio nao vou mais precisar usar pq estou varrendo corpus
    mod = this->modelo;

    /*
    varro o objeto corpus e transformo cada linha em um n� svm_node.
    assim mantem-se a estrutura do framework (trabalhando com o objeto corpus)
    e realiza a predi��o com o m�todo do svm (svm_predict)
    */


    //determina tamanho do conjunto
    nConjExemplos = corpus.pegarQtdConjExemplos();
    nAtributos = atributos.size();
    nClasses = classes.size();
    pos = corpus.pegarIndice("+1");
    neg = corpus.pegarIndice("-1");

    //varre os exemplos
    for (c=0; c < nConjExemplos; c++){
        nExemplos = corpus.pegarQtdExemplos(c);
        for (e = 0; e < nExemplos; e++){

                x_node = new struct svm_node[nAtributos + 1 + 1]; //alocando vetor de atributos (total att + valor d atual + finalizador svm_node) = maximo


                for (a=0; a < nAtributos; a++){
                    i = corpus.pegarPosAtributo(atributos[a]);
                    v = corpus.pegarValor(c, e, i);
                    (std::istringstream)(corpus.pegarSimbolo(v)) >> val >> std::dec;//converte para float

                    if (val != 0.0) {
                        x_node[a].index = (a + 1);
                        x_node[a].value = val;

                    }
                }
                //finalizador
                x_node[a].index = (-1);

                predict_label = svm_predict(mod,x_node);

                if (predict_label >= 0.5) {
                    out = pos;
                }
                else{
                    out = neg;
                }

                corpus.ajustarValor(c,e,atributo,out);

        }
    }

	return true;

}


void ClassificadorLibSvm::ajustarClasses(vector<string> classes)
{
    this->classes = classes;
}


string ClassificadorLibSvm::descricaoConhecimento(){
    ostringstream ret;
    ret << " ";

    return ret.str();
}
