#include <iostream>
#include <iomanip>
#include <dirent.h>
#include <cstdlib>
#include <string>

#include <opencv/cv.h>
#include <opencv/highgui.h>

#include "../corpus/corpusmatriz.h"
#include "../treinador/treinador.h"
#include "../classificador/classificador.h"
#include "../treinador/libsvm.h"
#include "../avaliador/avaliador_acuracia.h"

using namespace cv;
using namespace std;

string processarImagem(char path_image[],int height,int width,int colors,string classe)
{
    Mat image = imread(path_image);

    /* Pré-processamento */
    Mat image_resized;
    resize(image,image_resized,Size(width,height),0,0,INTER_LINEAR);

    vector<Mat> planes;
    split(image_resized,planes);

    vector<Mat> outplanes(planes.size());

    for(size_t i = 0;i < planes.size();i++)
    {
        planes[i].convertTo(planes[i],CV_32FC1);
        dct(planes[i],outplanes[i]);
    }

    stringstream sstm;

    int tam = width*height*colors;
    int ii = 0;

    for(int k = 0;k < colors;k++)
    {
        for(int i = 0;i < outplanes[k].rows;i++)
        {
            for(int j = 0;j < outplanes[k].cols;j++)
            {
                sstm << (float)outplanes[k].at<uchar>(i,j) << ";";

                ii++;
                tam--;
            }
        }
    }

    //sstm << classe << ";";
    sstm << classe;

    string image_line = sstm.str();

    return image_line;
}

int carregarImagens(char path_input[],char path_output_arq[],int height,int width,int colors,bool classificar = false)
{
    struct dirent **namelist_class;
    struct dirent **namelist_img;
    struct dirent **namelist_neg;
    struct dirent **namelist_img_neg;

    int nclass,nimg,nneg,nimgneg;

    char path_arq[100];

    cout << "\nCarregando imagens a serem treinadas... \n";

    nclass = scandir(path_input,&namelist_class,0,alphasort);

    if(nclass < 0)
        perror("scandir");
    else
    {
        while(nclass--)
        {
            char path_class[100];

            strcpy(path_class,path_input);
            strcat(path_class,namelist_class[nclass]->d_name);
            strcat(path_class,"/");

            if(!strstr(path_class,"."))
            {
                cout << "     - " << path_class << " \n";

                strcpy(path_arq,path_output_arq);
                strcat(path_arq,"imagens_");
                strcat(path_arq,namelist_class[nclass]->d_name);

                ofstream arqout(path_arq);

                //imagens +1
                nimg = scandir(path_class,&namelist_img,0,alphasort);

                if(nimg < 0)
                    perror("scandir");
                else
                {
                    while(nimg--)
                    {
                        if(strlen(namelist_img[nimg]->d_name) > 2)
                        {
                            char path_img[100];

                            strcpy(path_img,path_class);
                            strcat(path_img,namelist_img[nimg]->d_name);

                            string image_line = processarImagem(path_img,height,width,colors,"+1");
                            arqout << image_line << endl;
                        }

                        free(namelist_img[nimg]);
                    }
                    free(namelist_img);
                }

                //imagens -1
                nneg = scandir(path_input,&namelist_neg,0,alphasort);

                if(nneg < 0)
                    perror("scandir");
                else
                {
                    while(nneg--)
                    {
                        char path_neg[100];

                        strcpy(path_neg,path_input);
                        strcat(path_neg,namelist_neg[nneg]->d_name);
                        strcat(path_neg,"/");

                        if(!strstr(path_neg,"."))
                        {
                            if(strcmp(path_neg,path_class) != 0)
                            {
                                nimgneg = scandir(path_neg,&namelist_img_neg,0,alphasort);

                                if(nimgneg < 0)
                                    perror("scandir");
                                else
                                {
                                    while(nimgneg--)
                                    {
                                        if(strlen(namelist_img_neg[nimgneg]->d_name) > 2)
                                        {
                                            char path_img_neg[100];

                                            strcpy(path_img_neg,path_neg);
                                            strcat(path_img_neg,namelist_img_neg[nimgneg]->d_name);

                                            string image_line = processarImagem(path_img_neg,height,width,colors,"-1");
                                            arqout << image_line << endl;
                                        }

                                        free(namelist_img_neg[nimgneg]);
                                    }
                                    free(namelist_img_neg);
                                }
                            }else{
                                //cout << path_neg << " == " << path_class << "\n";
                            }
                        }
                        free(namelist_neg[nneg]);
                    }
                    free(namelist_neg);
                }

                arqout.close();
            }

            free(namelist_class[nclass]);
        }
        free(namelist_class);
    }

    cout << "\nArquivos imagens_<diretorio> criados com sucesso! \n";

    return 0;
}

