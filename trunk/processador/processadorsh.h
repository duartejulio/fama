#ifndef PROCESSADORSH_H
#define PROCESSADORSH_H

#include "processador.h"

class ProcessadorSerieHistorica
{
        int janela;
        string atributo;
    public:
        ProcessadorSerieHistorica(int janela, string atributo);
        ~ProcessadorSerieHistorica();
        bool processarCorpus(Corpus&);

};

#endif // PROCESSADORSH_H

