#include "validadorteste.h"

ValidadorTeste::ValidadorTeste( Corpus &corpusTreino )
{
    this->corpusTreino = &corpusTreino;
}

ValidadorTeste::~ValidadorTeste()
{
    //dtor
}

vector< vector< float > > ValidadorTeste::executarExperimento( Treinador &treinador, Corpus &corpus )
{
    vector< vector< float > > resultado;
    treinador.executarTreinamento( *corpusTreino, ATRBT_ANALISADO )->executarClassificacao( corpus, ATRBT_CLASSIFICADO );
    resultado.push_back( avaliador->calcularDesempenho( corpus, ATRBT_ANALISADO, corpus.pegarQtdAtributos() - 1 ) );
    return resultado;
}
