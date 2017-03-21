#ifndef PROCESSADORJANELA_H
#define PROCESSADORJANELA_H

#include "processador.h"

class ProcessadorJanela
{
        int janela;
        string atributo, itemNulo;
        bool aggregate;
    public:
        ProcessadorJanela(int janela, string atributo,
                          bool aggregate = false, string itemNulo = "O");
        vector<string> processarCorpus(Corpus&);
        ~ProcessadorJanela();
};

#endif // PROCESSADORJANELA_H

