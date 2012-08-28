#include "stump.h"

#include <cmath>

ClassificadorStump::ClassificadorStump(vector<string> clas, string atr, string val, string cla):Classificador(){
    //guarda parametros
    classes = clas;
    atributo = atr;
    classe = cla;
    valor = val;
}

bool ClassificadorStump::executarClassificacao( Corpus &corpus, int atributo ){
    int iAtr, iCla, iVal, iOutra;
    int a, nAmostras;

    //determina tamanho do conjunto
    nAmostras = corpus.pegarQtdExemplos(0);

    //mapeia atributo
    iAtr = corpus.pegarPosAtributo(this->atributo);
    if (iAtr==-1)
        return false;

    //mapeia valor e classe no corpus atual
    iVal = corpus.pegarIndice(valor);
    iCla = corpus.pegarIndice(classe);

    //determina indice da outra classe
    iOutra = corpus.pegarIndice((classe==classes[0])?classes[1]:classes[0]);

    //varre os exemplos
    for (a = 0; a < nAmostras; a++)
        //criterio de decisao
        if (iVal == corpus.pegarValor(0, a, iAtr))
            corpus.ajustarValor(0, a, atributo, iCla);
        else
            corpus.ajustarValor(0, a, atributo, iOutra);

    return true;
}

DecisionStump::DecisionStump(vector<string> atr, vector<string> cla):Treinador(){
    //guarda parametros
    atributos = atr;
    classes = cla;
}

Classificador* DecisionStump::executarTreinamento( Corpus &corpus, int atributo ){
    int indicePos, indiceNeg, nExemplos, nAtributos, i, a, e, melhorQualidade, qualidade,
     iValor;
    string mAtributo, mValor, mClasse;
    map <string, bool> mapaValores;
    map <string, bool>::iterator it;

    //determina valores das classes no dicionario
    indicePos = corpus.pegarIndice(classes[1]);
    indiceNeg = corpus.pegarIndice(classes[0]);

    //determina números de exemplos e atributos
    nExemplos = corpus.pegarQtdExemplos(0);
    nAtributos = atributos.size();


    melhorQualidade = -1;
    //varre atributos
    for (a=0; a<nAtributos;a++){
        //determina quais são os valores possíveis para o atributo
        mapaValores.clear();
        i = corpus.pegarPosAtributo(atributos[a]);
        for (e=0; e < nExemplos; e++)
            mapaValores[corpus.pegarSimbolo(corpus.pegarValor(0, e, i))] = true;

        //varre todos os valores possiveis
        for (it = mapaValores.begin(); it!=mapaValores.end(); it++){
            iValor = corpus.pegarIndice(it->first);

            //calcula a qualidade desse atributo,valor diferenciando as classes
            qualidade = 0;
            for (e=0; e < nExemplos; e++){
                if (iValor == corpus.pegarValor(0, e, i)){
                    if (corpus.pegarValor(0, e, atributo)==indicePos)
                        qualidade++;
                    else
                        qualidade--;
                }
                else{
                    if (corpus.pegarValor(0, e, atributo)==indiceNeg)
                        qualidade++;
                    else
                        qualidade--;
                }
            }

            //verifica se esse atributo,valor é melhor que o anteriormente escolhido
            if (fabs(qualidade) > melhorQualidade){
                mAtributo = atributos[a];
                mValor = it->first;
                mClasse = (qualidade<0)?classes[0]:classes[1];
                melhorQualidade = (int)fabs(qualidade);
                //cout << "* " << mAtributo << " - " << mValor << " - " << mClasse << " - " << melhorQualidade << endl;
            }
            //cout << i << " - " << a << " - " << atributos[a] << " - " << it->first << " - " << ((qualidade<0)?classes[0]:classes[1]) << " - " << qualidade << endl;
        }
    }

    //retorna um novo classificador com os parametros encontrados
    return new ClassificadorStump(classes, mAtributo, mValor, mClasse);
}
