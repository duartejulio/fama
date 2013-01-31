#include <iostream>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cstdlib>

#include "../processador/processadorsh.h"
#include "../corpus/corpusmatriz.h"
#include "../avaliador/avaliador_acuracia.h"
#include "../treinador/naivebayes.h"
#include "../treinador/libsvm.h"
#include "../treinador/reglog.h"
#include "../validador/validadorkdobras.h"
#include "../classificador/classificadorbls.h"

using namespace std;

/**************************** DECLARAÇÃO DE VARIÁVEIS *****************************/

string atributoValorEmD;                    //nome do atributo do valor do ativo no dia D (ex.: valor_petr4)
vector<string> atributosTreino;             //representa os atributos de treinamento (valor, fechamento, abertura, d-1, d-2...)

vector<int> valores_janelas(1);             //vetor das janelas a serem testadas
vector<string> valores_codigoativo(1);      //vetor dos ativos a serem testados
vector<string> classes;                     //representa as classes, positivas (+1) e negativa (-1)

int iResposta;                              //índice da resposta (atributo objetivo)

int iSaidaNB;                               //índice da saida do algoritmo NB
int iSaidaBLS;                              //índice da saida do algoritmo BLS
int iSaidaSVM;                              //índice da saida do algoritmo Support Vector Machine
int iSaidaRegLog;                           //índice da saida do algoritmo Regressão Logistica

int dobras = 2;                             //auxiliar para algoritmo NB

float acuracia = 0.0;                       //calcula acuracia do algoritmo
int janela;                                 //janela atual da execucao do algoritmo

bool svm;                                   //executa algoritmo Support Vector Machine
bool nb;                                    //executa algoritmo Naive Bayes
bool bls;                                   //executa algortimo Base Line System
bool reglog;                                //executa algoritmo Regressão Logística

AvaliadorAcuracia objAvalAcur;              //objeto do framework avaliador de acuracia
ValidadorKDobras objValidador(objAvalAcur, dobras); //auxiliar  do algoritmo NB
stringstream out;                           //auxiliar para manipular strings

Classificador *objClass;                    //classificador NB
ClassificadorBLS *cbls;                     //classificador BLS
Classificador *objClassLibSvm;              //classificador SVM
Classificador *objClassRegLog;              //classificador REGLOG

struct svm_parameter param;                 //auxiliar para integracao com SVM
float e, alpha, lamb, Jmin;                 // auxiliares regressao logistica
int iter;                                   // auxiliar regressao logistica
unsigned int i, j;                          //variaveis auxiliares
string auxexecbls;                          //manter o valor do BLS

