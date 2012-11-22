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
#include "../classificador/classificadorbls.h"


using namespace std;

int main()
{
    vector<string> atributos, classes, atributosTreino;
    int janela = 5, dobras=2;
     //indice do atributo a aprender
    int iResposta, iSaida, iSaidaBLS;

    //carrega conjunto de dados
    CorpusMatriz objCorpus(vector<string>(), ',', false, true);
    ProcessadorSerieHistorica psh(janela, "valor");

    objCorpus.carregarArquivo( "../inputs/ativos" );
    if (psh.processarCorpus(objCorpus))
        cout << "Sucesso\n";

    for (int d=1; d<=janela; d++){
        stringstream out;
        out << "d-" << d;
        atributosTreino.push_back(out.str());
    }
    classes.push_back("-1");
    classes.push_back("+1");

    NaiveBayes objNB(atributosTreino, classes);

    AvaliadorAcuracia objAvalAcur;
    ValidadorKDobras objValidador(objAvalAcur, dobras);

    iResposta = objCorpus.pegarPosAtributo("y");
    iSaida = objCorpus.criarAtributo("saida_nb");
    iSaidaBLS = objCorpus.criarAtributo("saida_bls");

    Classificador *objClass = objNB.executarTreinamento(objCorpus, iResposta);
    objClass->executarClassificacao(objCorpus, iSaida);
    cout << objClass->descricaoConhecimento();

    cout << "Qualidade Naive Bayes: " << 100.*objAvalAcur.calcularDesempenho(objCorpus, iResposta, iSaida)[0] << "%" << endl ;

    ClassificadorBLS *cbls;
    cbls = new ClassificadorBLS(classes, "valor");
    cbls->executarClassificacao(objCorpus, iSaidaBLS);
    cout << cbls->descricaoConhecimento();

    cout << "Qualidade BLS: " << 100.*objAvalAcur.calcularDesempenho(objCorpus, iResposta, iSaidaBLS)[0] << "%" << endl ;

    objCorpus.gravarArquivo( "../inputs/#teste_nb.txt" );

    return 0;
}





