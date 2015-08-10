
#include "classificadoradaboost.h"
#include <fstream>
string ClassificadorAdaboost::descricaoConhecimento (){
    stringstream kno;
    kno << "Alphas: [";
    for (unsigned  i=0;i<alphas.size();i++){
        kno << alphas[i];
        if (i<alphas.size()-1)
            kno << " ";
    }
    kno << "]" << endl;
    kno << "Classificadores: " << endl;
    for (unsigned  i=0;i<classificadores.size();i++){
        kno << i << " ";
        kno << classificadores[i]->descricaoConhecimento();
        //kno << endl;
    }
    return kno.str();

}

bool ClassificadorAdaboost::gravarConhecimento( string arquivo ){
    ofstream arq(arquivo.c_str());
    unsigned i;

    arq << classes.size() << " ";
    for (i = 0; i < classes.size(); i++)
        arq << classes[i] << " ";
    arq << endl;

    arq << alphas.size() << " ";
    for (i = 0; i < alphas.size(); i++)
        arq << alphas[i] << " ";
    arq << endl;

    for (i = 0; i < classificadores.size(); i++){
        ostringstream nomeArq;
        nomeArq << i << "-" << arquivo;
        classificadores[i]->gravarConhecimento(nomeArq.str());
    }

    arq.close();
    return true;

}

bool ClassificadorAdaboost::carregarConhecimento( string arquivo ){

    unsigned n, i;
    string classe;
    double alpha;

    ifstream arq(arquivo.c_str());

    arq >> n;
    classes.clear();
    for (i = 0; i < n; i++){
        arq >> classe;
        classes.push_back(classe);
    }

    arq >> n;
    alphas.clear();
    for (i = 0; i < n; i++){
        arq >> alpha;
        alphas.push_back(alpha);
    }

    //cout << "*" << n << "-" << classificadores.size() << endl;

    if (classificadores.size()!=n)
        throw (string)"carregarConhecimento precisa de classificadores base já criados";

    for (i=0;i<n;i++){
        ostringstream nomeArq;
        nomeArq << i << "-" << arquivo;
        classificadores[i]->carregarConhecimento(nomeArq.str());
    }

    return true;
}

bool ClassificadorAdaboost::executarClassificacao( Corpus &corpusProva, int atributo ){

    vector<int> indices, atributos;
    unsigned  c, it, i, n;
    double h;

    n = corpusProva.pegarQtdConjExemplos();

    for (c=0; c< classes.size(); c++)
        indices.push_back(corpusProva.pegarIndice(classes[c]));

    it = alphas.size();

    for (i=0;i<it;i++){
        atributos.push_back(corpusProva.criarAtributo(((string)"adab") + (char)(i+'0')));
        classificadores[i]->executarClassificacao(corpusProva, atributos[i]);
    }

    //generalizar para mais de um exemplo por conjunto
    for (c=0;c<n;c++){
        h = 0.0;
        for (i = 0; i<it; i++)
            if (corpusProva.pegarValor(c,0,atributos[i])==indices[1])
                h += alphas[i];
            else
            if (corpusProva.pegarValor(c,0,atributos[i])==indices[0])
                h -= alphas[i];
            else{
                throw (string)"Saida errada no algoritmo base";
            }
        if (h>=0)
            corpusProva.ajustarValor(c,0,atributo,indices[1]);
        else
            corpusProva.ajustarValor(c,0,atributo,indices[0]);
    }

    for (i=0;i<it;i++)
        corpusProva.removerAtributo(((string)"adab") + (char)(i+'0'));

    return true;
}
