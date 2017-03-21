#include "processadorJanela.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

ProcessadorJanela::ProcessadorJanela(int janela, string atributo,
                                     bool aggregate, string itemNulo){
    this->janela = janela;
    this->atributo = atributo;
    this->itemNulo = itemNulo;
    this->aggregate = aggregate;
}

ProcessadorJanela::~ProcessadorJanela(){
}

vector<string> ProcessadorJanela::processarCorpus(Corpus &objCorpus){
    vector<string> novosAtributos;
    vector<int> indicesAtributos;
    int iAtributo, iNovoAtributo, nConjExemplos, nExemplos, c, e, i;

    nConjExemplos = objCorpus.pegarQtdConjExemplos();
    iAtributo = objCorpus.pegarPosAtributo(atributo);

    for (i=-janela; i<=janela; i++){
        if (i){
            ostringstream nomeAtributo;
            nomeAtributo << atributo << ((i<0)?"_":"_+") << i;
            novosAtributos.push_back(nomeAtributo.str());

            iNovoAtributo = objCorpus.criarAtributo(nomeAtributo.str());
            indicesAtributos.push_back(iNovoAtributo);

            for (c=0; c<nConjExemplos; c++){
                nExemplos = objCorpus.pegarQtdExemplos(c);
                for (e=0; e<nExemplos; e++)
                    objCorpus(c, e, iNovoAtributo,
                     (e + i >= 0 && e + i < nExemplos)?objCorpus(c, e + i, iAtributo):itemNulo);
            }
        }
    }

    if (aggregate){

        ostringstream nomeAtributo;
        int nNovosAtributos = indicesAtributos.size();
        nomeAtributo << atributo << "_" << -janela << "_" << janela;
        novosAtributos.push_back(nomeAtributo.str());
        iNovoAtributo = objCorpus.criarAtributo(nomeAtributo.str());

        for (c=0; c<nConjExemplos; c++){
            //cout << c;
            nExemplos = objCorpus.pegarQtdExemplos(c);
            for (e=0; e<nExemplos; e++){
                ostringstream valor;
                valor << objCorpus(c, e, iAtributo);
                for (i=0; i<nNovosAtributos; i++){
                    valor << "_" << objCorpus(c, e, indicesAtributos[i]);
                }
                objCorpus(c, e, iNovoAtributo, valor.str());
            }
        }

    }
    return novosAtributos;
}


