#ifndef PRE_PROCESSAR_H
#define PRE_PROCESSAR_H

#include <iostream>
#include "corpus.h"
#include "corpusmatriz.h"



using namespace std;

class pre_processar
{
    public:
      bool gerarCorpusProcessado(CorpusMatriz &objCorpus, int janela);


};

#endif // PRE_PROCESSAR_H

