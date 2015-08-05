#include "treinador/treinador_distribuicao.h"

#ifndef TREINADORCONTAINERDISTRIBUICAO_H
#define TREINADORCONTAINERDISTRIBUICAO_H


class TreinadorContainerDistribuicao : public TreinadorDistribuicao
{
private:
    TreinadorContainerDistribuicao();
    Treinador *base;

public:
    TreinadorContainerDistribuicao(Treinador *base) : TreinadorDistribuicao(), base(base) {}
    TreinadorContainerDistribuicao(Treinador *base, vector<double> dist) : TreinadorDistribuicao(dist), base(base) {}

    
    
    ~TreinadorContainerDistribuicao();
};

#endif // TREINADORCONTAINERDISTRIBUICAO_H