int main()
{
    int height = 16;
    int width = 16;
    int colors = 3;

    bool loadImages = false;
    bool trainStart = true;

    char path_input[] = "/home/diego/workspace/FAMA/inputs/";
    char path_output[] = "/home/diego/workspace/FAMA/outputs/";

    char path_train[] = "/home/diego/workspace/FAMA/inputs/train-edited/";
    char path_test[] = "/home/diego/workspace/FAMA/inputs/test-edited/";

    vector<string> classes;
    classes.push_back("+1");
    classes.push_back("-1");

    Classificador *objClassLibSvm_A;
    Classificador *objClassLibSvm_B;
    Classificador *objClassLibSvm_C;
    Classificador *objClassLibSvm_Five;
    Classificador *objClassLibSvm_Point;
    Classificador *objClassLibSvm_V;

    cout << "Buscando classes...\n";

    vector<string> classesNames;

    struct dirent **namelist_class;
    int nclass = scandir(path_train,&namelist_class,0,alphasort);

    if(nclass < 0)
        perror("scandir");
    else
    {
        int i = 0;
        while(i < nclass)
        {
            if(!strstr(namelist_class[i]->d_name,"."))
            {
                cout << "   - Classe " << namelist_class[i]->d_name << " encontrada. \n";
                classesNames.push_back(namelist_class[i]->d_name);
            }
            i++;
        }
        free(namelist_class);
    }

    char path_arq[100];

    if(loadImages)
    {
        cout << "\n\nCriando arquivos...\n";

        strcpy(path_arq,path_input);
        strcat(path_arq,"/train-txt/");

        carregarImagens(path_train,path_arq,width,height,colors);

        strcpy(path_arq,path_input);
        strcat(path_arq,"/test-txt/");

        carregarImagens(path_test,path_arq,width,height,colors);
        //carregarImagensClassificar(path_classify,path_input,width,height,colors,classesNames);
    }

    if(trainStart)
    {
        cout << "\n\nTreinamento: \n";

        //Criação do corpus para treinamento
        vector<string> atributos;

        for(int i=0;i < (width*height*colors);i++)
        {
            stringstream ss;
            ss << i;

            atributos.push_back(ss.str());
        }
        atributos.push_back("classe");

        //CorpusMatriz objCorpus(atributos,';',true,true);
        CorpusMatriz objCorpus_A(atributos,';',true,true);
        CorpusMatriz objCorpus_B(atributos,';',true,true);
        CorpusMatriz objCorpus_C(atributos,';',true,true);
        CorpusMatriz objCorpus_Five(atributos,';',true,true);
        CorpusMatriz objCorpus_Point(atributos,';',true,true);
        CorpusMatriz objCorpus_V(atributos,';',true,true);

        strcpy(path_arq,path_input);
        strcat(path_arq,"train-txt/imagens_A");

        cout << "\nCarregando corpus...\n" << path_arq << "\n\n";
        objCorpus_A.carregarArquivo(path_arq);

        strcpy(path_arq,path_input);
        strcat(path_arq,"train-txt/imagens_B");

        cout << "\nCarregando corpus...\n" << path_arq << "\n\n";
        objCorpus_B.carregarArquivo(path_arq);

        strcpy(path_arq,path_input);
        strcat(path_arq,"train-txt/imagens_C");

        cout << "\nCarregando corpus...\n" << path_arq << "\n\n";
        objCorpus_C.carregarArquivo(path_arq);

        strcpy(path_arq,path_input);
        strcat(path_arq,"train-txt/imagens_Five");

        cout << "\nCarregando corpus...\n" << path_arq << "\n\n";
        objCorpus_Five.carregarArquivo(path_arq);

        strcpy(path_arq,path_input);
        strcat(path_arq,"train-txt/imagens_Point");

        cout << "\nCarregando corpus...\n" << path_arq << "\n\n";
        objCorpus_Point.carregarArquivo(path_arq);

        strcpy(path_arq,path_input);
        strcat(path_arq,"train-txt/imagens_V");

        cout << "\nCarregando corpus...\n" << path_arq << "\n\n";
        objCorpus_V.carregarArquivo(path_arq);

        struct svm_parameter param;
        param.svm_type = C_SVC;
        param.kernel_type = RBF;
        param.degree = 0;               // for poly
        param.gamma = 20;               // for poly/rbf/sigmoid
        param.coef0 = 0;                // for poly/sigmoid
        param.nu = 0.5;                 // for NU_SVC, ONE_CLASS, and NU_SVR
        param.cache_size = 1024;        // in MB
        param.C = 1024;                   // for C_SVC, EPSILON_SVR, and NU_SVR
        param.eps = 1e-6;               // stopping criteria
        param.p = 0.0;                  // for EPSILON_SVR
        param.shrinking = 1;            // use the shrinking heuristics
        param.probability = 1;
        param.nr_weight = 0;            // for C_SVC
        param.weight_label = NULL;      // for C_SVC
        param.weight = NULL;            // for C_SVC

        int idAtribClasse;

        idAtribClasse = objCorpus_A.pegarPosAtributo("classe");

        LibSvm objLSVM(atributos,classes,param);

        //Executa o treinamento passando a posição da classe no arquivo imagens_A
        objClassLibSvm_A = objLSVM.executarTreinamento(objCorpus_A,idAtribClasse);
        objClassLibSvm_B = objLSVM.executarTreinamento(objCorpus_B,idAtribClasse);
        objClassLibSvm_C = objLSVM.executarTreinamento(objCorpus_C,idAtribClasse);
        objClassLibSvm_Five = objLSVM.executarTreinamento(objCorpus_Five,idAtribClasse);
        objClassLibSvm_Point = objLSVM.executarTreinamento(objCorpus_Point,idAtribClasse);
        objClassLibSvm_V = objLSVM.executarTreinamento(objCorpus_V,idAtribClasse);

        cout << "\n\nClassificação: \n";

        //Criação do corpus para classificação
        //Criação do corpus para treinamento
        vector<string> atributosProva;

        for(int i=0;i < (width*height*colors);i++)
        {
            stringstream ss;
            ss << i;

            atributosProva.push_back(ss.str());
        }
        atributosProva.push_back("classe");

        //CorpusMatriz objCorpusProva(atributosProva,';',true,true);
        CorpusMatriz objCorpusProva_A(atributosProva,';',true,true);
        CorpusMatriz objCorpusProva_B(atributosProva,';',true,true);
        CorpusMatriz objCorpusProva_C(atributosProva,';',true,true);
        CorpusMatriz objCorpusProva_Five(atributosProva,';',true,true);
        CorpusMatriz objCorpusProva_Point(atributosProva,';',true,true);
        CorpusMatriz objCorpusProva_V(atributosProva,';',true,true);

        strcpy(path_arq,path_input);
        strcat(path_arq,"/test-txt/imagens_A");

        cout << "\nCarregando corpus...\n" << path_arq << "\n\n";
        objCorpusProva_A.carregarArquivo(path_arq);

        strcpy(path_arq,path_input);
        strcat(path_arq,"test-txt/imagens_B");

        cout << "\nCarregando corpus...\n" << path_arq << "\n\n";
        objCorpusProva_B.carregarArquivo(path_arq);

        strcpy(path_arq,path_input);
        strcat(path_arq,"test-txt/imagens_C");

        cout << "\nCarregando corpus...\n" << path_arq << "\n\n";
        objCorpusProva_C.carregarArquivo(path_arq);

        strcpy(path_arq,path_input);
        strcat(path_arq,"test-txt/imagens_Five");

        cout << "\nCarregando corpus...\n" << path_arq << "\n\n";
        objCorpusProva_Five.carregarArquivo(path_arq);

        strcpy(path_arq,path_input);
        strcat(path_arq,"test-txt/imagens_Point");

        cout << "\nCarregando corpus...\n" << path_arq << "\n\n";
        objCorpusProva_Point.carregarArquivo(path_arq);

        strcpy(path_arq,path_input);
        strcat(path_arq,"test-txt/imagens_V");

        cout << "\nCarregando corpus...\n" << path_arq << "\n\n";
        objCorpusProva_V.carregarArquivo(path_arq);

        int idclasse = objCorpusProva_A.pegarPosAtributo("classe");
        int idresult = objCorpusProva_A.criarAtributo("result");
        objCorpusProva_B.criarAtributo("result");
        objCorpusProva_C.criarAtributo("result");
        objCorpusProva_Five.criarAtributo("result");
        objCorpusProva_Point.criarAtributo("result");
        objCorpusProva_V.criarAtributo("result");

        cout << "\n classe: " << idclasse << " | result: " << idresult << "\n";

        char path[100];

        //Executa classificação passando o corpus com as imagens a serem classificadas
        objClassLibSvm_A->executarClassificacao(objCorpusProva_A,idresult);
        strcpy(path,path_output);
        strcat(path,"corpusGravadoA.txt");
        objCorpusProva_A.gravarArquivo(path);

        objClassLibSvm_B->executarClassificacao(objCorpusProva_B,idresult);
        strcpy(path,path_output);
        strcat(path,"corpusGravadoB.txt");
        objCorpusProva_B.gravarArquivo(path);

        objClassLibSvm_C->executarClassificacao(objCorpusProva_C,idresult);
        strcpy(path,path_output);
        strcat(path,"corpusGravadoC.txt");
        objCorpusProva_C.gravarArquivo(path);

        objClassLibSvm_Five->executarClassificacao(objCorpusProva_Five,idresult);
        strcpy(path,path_output);
        strcat(path,"corpusGravadoFive.txt");
        objCorpusProva_Five.gravarArquivo(path);

        objClassLibSvm_Point->executarClassificacao(objCorpusProva_Point,idresult);
        strcpy(path,path_output);
        strcat(path,"corpusGravadoPoint.txt");
        objCorpusProva_Point.gravarArquivo(path);

        objClassLibSvm_V->executarClassificacao(objCorpusProva_V,idresult);
        strcpy(path,path_output);
        strcat(path,"corpusGravadoV.txt");
        objCorpusProva_V.gravarArquivo(path);

        idAtribClasse = objCorpusProva_A.pegarPosAtributo("classe");

        AvaliadorAcuracia objAvalAcur;

        float acuraciaA = 100.*objAvalAcur.calcularDesempenho(objCorpusProva_A,idclasse,idresult)[0];
        float acuraciaB = 100.*objAvalAcur.calcularDesempenho(objCorpusProva_B,idclasse,idresult)[0];
        float acuraciaC = 100.*objAvalAcur.calcularDesempenho(objCorpusProva_C,idclasse,idresult)[0];
        float acuraciaFive = 100.*objAvalAcur.calcularDesempenho(objCorpusProva_Five,idclasse,idresult)[0];
        float acuraciaPoint = 100.*objAvalAcur.calcularDesempenho(objCorpusProva_Point,idclasse,idresult)[0];
        float acuraciaV = 100.*objAvalAcur.calcularDesempenho(objCorpusProva_V,idclasse,idresult)[0];

        cout << "\n\n********************************************************************************" << endl ;
        cout << " Acuracia A: " << acuraciaA << "%" << endl;
        cout << " Acuracia B: " << acuraciaB << "%" << endl;
        cout << " Acuracia C: " << acuraciaC << "%" << endl;
        cout << " Acuracia Five: " << acuraciaFive << "%" << endl;
        cout << " Acuracia Point: " << acuraciaPoint << "%" << endl;
        cout << " Acuracia V: " << acuraciaV << "%" << endl;
        cout << "********************************************************************************\n\n" << endl ;
    }


    return 0;
}














