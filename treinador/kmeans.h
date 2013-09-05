#ifndef KMEANS_H
#define KMEANS_H


#include "treinador.h"
#include "../classificador/classificador.h"
#include "../classificador/classificadorkmeans.h"
#include "../corpus/corpusmatriz.h"
#include "CImg.h"
#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <sstream>

using namespace cimg_library;

// Classe que desenha as iterações do algoritmo KMeans, representando os registros e centroids através de pontos
// em um plano bidimensional.
class desenhoKMeans
{
  public:
    int escala;
    int tamanhoPontos;
    int iteracoes;
    int limiteX;
    int limiteY;
    vector<vector<float > > cores;
    string nomeImagem;
    desenhoKMeans();
    desenhoKMeans(int limiteX, int limiteY, int escala, int tamanhoPontos, string nomeImagem);
    ~desenhoKMeans();
    void definirConfiguracoes(int limiteX, int limiteY, int escala, int tamanhoPontos, string nomeImagem);
    void desenharRegistro(CImg<unsigned char> &Imagem, float x, float y, vector<float> cor);
    void desenharRegistrosIniciais(vector<vector<float> > registros);
    void desenharCentroidesIniciais(vector<vector<float> > registros,vector<vector<float> > centroides);
    void desenharClusters(vector<vector<float> > registros, vector<vector<float> > centroides, map<int, int> registrosCentroides);
    void inicializarCores();
  };


////////////////////////////////////////////////////////
// Classe do algoritmo KMeans básico, possuindo o algoritmo KMeans++ implementado para geração de centroides iniciais;
class KMeans : public Treinador
{
    public:
        int numeroCentroids;
        int numeroIteracoes;
        bool iteracoes;
        bool gerarImagem;
        string tipoGeradorCentroids;
        desenhoKMeans dKmeans;
        vector<vector<float> > centroids;
        vector<vector<float> > registros;
        vector<vector<int> > registrosCentroids;
        vector<string> atributos;
        vector<int> posAtributos;
        map<int, int> mapaRegistroCentroide;
		KMeans();
		KMeans(int numeroCentroids);
		KMeans(int numeroCentroids, int numeroIteracoes);
		~KMeans();
		void definirNumeroIteracoes(int numeroIteracoes);
		void definirAtributos(vector<string> nomesAtributos);
		void pegarAtributos(Corpus &corpus);
		void definirNumeroCentroids(int numeroCentroids);
		void definirGeradorCentroids(string tipoGeradorCentroids);
		void reiniciarRegistrosCentroids();
		float calcularDistancia(vector<float> ponto1, vector<float> ponto2);
		void gerarCentroids();
		void gerarCentroidsKMeansPP();
		vector<vector<float> > recalcularCentroids();
		bool compararCentroids(vector<vector<float> > novosCentroids);
		void carregarRegistros(Corpus &corpus);
		void definirCluster(vector<float> registro, int posRegistro);
		virtual Classificador* executarTreinamento(Corpus &corpus, int atributo);
		bool compararVetores(vector<float> vetor1, vector<float> vetor2);
		void trocarVetores (vector<float> &vetor1, vector<float> &vetor2);
		void definirConfiguracoesImagem(int limiteX, int limiteY, int escala, int tamanhoPontos, string nomeImagem);
		Classificador* executarKMeans(Corpus &corpus);
		Classificador* executarKMeansImagem(Corpus &corpus);
};


#endif
