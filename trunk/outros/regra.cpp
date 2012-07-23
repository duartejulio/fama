#include "regra.h"

Regra::Regra( multimap< int, vector< int > > estrutura, int resp )
{
    this->estrutura = estrutura;
    this->resp = resp;
    good = bad = 0;
}
