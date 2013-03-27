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
#include "../treinador/regressaologistica.h"
#include "../validador/validadorkdobras.h"
#include "../classificador/classificadorbls.h"

using namespace std;

/**************************** DECLARAÇÃO DE VARIÁVEIS *****************************/

string atributoValorEmD;                    //nome do atributo do valor do ativo no dia D (ex.: valor_petr4)
vector<string> atributosTreino;             //representa os atributos de treinamento (valor, fechamento, abertura, d-1, d-2...)

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

int janela_max = 60;                        //tamanho maximo da janela do processamento
int qtd_ativos = 6; //6                     //quantidade de itens no vetor de ativos
int qtd_janela = 7; //7                     //quantidade de itens no vetor da janela

vector<int> valores_janelas(qtd_janela);        //vetor das janelas a serem testadas
vector<string> valores_codigoativo(qtd_ativos); //vetor dos ativos a serem testados
vector<string> classes;                         //representa as classes, positivas (+1) e negativa (-1)

int main()
{
    /*
    Estrutura do Corpus (atual)
    1:   valor_alll11
    2:   valor_ligt3
    3:   valor_petr4
    4:   valor_vivo4
    5:   valor_vale5
    6:   valor_arcz6
    7:   d-1
    8:   d-2
    n:   d-n
    n+1: y (+1,-1)
    n+2: saida_nb (+1,-1,0)
    n+3: saida_bls (+1,-1,0)
    n+4: saida_svm (+1,-1,0)
    n+5: saida_reglog (+1,-1,0)
    */
    /**************************** PARAMENTROS DE ENTRADA DO PROGRAMA *****************************/
    valores_janelas[0] = 3;
    valores_janelas[1] = 5;
    valores_janelas[2] = 10;
    valores_janelas[3] = 15;
    valores_janelas[4] = 20;
    valores_janelas[5] = 40;
    valores_janelas[6] = 60;

    valores_codigoativo[0] = "alll11";
    valores_codigoativo[1] = "ligt3";
    valores_codigoativo[2] = "petr4";
    valores_codigoativo[3] = "vivo4";
    valores_codigoativo[4] = "vale5";
    valores_codigoativo[5] = "arcz6";

    //define quais algoritmos serão executados
    svm = true;
    nb = false;
    bls = false;
    reglog = false;

    /**************************** INICIO DO PROGRAMA *****************************/

    CorpusMatriz objCorpus(vector<string>(), ';', false, true);

    classes.push_back("-1");
    classes.push_back("+1");

    objCorpus.carregarArquivo( "../inputs/ativos_completos_bvmf" );

    ProcessadorSerieHistorica psh(janela_max, "");

    //cria atributos a serem utilizados como parametros (y, d-1, d-2, d-..n) + saidas de algoritmos
    psh.criarAtributosAuxiliares(objCorpus, janela_max);
    //obtendo referencia em memoria para os atributos
    iResposta = objCorpus.pegarPosAtributo("y");
    iSaidaNB = objCorpus.criarAtributo("saida_nb");
    iSaidaBLS = objCorpus.criarAtributo("saida_bls");
    iSaidaSVM = objCorpus.criarAtributo("saida_svm");
    iSaidaRegLog = objCorpus.criarAtributo("saida_reglog");
    //parametros do sistema para SVM
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
    //parametros do sistema para Reglog
    e= 2.7182818;
    alpha = 0.001;
    lamb = 0.002;
    Jmin = 1000;
    iter = 200;
    //algortimos
    LibSvm objLSVM(atributosTreino, classes, param);
    NaiveBayes objNB(atributosTreino, classes);
    RegressaoLogistica objTreino(classes);
    //classificador baseline
    cbls = new ClassificadorBLS(classes, atributoValorEmD);
    std::string s;
    //arquivo auxiliar para analise posterior
    ofstream outfile;
    outfile.open("../outputs/saida.txt", fstream::out);
    outfile.clear();
    outfile << "ATIVO;JANELA;BLS;SVM;NB;REGLOG;" << endl;

    try{

        for (i=0; i<valores_codigoativo.size();i++){

            outfile << valores_codigoativo[i] << ";";

            //atualiza o valor em D do ativo de execucao
            atributoValorEmD = "valor_" + valores_codigoativo[i];
            psh.atualizarAtributo(atributoValorEmD);
            cout << "******************************************" << endl ;
            cout << ":: Processando Ativo: " << valores_codigoativo[i] << endl ;
            cout << "******************************************" << endl ;

            //seta os valores dos parametros d-1, d-2, d-n + y no corpus para o ativo em questao
            if (!psh.processarCorpus(objCorpus).size())
            {
                cout << "psh.processarCorpus: Erro\n";
            }

            //temporario!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            objCorpus.gravarArquivo( "../inputs/#corpus_" + valores_codigoativo[i] + ".txt" );

            //realiza a execucao com distintos parametros de janelas j para o ativo i
            int inicio_janela = 1;
            for (j=0; j<valores_janelas.size();j++){
                //log
                outfile << valores_janelas[j] << ";";
                cout << ":: d-" << valores_janelas[j] << " = " ;
                //seta os valores dos parametros d-1, d-2, d-n + y no corpus para o ativo em questao
                //??????????????????????????????????????????????????
                if (!psh.processarCorpus(objCorpus).size())
                {
                    cout << "psh.processarCorpus: Erro\n";
                }

                //atualiza atributos de treino (d-1, d-2...d-n)
                for (int d=inicio_janela; d<=valores_janelas[j]; d++){
                    std::stringstream out;
                    out << "d-" << d;
                    atributosTreino.push_back(out.str());
                }
                //marco o proximo valor a ser calculado, na proxima iteracao
                inicio_janela = valores_janelas[j] + 1;
                //atualiza janela atual
                janela = valores_janelas[j];
                psh.atualizarJanela(janela);

                /****************************************** Base Line System ******************************************/

                    if (bls) {
                        //só executa na primeira vez, para este baseline
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

                        } //se nao for primeira vez, pega memoria
                        else{
                            cout << " BLS: " << auxexecbls << "%"  ;
                            outfile << auxexecbls << ";";
                        }

                    }
                    else{
                        outfile << "-1;";
                    }

                /********************************************* LibSVM **********************************************/

                    if (svm) {

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
                        outfile << "-1;";
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
                        outfile << "-1;";
                    }
                /********************************* Regressão Logística (Gradiente) ************************************/

                    if (reglog) {

                        //thetas_mini.resize(M+1);
                        //fui obrigado a comentar a linha seguinte pois a regressao logistica do FAMA não possui esses parametros
                        //objTreino.ajustarParametros(e, alpha, lamb, Jmin, iter, atributosTreino);
                        objClassRegLog = objTreino.executarTreinamento(objCorpus, iResposta);


                        objClassRegLog->executarClassificacao(objCorpus, iSaidaRegLog);
                        //cout << objClassRegLog->descricaoConhecimento();

                        acuracia = 100.*objAvalAcur.calcularDesempenho(objCorpus, iResposta, iSaidaRegLog)[0];
                        cout << " RL: " << acuracia << "%"  ;
                        outfile << acuracia << ";";


                        //out << acuracia; s = out.str();

                    }
                    else{
                        outfile << "-1;";
                    }


                    //objLSVM.~Treinador();
                    cout << endl;
            } //fim j - janela
            cout << endl;
            outfile << ";" << endl ;
        } //fim i - codigo ativo

        outfile.flush();
        outfile.close();
        objCorpus.gravarArquivo( "../inputs/#corpus_final.txt" );
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





