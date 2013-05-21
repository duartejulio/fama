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
#include "../treinador/reglog.h"
#include "../validador/validadorkdobras.h"
#include "../validador/validadorkdobras_deslizante.h"
#include "../classificador/classificadorbls.h"

using namespace std;

/**************************** DECLARAÇÃO DE VARIÁVEIS *****************************/

vector<string> atributosTreino;             //representa os atributos de treinamento (valor, fechamento, abertura, d-1, d-2...)
int iResposta;                              //índice da resposta (atributo objetivo)
int iSaidaNB;                               //índice da saida do algoritmo NB
int iSaidaBLS;                              //índice da saida do algoritmo BLS
int iSaidaSVM;                              //índice da saida do algoritmo Support Vector Machine
int iSaidaRegLog;                           //índice da saida do algoritmo Regressão Logistica
float acuracia = 0.0;                       //calcula acuracia do algoritmo
bool svm = true;                                   //executa algoritmo Support Vector Machine
bool nb = false;                                    //executa algoritmo Naive Bayes
bool bls = false;                                   //executa algortimo Base Line System
bool reglog = false;                                //executa algoritmo Regressão Logística
bool svm_validacao_cruzada = true;                 //objeto avaliador de acurácia
bool reglog_validacao_cruzada = false;
bool nb_validacao_cruzada = false;
int dobras = 5;
AvaliadorAcuracia objAvalAcur;              //objeto do framework avaliador de acuracia
stringstream out;                           //auxiliar para manipular strings
struct svm_parameter param;                 //auxiliar para integracao com SVM
int iter;                                   // auxiliar regressao logistica
unsigned int i, j;                          //variaveis auxiliares
string auxexecbls;                          //manter o valor do BLS
                    //quantidade de itens no vetor de ativos
                    //quantidade de itens no vetor da janela
vector<int> valores_janelas(8);        //vetor das janelas a serem testadas
vector<string> valores_codigoativo(50); //50 -vetor dos ativos a serem testados
vector<string> classes;                         //representa as classes, positivas (+1) e negativa (-1)

std::stringstream ssouttela;
//float **MATRIX_BEST_WINDOW;


