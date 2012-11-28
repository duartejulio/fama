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
#include "../treinador/libsvm.h"


using namespace std;

int main()
{
    vector<string> atributos, classes, atributosTreino;
    int janela = 30, dobras=2;
     //indice do atributo a aprender
    int iResposta, iSaida, iSaidaBLS, iSaidaSVM;

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
    iSaidaSVM = objCorpus.criarAtributo("saida_svm");

/*************************************************************************************************
                                          Naive Bayes
*************************************************************************************************/
    Classificador *objClass = objNB.executarTreinamento(objCorpus, iResposta);
    objClass->executarClassificacao(objCorpus, iSaida);
    cout << objClass->descricaoConhecimento();

    cout << "Qualidade Naive Bayes: " << 100.*objAvalAcur.calcularDesempenho(objCorpus, iResposta, iSaida)[0] << "%" << endl ;

/*************************************************************************************************
                                        Base Line System
*************************************************************************************************/
    ClassificadorBLS *cbls;
    cbls = new ClassificadorBLS(classes, "valor");
    cbls->executarClassificacao(objCorpus, iSaidaBLS);
    cout << cbls->descricaoConhecimento();

    cout << "Qualidade BLS: " << 100.*objAvalAcur.calcularDesempenho(objCorpus, iResposta, iSaidaBLS)[0] << "%" << endl ;

/*************************************************************************************************
                                             LibSVM
*************************************************************************************************/

    struct svm_parameter param;


    param.svm_type = C_SVC;
	param.kernel_type = LINEAR; //RBF;
	param.degree = 3;
	param.gamma = 0;
	param.coef0 = 0;
	param.nu = 0.5;
	param.cache_size = 100;
	param.C = 1;
	param.eps = 1e-3;
	param.p = 0.1;
	param.shrinking = 1;
	param.probability = 0;
	param.nr_weight = 0;
	param.weight_label = NULL;
	param.weight = NULL;


    LibSvm objLSVM(atributosTreino, classes, param);
    Classificador *objClassLibSvm = objLSVM.executarTreinamento(objCorpus, iResposta);

    objClassLibSvm->executarClassificacao(objCorpus, iSaidaSVM);
    cout << objClassLibSvm->descricaoConhecimento();

    cout << "Qualidade Support Vector Machine: " << 100.*objAvalAcur.calcularDesempenho(objCorpus, iResposta, iSaidaSVM)[0] << "%" << endl ;


/************************************************************************************************/

    objCorpus.gravarArquivo( "../inputs/#teste_nb.txt" );

    return 0;
}





