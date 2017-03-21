#include "stump.h"

#include <cmath>
#include <fstream>
#include <sstream>

ClassificadorStump::ClassificadorStump(vector<string> clas, string atr, string val, string cla):Classificador(){
    //guarda parametros
    classes = clas;
    atributo = atr;
    classe = cla;
    valor = val;
}

bool ClassificadorStump::gravarConhecimento( string arquivo ){
    ofstream arq(arquivo.c_str());
    unsigned i;

    arq << classes.size() << " ";
    for (i = 0; i < classes.size(); i++)
        arq << classes[i] << " ";
    arq << endl;

    arq << atributo << endl;
    arq << classe << endl;
    arq << valor << endl;

    arq.close();
    return true;}

bool ClassificadorStump::carregarConhecimento( string arquivo ){
    unsigned n, i;

    ifstream arq(arquivo.c_str());

    arq >> n;
    classes.clear();
    for (i = 0; i < n; i++){
        arq >> classe;
        classes.push_back(classe);
    }

    arq >> atributo;
    arq >> classe;
    arq >> valor;

    arq.close();

    return true;
}

bool ClassificadorStump::executarClassificacao( Corpus &corpus, int atributo ){
    int iAtr, iCla, iVal, iOutra;
    int a, c, nAmostras, nConjAmostras;

    //determina tamanho do conjunto
    nConjAmostras = corpus.pegarQtdConjExemplos();

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
    for (c=0; c < nConjAmostras; c++){
        nAmostras = corpus.pegarQtdExemplos(c);
        for (a = 0; a < nAmostras; a++)
            if (iVal == corpus.pegarValor(c, a, iAtr))//criterio de decisao
                corpus.ajustarValor(c, a, atributo, iCla);
            else
                corpus.ajustarValor(c, a, atributo, iOutra);
    }
    return true;
}

string ClassificadorStump::descricaoConhecimento(){
    ostringstream ret;

    ret << "Se " << atributo << " = " << valor << " então " << classe << endl;
    ret << "Caso contrário então " << ((classe==classes[0])?classes[1]:classes[0]) << endl;
    return ret.str();
}

DecisionStump::DecisionStump(vector<string> atr, vector<string> cla):TreinadorDistribuicao(){
    //guarda parametros
    atributos = atr;
    classes = cla;
}

Classificador* DecisionStump::executarTreinamento( Corpus &corpus, int atributo ){
    int indicePos, indiceNeg, nExemplos, nConjExemplos, nAtributos,
     i, a, e, c;
    double qualidade, melhorQualidade;
    string mAtributo, mValor, mClasse;
    map <string, bool> mapaValores;
    map <string, bool>::iterator it;
    bool existeDistribuicao;

    //determina valores das classes no dicionario
    indicePos = corpus.pegarIndice(classes[1]);
    indiceNeg = corpus.pegarIndice(classes[0]);

    //determina números de conjuntos de exemplos e atributos
    nConjExemplos = corpus.pegarQtdConjExemplos();
    nAtributos = atributos.size();

    //verifica se existe distribuicao
    existeDistribuicao = dist.size();
    if (!existeDistribuicao)
        for (c=0;c<nConjExemplos;c++)
            dist.push_back(1);
    else{
        if (dist.size()!=(unsigned)nConjExemplos){
            ostringstream erro;
            erro << "Distribuição de pesos de tamanho incorreta passada:" << dist.size() << ", " << nConjExemplos;
            throw erro.str();
        }
    }


    melhorQualidade = -1;
    //varre atributos
    for (a=0; a<nAtributos;a++){
        //determina quais são os valores possíveis para o atributo
        mapaValores.clear();
        i = corpus.pegarPosAtributo(atributos[a]);
        for (c=0; c < nConjExemplos; c++){
            nExemplos = corpus.pegarQtdExemplos(c);
            for (e=0; e < nExemplos; e++)
                //mapaValores[corpus.pegarSimbolo(corpus.pegarValor(c, e, i))] = true;
                mapaValores[corpus(c, e, i)] = true;
        }

        //varre todos os valores possiveis
        for (it = mapaValores.begin(); it!=mapaValores.end(); it++){
            //calcula a qualidade desse atributo,valor diferenciando as classes
            qualidade = 0;
            for (c=0; c < nConjExemplos; c++){
                nExemplos = corpus.pegarQtdExemplos(c);
                for (e=0; e < nExemplos; e++){
                    if (it->first == corpus(c, e, i)){
                        if (corpus.pegarValor(c, e, atributo)==indicePos)
                            qualidade += dist[c];
                        else
                            qualidade -= dist[c];
                    }
                    else{
                        if (corpus.pegarValor(c, e, atributo)==indiceNeg)
                            qualidade += dist[c];
                        else
                            qualidade -= dist[c];
                    }
                }
            }

            //verifica se esse atributo,valor é melhor que o anteriormente escolhido
            if (fabs(qualidade) > melhorQualidade){
                mAtributo = atributos[a];
                mValor = it->first;
                mClasse = (qualidade<0)?classes[0]:classes[1];
                melhorQualidade = fabs(qualidade);
                //cout << "* " << mAtributo << " - " << mValor << " - " << mClasse << " - " << melhorQualidade << endl;
            }
            //cout << i << " - " << a << " - " << atributos[a] << " - " << it->first << " - " << ((qualidade<0)?classes[0]:classes[1])
            // << " - " << qualidade << " - " << melhorQualidade << endl;
        }
    }

    if (!existeDistribuicao)
            dist.clear();
    //cout << "* " << mAtributo << " - " << mValor << " - " << mClasse << " - " << melhorQualidade << endl;
    //retorna um novo classificador com os parametros encontrados
    return new ClassificadorStump(classes, mAtributo, mValor, mClasse);
}
