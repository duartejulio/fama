#include "dtree.h"
#include <cmath>
#include <sstream>
#include <algorithm>
//#include <conio.h>
//#include <stdlib.h>

ComiteClassificador::ComiteClassificador(vector<Classificador*> com){
    comite = com;
}

bool ComiteClassificador::executarClassificacao( Corpus &corpus, int atributo){

    register unsigned int quantidadeMembros = comite.size(), i, nExemplos, nConjExemplos, c, e;
    int atributoVoto, maior, imaior;
    map<int, int> mapaVoto;
    map<int, int >::iterator it;
    vector<int> iVotos;

    cout << endl << "Quant membros: " << quantidadeMembros;

    for (i=0; i < quantidadeMembros; i++){
        ostringstream nomeVoto;
        nomeVoto << "voto" << i;
        atributoVoto = corpus.criarAtributo(nomeVoto.str());
        iVotos.push_back(atributoVoto);
        cout << endl << "comite" << i << ": " << comite[i];

        comite[i]->executarClassificacao(corpus, atributoVoto);
        cout << endl << "=== teste ===";
    }

    nConjExemplos = corpus.pegarQtdConjExemplos();
    for (c=0; c<nConjExemplos; c++){
        nExemplos = corpus.pegarQtdExemplos(c);
        for (e=0; e<nExemplos; e++){
            mapaVoto.clear();
            for (i=0; i<quantidadeMembros; i++)
                mapaVoto[corpus.pegarValor(c, e, iVotos[i])]++;
            maior = -1;
            imaior = 0;
            for (it = mapaVoto.begin(); it!=mapaVoto.end(); it++)
                if (maior < it->second){
                    maior = it->second;
                    imaior = it->first;
                }
            corpus.ajustarValor(c, e, atributo, imaior);
        }

    }

    return true;
}

RandomForest::RandomForest(DecisionTree *dt, vector <string> atr, unsigned int n, unsigned int nAtr){
    arvoreBase = dt;
    atributos = atr;
    quantidadeMembros = n;
    numeroAtributos = nAtr;
}

Classificador* RandomForest::executarTreinamento( Corpus &corpus, int atributo ){
    vector <string> atributosBase(atributos);
    vector<string>::iterator it;
    string atributoAlvo;
    register unsigned int i;
    vector < Classificador*> comite;

    atributoAlvo = corpus.pegarAtributo(atributo);
    int sorte;

    cout << endl << "valor de atributo alvo: " << atributo << endl;

    //remove atributoalvo
    for (i=0; i < atributosBase.size();i++)
        if (atributosBase[i]==atributoAlvo)
            break;
    atributosBase.erase(atributosBase.begin() + i);

    for (i=0; i<quantidadeMembros; i++){
        vector <string> atributosAtuais(atributosBase);
        //shuffle
        random_shuffle(atributosAtuais.begin(), atributosAtuais.end());

//        sorte=rand()% numeroAtributos;
//        cout << endl << "valor de sorte: " << sorte << endl;

        Corpus *subcorpus;
        subcorpus = corpus.clone();

        while (atributosAtuais.size() > numeroAtributos) {
            subcorpus->removerAtributo(atributosAtuais.back());
            atributosAtuais.pop_back();
        }

        //readiciona atributo alvo
        atributosAtuais.push_back(atributoAlvo);

        atributo = numeroAtributos;

        cout << endl << "valor de atributo alvo: " << atributo << endl;

        arvoreBase->ajustarAtributos(atributosAtuais);
//        Classificador* comiteteste = arvoreBase->executarTreinamento(*subcorpus, atributo);
//        comite.push_back(arvoreBase->executarTreinamento(corpus, atributo));

        comite.push_back(arvoreBase->executarTreinamento(*subcorpus, atributo));
        cout << "***" << endl;

        cout << endl << "Press any key to quit..." << endl;
//	    getch();
    }
    return new ComiteClassificador(comite);
}

ClassificadorTree::ClassificadorTree(vector<string> clas, TreeNo &EndNoRaiz):Classificador(){
    //guarda parametros
    classes = clas;
    Raiz = EndNoRaiz;
}

bool ClassificadorTree::executarClassificacao( Corpus &corpus, int atributo ){
    int i, nAmostras, nConjAmostras;
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
//                TreeNo* Endteste = Raiz.mapaValoresEndNo[corpus.pegarSimbolo(corpus.pegarValor(c, e, i))];

                TreeNo* Endteste=(Raiz.mapaValoresNo[corpus.pegarSimbolo(corpus.pegarValor(c, e, i))]).endNo;

                while ((Endteste->nomeNo!=classes[0]) && (Endteste->nomeNo!=classes[1])) {
                    try{
                        i = corpus.pegarPosAtributo(Endteste->nomeNo);
                    }
                    catch(string str){//o atributo não existe no corpus saia
                        cout << "**" << str << "**" << endl;
                        break;
                    }
//                    Endteste = Endteste->mapaValoresEndNo[corpus.pegarSimbolo(corpus.pegarValor(c, e, i))];
                    Endteste = (Endteste->mapaValoresNo[corpus.pegarSimbolo(corpus.pegarValor(c, e, i))]).endNo;
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
    cout << "\n========== executarClassificao ==============";

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
