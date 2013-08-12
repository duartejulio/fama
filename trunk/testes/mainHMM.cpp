#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>

#include "../corpus/corpusmatriz.h"
#include "../treinador/hmm.h"

#include "../avaliador/avaliador_acuracia.h"
#include "../classificador/classificadorhmm.h"


using namespace std;

int main()
{
    vector<string> atributos;
    int novoAtributo, atributo;

    atributos.push_back("word");
    atributos.push_back("pos");
    atributos.push_back("dontcare");

    CorpusMatriz objCorpus( atributos );
    objCorpus.carregarArquivo( "../inputs/train.txt" );
    atributo = objCorpus.pegarPosAtributo("pos");

    Classificador *objClass;
    HMM objHMM;
    objClass = objHMM.executarTreinamento( objCorpus, atributo );
    //objClass->carregarConhecimento( "inputs/conhecimentoHMM.txt" );

    CorpusMatriz objCorpusProva( atributos );
    objCorpusProva.carregarArquivo( "../inputs/test.txt" );

    atributo = objCorpus.pegarPosAtributo("pos");
    novoAtributo = objCorpusProva.criarAtributo("novopos");

    objClass->executarClassificacao( objCorpusProva, novoAtributo );

    AvaliadorAcuracia objAvalAcur;
    printf( "\nAcuracia: %.2f%%\n", 100 * objAvalAcur.calcularDesempenho( objCorpusProva, atributo, novoAtributo )[ 0 ] );
    objCorpusProva.gravarArquivo( "../outputs/corpusGravado.txt" );
    objClass->gravarConhecimento( "../outputs/conhecimentoHMM.txt" );

    delete objClass;

	return 0;
}

