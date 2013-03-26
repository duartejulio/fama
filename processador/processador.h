#ifndef PROCESSADOR_H
#define PROCESSADOR_H

#include "../corpus/corpus.h"


class Processador
{
    public:
        Processador();
        virtual ~Processador();
        virtual vector<string> processarCorpus(Corpus &) = 0;
};

#endif // PROCESSADOR_H

