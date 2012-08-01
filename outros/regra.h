#ifndef REGRA_H
#define REGRA_H

using namespace std;

struct Regra
{
    //multimap< int, vector< int > > estrutura;
    int resp, good, bad;//se for feita mais de uma classificação simultanea resp tem que ser atualizado para map e respMolde tem que ser criado
    //Regra( multimap< int, vector< int > > estrutura, int resp );
    Regra( int resp, int good );
};

#endif // REGRA_H
