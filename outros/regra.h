#ifndef REGRA_H
#define REGRA_H

#include <map>
#include <vector>

using namespace std;

struct Regra
{
    multimap< int, vector< int > > estrutura;
    int resp, good, bad;//se for feita mais de uma classificação simultanea resp tem que ser atualizado para map e respMolde tem que ser criado
    Regra( multimap< int, vector< int > > estrutura, int resp );
};

#endif // REGRA_H
