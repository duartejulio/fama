#include <iostream>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cstdlib>

#include "../processador/processadorsh.h"
#include "../corpus/corpusmatriz.h"
#include "../avaliador/avaliador_acuracia.h"
#include "../treinador/naivebayes.h"
#include "../validador/validadorkdobras.h"

using namespace std;

int main()
{
    vector<string> atributos, classes, atributosTreino;
    int janela = 50, dobras=2;
     //indice do atributo a aprender
    int iResposta, iSaida;

    //carrega conjunto de dados
    CorpusMatriz objCorpus(vector<string>(), ',', false, true);
    ProcessadorSerieHistorica psh(janela, "valor");

    objCorpus.carregarArquivo( "../inputs/ativos" );
    if (psh.processarCorpus(objCorpus))
        cout << "Sucesso\n";


    for (int d=1; d<=janela; d++)
    {
        string s;
        stringstream out;
        out << d;
        atributosTreino.push_back("d-" + out.str());
    }
    classes.push_back("-1");
    classes.push_back("+1");

    NaiveBayes objNB(atributosTreino, classes);
    AvaliadorAcuracia objAvalAcur;
    ValidadorKDobras objValidador(objAvalAcur, dobras);

    iResposta = objCorpus.pegarPosAtributo("y");
    iSaida = objCorpus.criarAtributo("teste");
/*
    cout << "*OK" << endl;
    vector< vector< float > > v = objValidador.executarExperimento(objNB, objCorpus, iResposta, iSaida);
    cout << "*" << v[0][0] << endl;
    float media = 0;
    for (int c=0;c<dobras;c++){
        cout << c << " - " << v[c][0] << endl;
        media += v[c][0];
    }
    cout << "*" << media/dobras << endl;
*/


    Classificador *objClass = objNB.executarTreinamento(objCorpus, iResposta);
    objClass->executarClassificacao(objCorpus, iSaida);
    cout << objClass->descricaoConhecimento();

    cout << "Qualidade: " << 100.*objAvalAcur.calcularDesempenho(objCorpus, iResposta, iSaida)[0] << "%" << endl ;
    objCorpus.gravarArquivo( "../inputs/#teste.txt" );


    return 0;
}
