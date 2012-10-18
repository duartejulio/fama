#ifndef PROCESSADOR_H
#define PROCESSADOR_H

#include "../corpus/corpus.h"


class Processador
{
    public:
        Processador();
        virtual ~Processador();
        virtual bool processarCorpus(Corpus &) = 0;
};

#endif // PROCESSADOR_H

