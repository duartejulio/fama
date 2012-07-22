#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>

#include "corpusmatriz.h"
#include "maisprovavel.h"
#include "avaliador_acuracia.h"
#include "classificador_maisprovavel.h"
#include "classificadorhmm.h"
#include "classificadortbl.h"

#define LIM_FREQ_UNKNOWN 3
#define ATRBT_ANALISADO 1
#define ATRBT_CLASSIFICADO 0
#define ATRBT_NOVO 3

using namespace std;
//MaisProvavel
int main()
{
    vector<string> atributos;
    atributos.push_back("word");
    atributos.push_back("tpos");
    atributos.push_back("np");

    CorpusMatriz objCorpus( atributos );
    objCorpus.carregarArquivo( "inputs/train.txt" );

    Classificador *objClass;
    MaisProvavel objMProv( LIM_FREQ_UNKNOWN );
    objClass = objMProv.executarTreinamento( objCorpus, ATRBT_ANALISADO );
    //objClass->carregarConhecimento( "inputs/conhecimentoMProv.txt" );

    CorpusMatriz objCorpusProva( atributos );
    objCorpusProva.carregarArquivo( "inputs/test.txt" );

    objClass->executarClassificacao( objCorpusProva, ATRBT_CLASSIFICADO );
    AvaliadorAcuracia objAvalAcur;

    printf( "Acuracia: %.2f%%\n", 100 * objAvalAcur.calcularDesempenho( objCorpusProva, ATRBT_ANALISADO, ATRBT_NOVO )[ 0 ] );
    objCorpusProva.gravarArquivo( "outputs/corpusGravado.txt" );
    objClass->gravarConhecimento( "outputs/conhecimentoMProv.txt" );
    delete objClass;

	return 0;
}

