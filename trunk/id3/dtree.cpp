#include "dtree.h"
#include <cmath>

ClassificadorTree::ClassificadorTree(vector<string> clas, TreeNo &EndNoRaiz):Classificador(){
    //guarda parametros
    classes = clas;
    Raiz = EndNoRaiz;
}

bool ClassificadorTree::executarClassificacao( Corpus &corpus, int atributo ){
    int i, nAmostras, nConjAmostras, cont;
    //determina tamanho do conjunto
    nConjAmostras = corpus.pegarQtdConjExemplos();


    cout << "\n No Raiz:" << Raiz.nomeNo;
    cout << "\n No this Raiz:" << this->Raiz.nomeNo;
    cout << "\n========== executarClassificao ==============";
    cout << "\n nome No Raiz: " << Raiz.nomeNo;

    for (register int c=0; c < nConjAmostras; c++){
        nAmostras = corpus.pegarQtdExemplos(c);
        for (register int e=0; e < nAmostras; e++) {
                //cout << "\n";
                i = corpus.pegarPosAtributo(Raiz.nomeNo);
                TreeNo* Endteste = Raiz.mapaValoresEndNo[corpus.pegarSimbolo(corpus.pegarValor(c, e, i))];

                while ((Endteste->nomeNo!=classes[0]) && (Endteste->nomeNo!=classes[1])) {
                    try{
                        i = corpus.pegarPosAtributo(Endteste->nomeNo);
                    }
                    catch(string str){//o atributo não existe no corpus saia
                        break;
                    }
                    Endteste = Endteste->mapaValoresEndNo[corpus.pegarSimbolo(corpus.pegarValor(c, e, i))];
                }

                if (Endteste->nomeNo==classes[0])
                    corpus.ajustarValor(c, e, atributo, corpus.pegarIndice(classes[0]));
                else
                if (Endteste->nomeNo==classes[1])
                    corpus.ajustarValor(c, e, atributo, corpus.pegarIndice(classes[1]));
                else
                    corpus.ajustarValor(c, e, atributo, corpus.pegarIndice("?"));

                //for (cont=0; cont < (atributo+1); cont++)
                //     cout << corpus.pegarSimbolo(corpus.pegarValor(c, e, cont)) << ", ";
        }
    }
    return true;
}


DecisionTree::DecisionTree(vector<string> atr, vector<string> cla):Treinador(){
    //guarda parametros
    atributos = atr;
    classes = cla;
}

void DecisionTree::pegarEndNoRaiz(TreeNo* EndNoRaiz){
    cout << "\n========== pegarEndNoRaiz ===========";
    NoRaiz=EndNoRaiz;
}

void DecisionTree::printDTree() {

     cout << "\n";
     cout << "\n-----------------------------------";
     cout << "\n";
     cout << "\n--       Decision Tree           --";
     cout << "\n";
     cout << "\n-----------------------------------";
     cout << "\n";
     cout << "\n";

     cout << "\n End No Raiz:" << NoRaiz;

     cout << "\n No Raiz:" << NoRaiz->nomeNo;
     NoRaiz->imprimirNo();
}



Classificador* DecisionTree::executarTreinamento( Corpus &corpus, int atributo ){
    int iResposta;
    iResposta=atributo;
    string melhorAttr;

    TreeNo NoRaiz;

    melhorAttr=NoRaiz.escolherAtributoNo(corpus, atributos, iResposta);

// no raiz
    NoRaiz.adicionarNo(melhorAttr);
    cout << "\nNo Raiz: " << melhorAttr;

    pegarEndNoRaiz(&NoRaiz);

    NoRaiz.pegarValoresNo(corpus, corpus.pegarPosAtributo(melhorAttr), iResposta);

    printDTree();


    return new ClassificadorTree(classes, NoRaiz);
}
