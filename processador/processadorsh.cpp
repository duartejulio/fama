#include "processadorsh.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

ProcessadorSerieHistorica::ProcessadorSerieHistorica(int janela, string atributo){
    this->janela = janela;
    this->atributo = atributo;
}

ProcessadorSerieHistorica::~ProcessadorSerieHistorica(){
}

bool ProcessadorSerieHistorica::processarCorpus(Corpus &objCorpus)
{

    int totlinhas, qtdConjExemplos, c;

    int  d, ipreco, idColDiferenca_i,  idColY, linhai, linhaj;
    float diferenca_i[janela];
    ipreco = objCorpus.pegarPosAtributo(atributo);

    //criando atributos (colunas) das diferenças de valores
    for (d=1; d<=janela; d++)
    {
        std::string s;
        std::stringstream out;
        out << d;
        s = "d-" + out.str();

        objCorpus.criarAtributo(s,"0");
    }
    //criando atributo (coluna) de saida
    idColY = objCorpus.criarAtributo("y","0");

    qtdConjExemplos = objCorpus.pegarQtdConjExemplos();
    for (c=0; c<qtdConjExemplos; c++){
        totlinhas = objCorpus.pegarQtdExemplos(c);

        for (d=1; d<=janela; d++)//zerando o valor do corpus
            diferenca_i[d-1] = 0;

        //preenche os valores das diferenças
        for (linhai=0; linhai<=totlinhas  - 1; linhai++){

            //atualiza os valores do vetor de diferencas
            for (linhaj=janela - 1;linhaj > 0; linhaj--){
                diferenca_i[linhaj] = diferenca_i[linhaj - 1];
            }

            //obtem o valor atual do ativo
            int  vatual= objCorpus.pegarValor(c,linhai,ipreco);
            float valor_atual;
            (std::istringstream)(objCorpus.pegarSimbolo(vatual)) >> valor_atual >> std::dec;//converte para float

            //obtem o valor de ontem do ativo
            int  v_di;
            float valor_di =0;
            if (linhai > 0){
                v_di = objCorpus.pegarValor(c,(linhai - 1),ipreco);
                (std::istringstream)(objCorpus.pegarSimbolo(v_di)) >> valor_di >> std::dec;//converte para float
            }
            else{
                valor_di = valor_atual;
            }

            //d-1
            diferenca_i[0] = valor_atual - valor_di;

            if (diferenca_i[0] >=0){
                objCorpus.ajustarValor(c,linhai,idColY,objCorpus.pegarIndice("1"));
            }else {
                objCorpus.ajustarValor(c,linhai,idColY,objCorpus.pegarIndice("-1"));
            }

            //preenche os valores das diferenças
            for (linhaj=1;linhaj <= janela ; linhaj++){
                std::string s;
                std::stringstream out;
                out << linhaj;
                s = "d-" + out.str();

                idColDiferenca_i = objCorpus.pegarPosAtributo(s);

                std::stringstream out2;
                out2 << setprecision(2) << setiosflags(ios::fixed);
                out2 << diferenca_i[linhaj-1];

                objCorpus.ajustarValor(c,linhai,idColDiferenca_i, objCorpus.pegarIndice(out2.str()));

            }

        }
    }

    return true;

}
