#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>

#include "../processador/processadorsh.h"
#include "../corpus/corpusmatriz.h"
#include "../avaliador/avaliador_acuracia.h"

using namespace std;

int main()
{
    //carrega conjunto de dados
    CorpusMatriz objCorpus(vector<string>(), ',', false, true);
    ProcessadorSerieHistorica psh(3, "valor");

    objCorpus.carregarArquivo( "../inputs/ativos" );
    if (psh.processarCorpus(objCorpus))
        cout << "Sucesso\n";
    objCorpus.gravarArquivo( "../inputs/#teste.txt" );

    return 0;
}
