#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <iostream>
#include <sstream>
#include <sys/unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "../C50/c50.h"
#include "../corpus/corpusmatrizc50.h"
#include "../classificador/classificadorc50.h"
#include "../treinador/treinadorC50.h"

#define SetFOpt(V)	V = strtod(OptArg, &EndPtr);\
			if ( ! EndPtr || *EndPtr != '\00' ) break;\
			ArgOK = true
#define SetIOpt(V)	V = strtol(OptArg, &EndPtr, 10);\
			if ( ! EndPtr || *EndPtr != '\00' ) break;\
			ArgOK = true


int main()
{
    C50 objC50;
    
    CorpusC50 objCorpus(vector<string>(), ',', true, true);    
    objCorpus.carregarArquivo(objC50, "MalwareDinamicos" );
    //objC50.imprimir();
     TreinadorC50 objTreinador(objCorpus.pegarAtributos(),objCorpus.pegarClasses(),objCorpus.pegarAttValores(),objC50, 0.9);
   
    Classificador *objClass = objTreinador.executarTreinamento(objCorpus,0);
    cout<<"construiu o classificador"<<endl;
    //int x = objCorpus.criarAtributo("Classificacao");
  
    cout<<"criou o atributo"<<endl;
    objClass->executarClassificacao(objCorpus,28);
    cout<<"terminou a classificacao"<<endl;
    objCorpus.gravarArquivo("C:\\Users\\Leticia Cremasco\\Documents\\IP\\fama\\inputs\\corpusGravado3.txt");
    return 0;
}
