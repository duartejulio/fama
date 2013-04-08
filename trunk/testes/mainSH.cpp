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
#include "../validador/validadorkdobras_deslizante.h"
#include "../classificador/classificadorbls.h"

using namespace std;

/**************************** DECLARA��O DE VARI�VEIS *****************************/

string atributo_atual;                    //nome do atributo do valor do ativo no dia D (ex.: valor_petr4)
vector<string> atributosTreino;             //representa os atributos de treinamento (valor, fechamento, abertura, d-1, d-2...)

int iResposta;                              //�ndice da resposta (atributo objetivo)

int iSaidaNB;                               //�ndice da saida do algoritmo NB
int iSaidaBLS;                              //�ndice da saida do algoritmo BLS
int iSaidaSVM;                              //�ndice da saida do algoritmo Support Vector Machine
int iSaidaRegLog;                           //�ndice da saida do algoritmo Regress�o Logistica

float acuracia = 0.0;                       //calcula acuracia do algoritmo
int janela;                                 //janela atual da execucao do algoritmo

bool svm;                                   //executa algoritmo Support Vector Machine
bool nb;                                    //executa algoritmo Naive Bayes
bool bls;                                   //executa algortimo Base Line System
bool reglog;                                //executa algoritmo Regress�o Log�stica
bool svm_validacao_cruzada;

AvaliadorAcuracia objAvalAcur;              //objeto do framework avaliador de acuracia
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

int janela_max = 100;                       //tamanho maximo da janela do processamento
int qtd_ativos = 6;                         //quantidade de itens no vetor de ativos
int qtd_janela = 8;                         //quantidade de itens no vetor da janela

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
    valores_janelas[7] = 100;

    valores_codigoativo[0] = "alll11";
    valores_codigoativo[1] = "ligt3";
    valores_codigoativo[2] = "petr4";
    valores_codigoativo[3] = "vivo4";
    valores_codigoativo[4] = "vale5";
    valores_codigoativo[5] = "arcz6";

    //define quais algoritmos ser�o executados
    svm = false;
    nb = false;
    bls = false;
    reglog = false;
    svm_validacao_cruzada = true;

    /**************************** INICIO DO PROGRAMA *****************************/
    //dividirExemplos = separa cada linha do corpus como um exemplo (TRUE: n�o alterar)
    //separarValores = trim

    CorpusMatriz objCorpus(vector<string>(), ';', true, true);


    classes.push_back("-1");
    classes.push_back("+1");

    objCorpus.carregarArquivo( "../inputs/ativos_completos_bvmf" );

    //informa maior janela a ser executada e a��o a ser lida vazia, inicialmente
    ProcessadorSerieHistorica psh(janela_max, "");

    //cria atributos a serem utilizados como parametros (y, d-1, d-2, d-..n) + saidas de algoritmos
    psh.criarAtributosAuxiliares(objCorpus);
    //obtendo referencia em memoria para os atributos
    iResposta = objCorpus.pegarPosAtributo("y");
    iSaidaNB = objCorpus.pegarPosAtributo("saida_nb");
    iSaidaBLS = objCorpus.pegarPosAtributo("saida_bls");
    iSaidaSVM = objCorpus.pegarPosAtributo("saida_svm");
    iSaidaRegLog = objCorpus.pegarPosAtributo("saida_reglog");
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
    cbls = new ClassificadorBLS(classes);
    std::string s;
    //arquivo auxiliar para analise posterior
    ofstream outfile;
    ofstream outfile2;

    outfile.open("../outputs/saida.txt", fstream::out);
    outfile2.open("../outputs/saida_k.txt", fstream::out);

    outfile.clear();
    outfile2.clear();

    outfile << "ATIVO;JANELA;BLS;SVM;SVM_K;NB;REGLOG;" << endl;

    try{

        for (i=0; i<valores_codigoativo.size();i++){

            outfile << valores_codigoativo[i] << ";";

            atributo_atual = "valor_" + valores_codigoativo[i];
            psh.atualizarAtributo(atributo_atual);
            cout << "******************************************" << endl ;
            cout << ":: Processando Ativo: " << valores_codigoativo[i] << endl ;
            cout << "******************************************" << endl ;

            outfile2 << "******************************************" << endl ;
            outfile2 << ":: Processando Ativo: " << valores_codigoativo[i] << endl ;
            outfile2 << "******************************************" << endl ;


            //limpando o vetor de atributos de treinamento
            atributosTreino.clear();

            //seta os valores dos parametros d-1, d-2, d-n + y no corpus para o ativo em questao
            if (!psh.processarCorpus(objCorpus).size())
            {
                cout << "psh.processarCorpus: Erro\n";
            }


            //realiza a execucao com distintos parametros de janelas j para o ativo i
            int inicio_janela = 1;
            for (j=0; j<valores_janelas.size();j++){
                //log
                outfile << valores_janelas[j] << ";";

                outfile2 << "janela: " << valores_janelas[j] << ";" << endl ;

                cout << ":: d-" << valores_janelas[j] << " = " ;

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
                        //s� executa na primeira vez, para este baseline
                        if (j==0){

                            cbls->atualizarValorEmD(atributo_atual);
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
                        ////cout << objClassLibSvm->descricaoConhecimento();
                        acuracia = 100.*objAvalAcur.calcularDesempenho(objCorpus, iResposta, iSaidaSVM)[0];

                        cout << " SVM sem validacao cruzada!: " << acuracia << "%"  ;
                        outfile << acuracia << ";";

                    }
                    else{
                        outfile << "-1;";
                    }

                     if (svm_validacao_cruzada){

                        objLSVM.atualizarAtributosTreino(atributosTreino);

                        int dobras = 12;
                        ValidadorKFoldDeslizante objValidador(objAvalAcur, dobras);
                        vector< vector< float > > v = objValidador.executarExperimento(objLSVM, objCorpus, iResposta, iSaidaSVM);
                        float c,soma_acuracia = 0;
                        for (c=0;c<dobras - 1;c++){
                            acuracia = 100.* v[c][0];
                            cout << c+1 << " validacao: - " << acuracia << "%" << endl;
                            outfile2 << c+1 << " validacao: - " << acuracia << "%" << endl;
                            soma_acuracia += v[c][0];
                        }

                        cout << " Media SVM k-dobras: " << 100.*(soma_acuracia/(dobras - 1)) << "%"  ;
                        outfile2 << "k=" << dobras << endl ;
                        outfile2 << " Media SVM k-dobras: " << 100.*(soma_acuracia/(dobras - 1)) << "%" << endl  ;

                        outfile << 100.*(soma_acuracia/(dobras - 1)) << ";" ;
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
                /********************************* Regress�o Log�stica (Gradiente) ************************************/

                    if (reglog) {

                        //thetas_mini.resize(M+1);
                        //fui obrigado a comentar a linha seguinte pois a regressao logistica do FAMA n�o possui esses parametros
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

            //temporario!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            objCorpus.gravarArquivo( "../inputs/#2corpus_" + valores_codigoativo[i] + ".txt" );

        } //fim i - codigo ativo

        outfile.flush();
        outfile.close();

        psh.~ProcessadorSerieHistorica();

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