int main()
{
    /**************************** PARAMENTROS DE ENTRADA DO PROGRAMA *****************************/
    //valores_janelas[0] = 3;
    //valores_janelas[1] = 5;
    //valores_janelas[2] = 10;
    //valores_janelas[3] = 15;
    //valores_janelas[4] = 20;
    //valores_janelas[5] = 40;
    //valores_janelas[6] = 60;
    valores_janelas[0] = 100; //tamanho máximo da janela

    //valores_codigoativo[0] = "alll11";
    //valores_codigoativo[0] = "ligt3";
    //valores_codigoativo[0] = "petr4";
    //valores_codigoativo[0] = "vivo4";
    //valores_codigoativo[0] = "vale5";
    valores_codigoativo[0] = "arcz6";

    //define quais algoritmos serão executados
    svm = false;
    nb = false;
    bls = true;
    reglog = false;

    /**************************** INICIO DO PROGRAMA *****************************/

    //carrega objeto corpus
    CorpusMatriz objCorpus(vector<string>(), ',', false, true);


    //classes.push_back("-1");
    classes.push_back("-1");
    classes.push_back("+1");

    //carrega arquivo de ativos
    objCorpus.carregarArquivo( "../inputs/ativos_completos_bvmf" );
    //objCorpus.carregarArquivo( "../inputs/ativos_completos_bvmf" );
    //objeto controlador dos algortimos a serem executados
    ProcessadorSerieHistorica psh(100, "");
    //cria atributos a serem utilizados como parametros (y, d-1, d-2, d-..n)
    psh.criarAtributosAuxiliares(objCorpus, 100);
    //setar variaveis controladoras dos indices
    iResposta = objCorpus.pegarPosAtributo("y");
    iSaidaNB = objCorpus.criarAtributo("saida_nb");
    iSaidaBLS = objCorpus.criarAtributo("saida_bls");
    iSaidaSVM = objCorpus.criarAtributo("saida_svm");
    iSaidaRegLog = objCorpus.criarAtributo("saida_reglog");

    //configuracoes SVM
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

    //configuracoes REGRESSAO LOGISTICA
    e= 2.7182818;
    alpha = 0.001;
    lamb = 0.002;
    Jmin = 1000;
    iter = 200;

    LibSvm objLSVM(atributosTreino, classes, atributoValorEmD, param);
    NaiveBayes objNB(atributosTreino, classes);
    RegLog objTreino(classes);

    cbls = new ClassificadorBLS(classes, atributoValorEmD);
    std::string s;

    //arquivo de saida
    ofstream outfile;
    outfile.open("../outputs/saida.txt", fstream::out);
    outfile.clear();

    //execucao
    try{

        for (i=0; i<valores_codigoativo.size();i++){

            outfile << valores_codigoativo[i] << ";";

            //atualiza o valor em D do ativo de execucao
            atributoValorEmD = "valor_" + valores_codigoativo[i];
            psh.atualizarAtributo(atributoValorEmD);
            cout << "******************************************" << endl ;
            cout << ":: Processando Ativo " << valores_codigoativo[i] << endl ;
            cout << "******************************************" << endl ;

            //seta os valores dos parametros d-1, d-2, d-n no corpus
            if (!psh.processarCorpus(objCorpus))
                { cout << "psh.processarCorpus: Erro\n"; }

            //realiza a execucao com distintos parametros de janelas j para o ativo i
            int inicio_janela = 1;
            for (j=0; j<valores_janelas.size();j++){

                outfile << valores_janelas[j] << ";";

                //atualiza valores das janelas
                if (!psh.processarCorpus(objCorpus))
                    { cout << "psh.processarCorpus: Erro\n"; }

                cout << ":: d-" << valores_janelas[j] << " = " ;
                //atributosTreino.clear();

                //atualiza atributos de treino (d-1, d-2...d-n)
                for (int d=inicio_janela; d<=valores_janelas[j]; d++){
                    std::stringstream out;
                    out << "d-" << d;
                    //cout << out.str();
                    atributosTreino.push_back(out.str());
                }

                inicio_janela = valores_janelas[j] + 1;

                //atualiza janela atual
                janela = valores_janelas[j];
                psh.atualizarJanela(janela);

                //std::stringstream out;
                //out << valores_janelas[j];
                //s = out.str();

                /****************************************** Base Line System ******************************************/

                    if (bls) {

                        if (j==0){

                            cbls->atualizarValorEmD(atributoValorEmD);
                            cbls->executarClassificacao(objCorpus, iSaidaBLS);
                            //cout << cbls->descricaoConhecimento();
                            acuracia = 100.*objAvalAcur.calcularDesempenho(objCorpus, iResposta, iSaidaBLS)[0];
                            stringstream tmp;
                            tmp << acuracia;
                            auxexecbls = tmp.str();
                            cout << " BLS: " << acuracia << "%"  ;
                            outfile << acuracia << ";";

                        }
                        else{
                            cout << " BLS: " << auxexecbls << "%"  ;
                            outfile << auxexecbls << ";";
                        }

                    }
                    else{
                        outfile << "0.0;";
                    }
                    /******************************************* Naive Bayes *********************************************/

                    if (nb) {

                        objNB.atualizarAtributosTreino(atributosTreino);

                        objClass = objNB.executarTreinamento(objCorpus, iResposta);
                        objClass->executarClassificacao(objCorpus, iSaidaNB);
                        //cout << objClass->descricaoConhecimento();

                        acuracia = 100.*objAvalAcur.calcularDesempenho(objCorpus, iResposta, iSaidaNB)[0];
                        cout << " NB: " << acuracia << "%"  ;
                        outfile << acuracia << ";";

                        //out << acuracia; s = out.str();
                    }
                    else{
                        outfile << "0.0;";
                    }
                    /********************************* Regressão Logística (Gradiente) ************************************/

                    if (reglog) {

                        //thetas_mini.resize(M+1);
                        objTreino.ajustarParametros(e, alpha, lamb, Jmin, iter, atributosTreino);
                        objClassRegLog = objTreino.executarTreinamento(objCorpus, iResposta);


                        objClassRegLog->executarClassificacao(objCorpus, iSaidaRegLog);
                        //cout << objClassRegLog->descricaoConhecimento();

                        acuracia = 100.*objAvalAcur.calcularDesempenho(objCorpus, iResposta, iSaidaRegLog)[0];
                        cout << " RL: " << acuracia << "%"  ;
                        outfile << acuracia << ";";


                        //out << acuracia; s = out.str();

                    }
                    else{
                        outfile << "0.0;";
                    }

                    /********************************************* LibSVM **********************************************/

                    if (svm) {

                        objLSVM.atualizarValorD(atributoValorEmD);
                        objLSVM.atualizarAtributosTreino(atributosTreino);
                        objClassLibSvm = objLSVM.executarTreinamento(objCorpus, iResposta);

                        objClassLibSvm->executarClassificacao(objCorpus, iSaidaSVM);
                        //cout << objClassLibSvm->descricaoConhecimento();

                        acuracia = 100.*objAvalAcur.calcularDesempenho(objCorpus, iResposta, iSaidaSVM)[0];
                        cout << " SVM: " << acuracia << "%"  ;
                        outfile << acuracia << ";" ;

                        //out << acuracia; s = out.str();

                    }
                    else{
                        outfile << "0.0;";
                    }

                    //objLSVM.~Treinador();
                    cout << endl;
            } //fim j - janela
            cout << endl;
            outfile << ";" << endl ;
        } //fim i - codigo ativo

        outfile.flush();
        outfile.close();
        objCorpus.gravarArquivo( "../inputs/#teste_nb.txt" );
        getchar();
        return 0;

    }catch(string err){
        if (outfile.is_open())
        {
            outfile.close();
        }
        cout << err;
        return 1;
    }


}





