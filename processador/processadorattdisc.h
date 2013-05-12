#ifndef PROCESSADORATTDISC_H
#define PROCESSADORATTDISC_H

#include "processador.h"

class ProcessadorAttDisc
{
        int numatributos;
        bool attcriados;
        vector<string> atributo;



    public:
        ProcessadorAttDisc(vector<string> atr);
        bool processarCorpus(Corpus&);
        ~ProcessadorAttDisc();
        void criarAtributos(Corpus&);

};

#endif // PROCESSADORATTDISC_H

