#ifndef CLASSIFICADOR_KMEANS_H
#define CLASSIFICADOR_KMEANS_H

#include "../treinador/kmeans.h"
#include "classificador.h"
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
using namespace std;

// Classe que representa o "Classificador" do KMeans: armazena no arquivo escolhido em qual cluster cada registro se localiza
class ClassificadorKMeans : public Classificador
{
    public:
        vector<vector<float> > centroids;
        vector<vector<float> > registros;
        vector<int> atributos;
        ClassificadorKMeans();
        ClassificadorKMeans(vector<vector<float> > centroids, vector<int> atributos);
        ~ClassificadorKMeans();
        virtual bool executarClassificacao( Corpus &corpusProva, int atributo );
        virtual bool gravarConhecimento( string arquivo );
        virtual bool carregarConhecimento( string arquivo );
        float calcularDistancia(vector<float> ponto1, vector<float> ponto2);
};

#endif
