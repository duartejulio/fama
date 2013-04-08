#include "processadorsh.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

ProcessadorSerieHistorica::ProcessadorSerieHistorica(int _janela_max, string atributo){
    this->janela = _janela_max;
    this->atributo = atributo;
    this->attcriados = false;
    diferenca_i = new float[_janela_max];
}

ProcessadorSerieHistorica::~ProcessadorSerieHistorica(){
    delete []diferenca_i; // When done, free memory pointed to by a.
    diferenca_i = NULL; // Clear a to prevent using invalid memory reference.
}

bool ProcessadorSerieHistorica::criarNovosAtributos() {
}

void ProcessadorSerieHistorica::atualizarJanela(int janela){
    this->janela = janela;
}

void ProcessadorSerieHistorica::atualizarAtributo(string att){
    this->atributo = att;
}

void ProcessadorSerieHistorica::criarAtributosAuxiliares(Corpus &objCorpus){

    int d;

    this->novosAtributos.clear();
    for (d=1; d<=this->janela; d++)
    {
        stringstream out;
        out << d;
        objCorpus.criarAtributo("d-" + out.str(), "0");
        this->novosAtributos.push_back("d-" + out.str());
    }

    objCorpus.criarAtributo("y","0");
    objCorpus.criarAtributo("saida_bls","0");
    objCorpus.criarAtributo("saida_nb","0");
    objCorpus.criarAtributo("saida_reglog","0");
    objCorpus.criarAtributo("saida_svm","0");

    //não adiciona y nos novos Atributos (não deve ser treinado com ele)
}

vector<string> ProcessadorSerieHistorica::processarCorpus(Corpus &objCorpus)
{

    int totlinhas, qtdConjExemplos, c, pos, neg;
    int  d, ipreco, idColDiferenca_i,  iY, linhai, coldif, iSaidaNB,iSaidaBLS,iSaidaSVM,iSaidaRegLog;

    pos = objCorpus.pegarIndice("+1");
    neg = objCorpus.pegarIndice("-1");

    ipreco = objCorpus.pegarPosAtributo(this->atributo);
    iY = objCorpus.pegarPosAtributo("y");
    iSaidaNB = objCorpus.pegarPosAtributo("saida_nb");
    iSaidaBLS = objCorpus.pegarPosAtributo("saida_bls");
    iSaidaSVM = objCorpus.pegarPosAtributo("saida_svm");
    iSaidaRegLog = objCorpus.pegarPosAtributo("saida_reglog");


    for (d=0; d<janela; d++){
        diferenca_i[d] = 0;
    }

    qtdConjExemplos = objCorpus.pegarQtdConjExemplos();
    //tive que alterar aqui pq agora cada registro eh considerado um conjunto de exemplos!
    for (c=0; c<qtdConjExemplos; c++){
        totlinhas = objCorpus.pegarQtdExemplos(c); //sempre = 1

        //preenche os valores das diferenças
        for (linhai=0; linhai < totlinhas; linhai++){

            //atualiza os valores do vetor de diferencas
            for (coldif=janela - 1;coldif > 0; coldif--){
                diferenca_i[coldif] = diferenca_i[coldif - 1];
            }

            //obtem o valor atual do ativo
            int  vatual= objCorpus.pegarValor(c,linhai,ipreco);
            float valor_atual;
            (std::istringstream)(objCorpus.pegarSimbolo(vatual)) >> valor_atual >> std::dec;//converte para float

            //obtem o valor de ontem do ativo
            int  v_di;
            float valor_di, valor_futuro;
            //if (linhai > 0){
            if (c > 0){ //alterei aqui por conta da separacao das linhas por conjunto de exemplos
                //v_di = objCorpus.pegarValor(c, linhai - 1, ipreco);
                v_di = objCorpus.pegarValor(c - 1, linhai , ipreco);
                (std::istringstream)(objCorpus.pegarSimbolo(v_di)) >> valor_di >> std::dec;//converte para float
            }
            else{
                valor_di = valor_atual;
            }

            //if (linhai != totlinhas - 1){
            if (c != qtdConjExemplos - 1){
                //v_di = objCorpus.pegarValor(c, linhai + 1, ipreco);
                v_di = objCorpus.pegarValor(c + 1, linhai , ipreco);
                (std::istringstream)(objCorpus.pegarSimbolo(v_di)) >> valor_futuro >> std::dec;//converte para float
            }
            else{
                valor_futuro = valor_atual;
            }

            //d-1
            diferenca_i[0] = valor_atual - valor_di;

            objCorpus.ajustarValor(c, linhai, iY, (valor_futuro > valor_atual)?pos:neg);

            //preenche os valores das diferenças
            for (coldif=1;coldif <= janela ; coldif++){
                std::string s;
                std::stringstream out;
                out << coldif;
                s = "d-" + out.str();

                idColDiferenca_i = objCorpus.pegarPosAtributo(s);

                std::stringstream out2;
                out2 << setprecision(2) << setiosflags(ios::fixed);
                out2 << diferenca_i[coldif-1];

                objCorpus.ajustarValor(c,linhai,idColDiferenca_i, objCorpus.pegarIndice(out2.str()));

            }

            //zerando novamente as colunas de saidas dos algoritmos
            objCorpus.ajustarValor(c,linhai,iSaidaNB, objCorpus.pegarIndice("0"));
            objCorpus.ajustarValor(c,linhai,iSaidaBLS, objCorpus.pegarIndice("0"));
            objCorpus.ajustarValor(c,linhai,iSaidaRegLog, objCorpus.pegarIndice("0"));
            objCorpus.ajustarValor(c,linhai,iSaidaSVM, objCorpus.pegarIndice("0"));
        }
    }

    return this->novosAtributos;
}
