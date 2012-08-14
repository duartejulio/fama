#include "avaliador_diferenca.h"

#include <cmath>
#include <sstream>
#include <iostream>
using std::istringstream;

AvaliadorDiferenca::AvaliadorDiferenca()
{
    //ctor
}

AvaliadorDiferenca::~AvaliadorDiferenca()
{
    //dtor
}

vector<float> AvaliadorDiferenca::calcularDesempenho( Corpus &corpus, int atributo_padrao, int atributo_teste )
{
    /**
    *
    *   Calcula a raiz quadrada da soma dos quadrados das diferenças
    *
    */
    vector<float> vectorAcuracia;
    int row = corpus.pegarQtdSentencas(), column, totalItens = 0, v;
    float val1, val2, acertos = 0.0;

    for ( register int i = 0; i < row; ++i )
    {
        column = corpus.pegarQtdTokens( i );

        for ( register int j = 0; j < column; ++j )
        {
            v = corpus.pegarValor(i, j, atributo_padrao);
            (std::istringstream)(corpus.pegarSimbolo(v)) >> val1 >> std::dec;
            v = corpus.pegarValor(i, j, atributo_teste);
            (std::istringstream)(corpus.pegarSimbolo(v)) >> val2 >> std::dec;
            acertos += (val1 - val2)*(val1 - val2);

            ++totalItens;
        }
    }


    vectorAcuracia.push_back(sqrt(acertos) / totalItens );

    return vectorAcuracia;
}
