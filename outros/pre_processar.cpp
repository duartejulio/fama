#include "pre_processar.h"
#include "corpus.h"
#include "corpusmatriz.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

bool pre_processar::gerarCorpusProcessado(Corpus &objCorpus, int janela)
{

    int totlinhas = objCorpus.pegarQtdTokens(0);

    int  d, ipreco, idColDiferenca_i,  idColY, linhai, linhaj;
    float diferenca_i[janela];
    ipreco = objCorpus.pegarPosAtributo("valor");

    //criando atributos (colunas) das diferenças de valores
    for (d=1; d<=janela; d++)
    {
        std::string s;
        std::stringstream out;
        out << d;
        s = "d-" + out.str();

        objCorpus.criarAtributo(s,"0");
        //zerando o valor do corpus
        diferenca_i[d-1] = 0;
    }
    //criando atributo (coluna) de saida
    idColY = objCorpus.criarAtributo("y","0");

    //preenche os valores das diferenças
    for (linhai=0; linhai<=totlinhas  - 1; linhai++){

        //atualiza os valores do vetor de diferencas
        for (linhaj=janela - 1;linhaj > 0; linhaj--){
            diferenca_i[linhaj] = diferenca_i[linhaj - 1];
        }

        //obtem o valor atual do ativo
        int  vatual= objCorpus.pegarValor(0,linhai,ipreco);
        float valor_atual;
        (std::istringstream)(objCorpus.pegarSimbolo(vatual)) >> valor_atual >> std::dec;//converte para float

        //obtem o valor de ontem do ativo
        int  v_di;
        float valor_di =0;
        if (linhai > 0){
            v_di= objCorpus.pegarValor(0,(linhai - 1),ipreco);
            (std::istringstream)(objCorpus.pegarSimbolo(v_di)) >> valor_di >> std::dec;//converte para float
        }
        else{
            valor_di = valor_atual;
        }



        //d-1
        diferenca_i[0] = valor_atual - valor_di;

        if (diferenca_i[0] >=0){
            objCorpus.ajustarValor(0,linhai,idColY,objCorpus.pegarIndice("1"));
        }else {
            objCorpus.ajustarValor(0,linhai,idColY,objCorpus.pegarIndice("-1"));
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
            out2<< diferenca_i[linhaj-1];

            objCorpus.ajustarValor(0,linhai,idColDiferenca_i, objCorpus.pegarIndice(out2.str()));

        }

    }


    return true;

}