int main()
{

 /*
    Estrutura do Corpus (new)
    1:   valor
    2:   d-1
    3:   d-2
    n:   d-n
    n+1: y (+1,-1)
    n+2: saida_nb (+1,-1,0)
    Estrutura do Corpus (old)
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


    /**************************** PARAMETROS DE ENTRADA DO PROGRAMA *****************************/
    valores_janelas[0] = 3;
    valores_janelas[1] = 5;
    valores_janelas[2] = 10;
    valores_janelas[3] = 15;
    valores_janelas[4] = 20;
    valores_janelas[5] = 40;
    valores_janelas[6] = 60;
    valores_janelas[7] = 80;


    //nome dos arquivos texto com serie devem seguir este sufixo
    //MATRIX_BEST_WINDOW = new float*[51];

    valores_codigoativo[0] = "ALLL11";
    valores_codigoativo[1] = "LIGT3";
    valores_codigoativo[2] = "PETR4";
    valores_codigoativo[3] = "VIVO4";
    valores_codigoativo[4] = "VALE5";
    valores_codigoativo[5] = "ARCZ6";
    valores_codigoativo[6] = "AMBV4";
    valores_codigoativo[7] = "BBAS3";
    valores_codigoativo[8] = "BBDC4";
    valores_codigoativo[9] = "BNCA3";
    valores_codigoativo[10] = "BRAP4";
    valores_codigoativo[11] = "BRKM5";
    valores_codigoativo[12] = "BRTO4";
    valores_codigoativo[13] = "CCRO3";
    valores_codigoativo[14] = "CGAS5";
    valores_codigoativo[15] = "CLSC6";
    valores_codigoativo[16] = "CMIG4";
    valores_codigoativo[17] = "CPFE3";
    valores_codigoativo[18] = "CPLE6";
    valores_codigoativo[19] = "CRUZ3";
    valores_codigoativo[20] = "CSAN3";
    valores_codigoativo[21] = "CSNA3";
    valores_codigoativo[22] = "CYRE3";
    valores_codigoativo[23] = "DURA4";
    valores_codigoativo[24] = "ELET6";
    valores_codigoativo[25] = "EMBR3";
    valores_codigoativo[26] = "GGBR4";
    valores_codigoativo[27] = "GOLL4";
    valores_codigoativo[28] = "ITAU4";
    valores_codigoativo[29] = "ITSA4";
    valores_codigoativo[30] = "KLBN4";
    valores_codigoativo[31] = "LAME4";
    valores_codigoativo[32] = "LREN3";
    valores_codigoativo[33] = "NATU3";
    valores_codigoativo[34] = "NETC4";
    valores_codigoativo[35] = "PCAR4";
    valores_codigoativo[36] = "PRGA3";
    valores_codigoativo[37] = "RSID3";
    valores_codigoativo[38] = "SBSP3";
    valores_codigoativo[39] = "SDIA4";
    valores_codigoativo[40] = "TAMM4";
    valores_codigoativo[41] = "TCSL4";
    valores_codigoativo[42] = "TMCP4";
    valores_codigoativo[43] = "TLPP4";
    valores_codigoativo[44] = "TNLP4";
    valores_codigoativo[45] = "TRPL4";
    valores_codigoativo[46] = "UBBR11";
    valores_codigoativo[47] = "UGPA4";
    valores_codigoativo[48] = "USIM5";
    valores_codigoativo[49] = "VCPA4";


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


    /**************************** INICIO DO PROGRAMA *****************************/
    //separarValores = trim
    //dividirExemplos = separa cada linha do corpus como um exemplo (TRUE: não alterar)
    //se colocar dividirExemplos = TRUE e usar separados errado (ex a virgula, para pegar quantidade menor) entao da problema.
    //ele se perde na divisao de exemplos

    std::string s;
    //arquivo auxiliar para analise posterior
    ofstream outfileCVS;
    //ofstream outfileK;

    try{

        classes.push_back("-1");
        classes.push_back("+1");

        outfileCVS.open("../outputs/saida.txt", fstream::out);
        //outfileK.open("../outputs/saida_k.txt", fstream::out);

        outfileCVS.clear();
        //outfileK.clear();

        outfileCVS << "ATIVO;JANELA;BLS;SVM;SVM_K;NB;NB_K;RL;RL_K" << endl;


        for (i=0; i<valores_codigoativo.size();i++){

            //MATRIX_BEST_WINDOW[i] = new float[4]; //4 algoritmos

            ssouttela << "******************************************" << endl ;
            ssouttela << ":: Processando Ativo: " << valores_codigoativo[i] << endl ;
            ssouttela << "******************************************" << endl ;

            outfileCVS << valores_codigoativo[i] << ";";
            cout << ssouttela.str();
            //outfileK << ssouttela.str();
            ssouttela.clear();

            //realiza a execucao com distintos parametros de janelas j para o ativo i
            int inicio_janela = 1;
            for (j=0; j<valores_janelas.size();j++){

                CorpusMatriz objCorpus(vector<string>(), ';', true, true);
                atributosTreino.clear();

                objCorpus.carregarArquivo( "../inputs/bolsasp/ativos/ativos_" + valores_codigoativo[i] );

                //informa maior janela a ser executada e ação a ser lida vazia, inicialmente
                ProcessadorSerieHistorica psh(valores_janelas[j], "valor");
                //cria atributos a serem utilizados como parametros (d-1, d-2, d-..n)
                //psh.criarAtributosAuxiliares(objCorpus, inicio_janela,valores_janelas[j]);
                psh.criarAtributosAuxiliares(objCorpus, 1, valores_janelas[j]);
                //seta os valores dos parametros d-1, d-2, d-n + y no corpus para o ativo em questao e zera as saidas
                if (!psh.processarCorpus(objCorpus).size())
                    { cout << "psh.processarCorpus: Erro\n";}

                iResposta    = objCorpus.pegarPosAtributo("y");
                iSaidaBLS    = objCorpus.pegarPosAtributo("saida_bls");
                iSaidaNB     = objCorpus.pegarPosAtributo("saida_nb");
                iSaidaRegLog = objCorpus.pegarPosAtributo("saida_reglog");
                iSaidaSVM    = objCorpus.pegarPosAtributo("saida_svm");

                //log
                outfileCVS << valores_janelas[j] << ";";
                ssouttela << "    d-" << valores_janelas[j] << " = " << endl ;
                //outfileK << ssouttela.str();
                cout << ssouttela.str();
                ssouttela.clear();

                //atualiza atributos de treino (d-1, d-2...d-n)
                //for (int d=inicio_janela; d<=valores_janelas[j]; d++){
                for (int d=1; d<=valores_janelas[j]; d++){
                    std::stringstream out;
                    out << "d-" << d;
                    atributosTreino.push_back(out.str());
                }

                //teste com valores base
                atributosTreino.push_back("maximo");
                atributosTreino.push_back("minimo");
                atributosTreino.push_back("abertura");


                inicio_janela = valores_janelas[j] + 1;

                //teste retirar isto
                //std::stringstream outsaidaarq;
                //outsaidaarq << "../outputs/#corpus_processado_" << valores_codigoativo[i] << "_" << valores_janelas[j] << ".txt";
                //objCorpus.gravarArquivo(outsaidaarq.str());

                /** Base Line System **/

                if (bls) {
                    if (j==0){
                        ClassificadorBLS *cbls;
                        cbls = new ClassificadorBLS(classes);
                        cbls->executarClassificacao(objCorpus, iSaidaBLS);
                        //cout << cbls->descricaoConheciatributo_atualmento();
                        acuracia = 100.*objAvalAcur.calcularDesempenho(objCorpus, iResposta, iSaidaBLS)[0];
                        stringstream tmp;
                        tmp << acuracia/100;
                        auxexecbls = tmp.str();
                        cout << " BLS: " << acuracia << "%"  ;
                        outfileCVS << acuracia/100 << ";";
                        delete cbls;

                    } //se nao for primeira vez, pega memoria
                    else{
                        cout << " BLS: " << auxexecbls << "%"  ;
                        outfileCVS << auxexecbls << ";";
                    }

                }
                else{
                    outfileCVS << "0;";
                }

                /** LibSVM **/
                if (svm) {

                    Classificador *objClassLibSvm;
                    LibSvm objLSVM(atributosTreino, classes, param);
                    objClassLibSvm = objLSVM.executarTreinamento(objCorpus, iResposta);
                    objClassLibSvm->executarClassificacao(objCorpus, iSaidaSVM);
                    ////cout << objClassLibSvm->descricaoConhecimento();
                    acuracia = 100.*objAvalAcur.calcularDesempenho(objCorpus, iResposta, iSaidaSVM)[0];
                    cout << " SVM sem validacao cruzada!: " << acuracia << "%"  ;
                    outfileCVS << acuracia/100 << ";";
                    delete objClassLibSvm;

                    if (svm_validacao_cruzada){

//                        ValidadorKFoldDeslizante objValidadorSVM(objAvalAcur, dobras);
//                        vector< vector< float > > v = objValidadorSVM.executarExperimento(objLSVM, objCorpus, iResposta, iSaidaSVM);
//                        float c,soma_acuracia = 0;
//                        for (c=0;c<dobras - 1;c++){
//                            acuracia = 100.* v[c][0];
//                            ssouttela << c+1 << " validacao: - " << acuracia << "%" << endl;
//                            cout << ssouttela.str();
//                            //outfileK << ssouttela.str();
//                            ssouttela.clear();
//                            soma_acuracia += v[c][0];
//                        }
//                        ssouttela << " Media SVM " << dobras << "-dobras: " << 100.*(soma_acuracia/(dobras - 1)) << "%" << endl  ;
//                        cout << ssouttela.str();
//                        //outfileK << ssouttela.str();
//                        ssouttela.clear();
//
//                        outfileCVS << (soma_acuracia/(dobras - 1)) << ";" ;

//                            //  TESTE DE EXPERIMENTO2
//                            ValidadorKFoldDeslizante objValidadorSVM(objAvalAcur, dobras);
//                            int tamanho_janela_deslizante = 80;
//                            vector< vector< float > > v = objValidadorSVM.executarExperimento2(objLSVM, objCorpus, iResposta, iSaidaSVM, tamanho_janela_deslizante);
//                            float c,soma_acuracia = 0;
//                            int tot = objCorpus.pegarQtdSentencas() - tamanho_janela_deslizante ;
//                            for (c=0; c < tot  ;c++){
//                                acuracia = 100.* v[c][0];
//                                ssouttela << c+1 << " validacao: " << acuracia << "%" << endl;
//                                cout << ssouttela.str();
//                                //outfileK << ssouttela.str();
//                                ssouttela.clear();
//                                soma_acuracia += v[c][0];
//                            }
//                            ssouttela << " Media SVM " << dobras << " dobras: " << 100.*(soma_acuracia/tot) << "%" << endl  ;
//                            cout << ssouttela.str();
//                            //outfileK << ssouttela.str();
//                            ssouttela.clear();
//
//                            outfileCVS << (soma_acuracia/tot-1) << ";" ;

                                //TESTE DE EXPERIMENTO3
                                ValidadorKFoldDeslizante objValidadorSVM(objAvalAcur, dobras);
                                int tamanho_treino = 80;
                                vector< vector< float > > v = objValidadorSVM.executarExperimento3(objLSVM, objCorpus, iResposta, iSaidaSVM, tamanho_treino);
                                acuracia = 100.* v[0][0];
                                ssouttela << " validacao " << dobras << " dobras: " << acuracia << "%" << endl;
                                cout << ssouttela.str();
                                //outfileK << ssouttela.str();
                                ssouttela.clear();

                                //outfileK << ssouttela.str();

                                outfileCVS << (acuracia) << ";" ;

                                //FIM TESTE DE EXPERIMENTO3


                    }
                    else{
                        outfileCVS << "0;";
                    }

                    //objLSVM.~Treinador();

                }
                else{
                    outfileCVS << "0;0;";
                }

                /** Naive Bayes **/

                if (nb) {
                    Classificador *objClass;
                    NaiveBayes objNB(atributosTreino, classes);
                    objClass = objNB.executarTreinamento(objCorpus, iResposta);
                    objClass->executarClassificacao(objCorpus, iSaidaNB);
                    //cout << objClass->descricaoConhecimento();

                    acuracia = 100.*objAvalAcur.calcularDesempenho(objCorpus, iResposta, iSaidaNB)[0];
                    cout << " NB: " << acuracia << "%"  << endl;
                    outfileCVS << acuracia/100 << ";";

                    delete objClass;
                    if (nb_validacao_cruzada){

                        ValidadorKFoldDeslizante objValidadorNB(objAvalAcur, dobras);
                        vector< vector< float > > v = objValidadorNB.executarExperimento(objNB, objCorpus, iResposta, iSaidaNB);
                        float c,soma_acuracia = 0;
                        for (c=0;c<dobras - 1;c++){
                            acuracia = 100.* v[c][0];
                            ssouttela << c+1 << " validacao: - " << acuracia << "%" << endl;
                            cout << ssouttela.str();
                            //outfileK << ssouttela.str();
                            ssouttela.clear();
                            soma_acuracia += v[c][0];
                        }

                        ssouttela << " Media NB " << dobras << "-dobras: " << 100.*(soma_acuracia/(dobras - 1)) << "%" << endl  ;
                        cout << ssouttela.str();
                        //outfileK << ssouttela.str();
                        ssouttela.clear();
                        outfileCVS << (soma_acuracia/(dobras - 1)) << ";" ;

                    }
                    else{
                        outfileCVS << "0;";
                    }

                }
                else{
                    outfileCVS << "0;0;";
                }
                /** Regressão Logística (Gradiente) **/

                if (reglog) {

                    //objCorpus.gravarArquivo( "../outputs/#corpusfull" + valores_codigoativo[i] + ".txt" );

                    Classificador *objClassRegLog;
                    //RegressaoLogistica oTRL(atributosTreino, classes);
                    RegressaoLogistica objRL(classes);
                    objClassRegLog = objRL.executarTreinamento(objCorpus, iResposta);
                    objClassRegLog->executarClassificacao(objCorpus, iSaidaRegLog);
                    acuracia = 100.*objAvalAcur.calcularDesempenho(objCorpus, iResposta, iSaidaRegLog)[0];
                    cout << " Regressao Logistica: " << acuracia << "%"  ;
                    outfileCVS << acuracia/100 << ";";
                    //oTRL.~RegressaoLogistica();
                    delete objClassRegLog;
                    //out << acuracia; s = out.str();

                    if (reglog_validacao_cruzada){

                        ValidadorKFoldDeslizante objValidadorRL(objAvalAcur, dobras);
                        vector< vector< float > > v = objValidadorRL.executarExperimento(objRL, objCorpus, iResposta, iSaidaRegLog);
                        float c,soma_acuracia = 0;
                        for (c=0;c<dobras - 1;c++){
                            acuracia = 100.* v[c][0];
                            ssouttela << c+1 << " validacao: - " << acuracia << "%" << endl;
                            cout << ssouttela.str();
                            //outfileK << ssouttela.str();
                            ssouttela.clear();
                            soma_acuracia += v[c][0];
                        }

                        ssouttela << " Media RL " << dobras << "-dobras: " << 100.*(soma_acuracia/(dobras - 1)) << "%" << endl  ;
                        cout << ssouttela.str();
                        //outfileK << ssouttela.str();
                        ssouttela.clear();

                        outfileCVS << (soma_acuracia/(dobras - 1)) << ";" ;
                    }
                    else{
                        outfileCVS << "0;";
                    }

                    }
                else{
                    outfileCVS << "0;0;";
                }

                cout << endl;

        } //fim j - janela
        cout << endl;
        outfileCVS << ";" << endl ;

        ////temporario!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //objCorpus.gravarArquivo( "../outputs/#fim_corpus_" + valores_codigoativo[i] + ".txt" );


        } //fim i - codigo ativo

        outfileCVS.flush();
        outfileCVS.close();
        //outfileK.flush();
        //outfileK.close();

        cout << "Fim da execucao dos algoritmos. Pressione ENTER" ;

        getchar();
        return 0;

        }catch(string err){
            if (outfileCVS.is_open())
            {
                outfileCVS.close();
            }
            //if (outfileK.is_open())
            //{
            //    outfileK.close();
            //}
            cout << err;
            return 1;
        }

}




