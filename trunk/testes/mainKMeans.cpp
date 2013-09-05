#include <iostream>
#include "..\..\treinador\kmeans.h"
#include "..\..\classificador\classificadorkmeans.h"
#include "..\..\corpus\corpusmatriz.h"

using namespace std;

int main()
{
    vector<string> atributos;
    Classificador *cl;
    CorpusMatriz objCorpus(atributos, ',', true, false);
    objCorpus.carregarArquivo("europe.data");
    KMeans KMeans(3);
    KMeans.definirGeradorCentroids("KMeansPP");
    KMeans.definirConfiguracoesImagem(600, 600, 5, 2, "europa");
    cl = KMeans.executarTreinamento(objCorpus, 1);
    cl->executarClassificacao(objCorpus, 0);
    objCorpus.gravarArquivo("resultado_kmeans.txt");
    return 0;
}
