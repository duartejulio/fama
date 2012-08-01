#include "avaliador_acuracia.h"

AvaliadorAcuracia::AvaliadorAcuracia()
{
    //ctor
}

AvaliadorAcuracia::~AvaliadorAcuracia()
{
    //dtor
}

vector<float> AvaliadorAcuracia::calcularDesempenho( Corpus &corpus, int atributo_padrao, int atributo_teste )
{
    /**
    *
    *   Calcula a porcentagem de acerto para um determinado atributo
    *
    */
    vector<float> vectorAcuracia;
    int row = corpus.pegarQtdSentencas(), column, acertos = 0, totalTokens = 0;

    for ( register int i = 0; i < row; ++i )
    {
        column = corpus.pegarQtdTokens( i );

        for ( register int j = 0; j < column; ++j )
        {
            if ( corpus.pegarValor(i,j,atributo_padrao) == corpus.pegarValor(i,j,atributo_teste) )
                ++acertos;

            ++totalTokens;
        }
    }


    vectorAcuracia.push_back( (float)acertos / totalTokens );

    return vectorAcuracia;
}
