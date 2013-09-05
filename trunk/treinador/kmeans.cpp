#include "kmeans.h"

using namespace std;
using namespace cimg_library;

  desenhoKMeans::desenhoKMeans()
  {
      this->inicializarCores();
  }

// Construtor da Classe desenhoKMeans com as configura��es iniciais: largura da imagem, altura, escala da posi��o original do ponto, tamanho de cada
// ponto que representa um registro, e o nome da imagem a ser gerado (gera um conjunto de imagens, representando cada itera��o)
  desenhoKMeans::desenhoKMeans(int limiteX, int limiteY, int escala, int tamanhoPontos, string nomeImagem)
  {
      this->limiteX = limiteX;
      this->limiteY = limiteY;
      this->escala = escala;
      this->tamanhoPontos = tamanhoPontos;
      this->nomeImagem = nomeImagem;
      this->iteracoes = 0;
      this->inicializarCores();
  }

  desenhoKMeans::~desenhoKMeans()
  {

  }

// M�todo para definir as configura��es das imagens a serem geradas.
  void desenhoKMeans::definirConfiguracoes(int limiteX, int limiteY, int escala, int tamanhoPontos, string nomeImagem)
  {
      this->limiteX = limiteX;
      this->limiteY = limiteY;
      this->escala = escala;
      this->tamanhoPontos = tamanhoPontos;
      this->nomeImagem = nomeImagem;
      this->iteracoes = 0;
  }

// M�todo respons�vel por desenhar os registros. Os pontos x e y representam os valores dos atributos do registro
  void desenhoKMeans::desenharRegistro(CImg<unsigned char> &Imagem, float x, float y, vector<float> cor)
  {
      for(int i = (x * this->escala); i < ((x * this->escala) + this->tamanhoPontos); i++)
      {
          for(int j = (y * this->escala); j < ((y * this->escala) + this->tamanhoPontos); j++)
          {
              for(int c = 0; c < cor.size(); c++)
              {
                Imagem(i, j, c) = cor[c];
              }
          }
      }
  }

// M�todo utilizado para desenhar os registros iniciais, antes de desenhar os centroides iniciais. Os registros iniciais s�o representados
// por pontos pretos, pois n�o est�o associados a nenhum centroide em um primeiro momento.
  void desenhoKMeans::desenharRegistrosIniciais(vector<vector<float> > registros)
  {
      CImg<unsigned char> Imagem(this->limiteX, this->limiteY, 1, 3, 255);
      stringstream ss;
      ss << this->nomeImagem << "_" << this->iteracoes++ << ".bmp";
      vector<float> cor;
      cor.push_back(0);
      cor.push_back(0);
      cor.push_back(0);
      for(int r = 0; r < registros.size(); r++)
      {
          this->desenharRegistro(Imagem, registros[r][0], registros[r][1], cor);
      }
      Imagem.save_bmp(ss.str().c_str());
  }

// M�todo utilizado para desenhar os centroides iniciais, cada um possuindo uma cor diferente (a implementa��o atual suporta at�
// 6 centroides com cores distintas)
  void desenhoKMeans::desenharCentroidesIniciais(vector<vector<float> > registros,vector<vector<float> > centroides)
  {
    CImg<unsigned char> Imagem(this->limiteX, this->limiteY, 1, 3, 255);
    stringstream ss;
    ss << this->nomeImagem << "_" << this->iteracoes++ << ".bmp";
    vector<float> cor;
    cor.push_back(0);
    cor.push_back(0);
    cor.push_back(0);
    for(int r = 0; r < registros.size(); r++)
    {
        this->desenharRegistro(Imagem, registros[r][0], registros[r][1], cor);
    }


    for(int k = 0; k < centroides.size(); k++)
    {
        this->desenharRegistro(Imagem, centroides[k][0], centroides[k][1], this->cores[k]);
    }

    Imagem.save_bmp(ss.str().c_str());

  }

// M�todo utilizado para desenhar cada um dos registros associado ao centroide mais pr�ximo, os representando por pontos com a cor
// do centroide ao qual est�o associados.
  void desenhoKMeans::desenharClusters(vector<vector<float> > registros, vector<vector<float> > centroides, map<int, int> registrosCentroides)
  {
    CImg<unsigned char> Imagem(this->limiteX, this->limiteY, 1, 3, 255);
    stringstream ss;
    ss << this->nomeImagem << "_" << this->iteracoes++ << ".bmp";
    for(int r = 0; r < registros.size(); r++)
    {
        this->desenharRegistro(Imagem, registros[r][0], registros[r][1], this->cores[registrosCentroides[r]]);
    }

    for(int k = 0; k < centroides.size(); k++)
    {
        this->desenharRegistro(Imagem, centroides[k][0], centroides[k][1], this->cores[k]);
    }
    Imagem.save_bmp(ss.str().c_str());
  }

// M�todo que inicializa os vetores de cor, utilizados para desenhar os centroides e registros, posteriormente.
  void desenhoKMeans::inicializarCores()
  {
      vector<float> cor1, cor2, cor3, cor4, cor5, cor6;

      cor1.push_back(255);
      cor1.push_back(0);
      cor1.push_back(0);

      cor2.push_back(0);
      cor2.push_back(255);
      cor2.push_back(0);

      cor3.push_back(0);
      cor3.push_back(0);
      cor3.push_back(255);

      cor4.push_back(255);
      cor4.push_back(255);
      cor4.push_back(0);

      cor5.push_back(255);
      cor5.push_back(0);
      cor5.push_back(255);

      cor6.push_back(0);
      cor6.push_back(255);
      cor6.push_back(255);

      this->cores.push_back(cor1);
      this->cores.push_back(cor2);
      this->cores.push_back(cor3);
      this->cores.push_back(cor4);
      this->cores.push_back(cor5);
      this->cores.push_back(cor6);
  }

KMeans::KMeans()
{

}

KMeans::KMeans(int numeroCentroids)
{
	this->definirNumeroCentroids(numeroCentroids);
	this->iteracoes = false;
	this->numeroIteracoes = -1;
	this->gerarImagem = false;
	this->tipoGeradorCentroids = "padrao";
}

KMeans::KMeans(int numeroCentroids, int numeroIteracoes)
{
	this->definirNumeroCentroids(numeroCentroids);
	this->iteracoes = true;
	this->numeroIteracoes = numeroIteracoes;
	this->gerarImagem = false;
	this->tipoGeradorCentroids = "padrao";
}

KMeans::~KMeans()
{

}

void KMeans::definirNumeroIteracoes(int numeroIteracoes)
{
    this->iteracoes = true;
    this->numeroIteracoes = numeroIteracoes;
}

// Metodo que define quais atributos dos registros ser�o utilizados. Se nenhum atributo for definido, o objeto ir� pegar todos os atributos.
void KMeans::definirAtributos(vector<string> nomesAtributos)
{
    copy(nomesAtributos.begin(), nomesAtributos.end(), atributos.begin());
}

//M�todo que armazena a posi��o dos atributos escolhidos. Se nenhum atributo for definido, pega o nome e posi��o de todos os atributos.
void KMeans::pegarAtributos(Corpus &corpus)
{
    if(this->atributos.size() < 1)
    {
        for(int i = 0; i < corpus.pegarQtdAtributos(); i++)
        {
            this->atributos.push_back(corpus.pegarAtributo(i));
            this->posAtributos.push_back(i);
        }
    }
    else
    {
        for(vector<string>::iterator atr = atributos.begin(); atr != atributos.end(); atr++)
            this->posAtributos.push_back(corpus.pegarPosAtributo(*atr));
    }
}

void KMeans::definirNumeroCentroids(int numeroCentroids)
{
	this->numeroCentroids = numeroCentroids;
	this->registrosCentroids.resize(numeroCentroids);
}

//M�todo que armazena a string que indicar� qual tipo de gerador de centroides ser� utilizado (padr�o ou KMeans++)
void KMeans::definirGeradorCentroids(string tipoGeradorCentroids)
{
    this->tipoGeradorCentroids = tipoGeradorCentroids;
}

//M�todo que limpa e formata o vetor que associa os registros ao centroide mais proximo de cada um
void KMeans::reiniciarRegistrosCentroids()
{
    this->registrosCentroids.clear();
    this->registrosCentroids.resize(this->numeroCentroids);
}

// M�todo que calcula a dist�ncia entre dois pontos. A fun��o de dist�ncia implementada � a euclidiana.
float KMeans::calcularDistancia(vector<float> ponto1, vector<float> ponto2)
{
    float distancia = 0;
    for(int i = 0; i < ponto1.size(); i++)
    {
        distancia += pow((ponto1[i] - ponto2[i]), 2);
    }
    distancia = sqrt(distancia);
    return distancia;
}

//M�todo que gera os centroides aleatoriamente, de acordo com o algoritmo do KMeans padr�o
void KMeans::gerarCentroids()
{
    vector<int> posCentroids;
    vector<float> novoCentroid;
    int random, total = this->registros.size();
    srand(time(NULL));
    for(int i = 0; i < this->numeroCentroids; i++)
    {
        do
        {
            random = rand() % total;
        }while(find(posCentroids.begin(), posCentroids.end(),random) != posCentroids.end());
        novoCentroid.clear();

        for(int count = 0; count < this->registros[random].size(); count++)
        {
            novoCentroid.push_back(this->registros[random][count]);
        }
        this->centroids.push_back(novoCentroid);
        posCentroids.push_back(random);
    }

}

// M�todo do algoritmo KMeans++ implementado para gerar os centroides iniciais com base em uma distribui��o de probabilidade baseada na dist�ncia dos registros aos centroides.
void KMeans::gerarCentroidsKMeansPP()
{
    vector<float> novoCentroid;
    int random, total = this->registros.size();
    float distancia = 0, centroid = 0, menorDistancia, totalDistancia, randomDistancia;
    vector<float> registroDistancia;

    srand(time(NULL));
    registroDistancia.resize(this->registros.size());
    int centroidsAtuais = 0;
    random = rand() % total;
    for(int count = 0; count < this->registros[random].size(); count++)
    {
        novoCentroid.push_back(this->registros[random][count]);
    }

    this->centroids.push_back(novoCentroid);
    novoCentroid.clear();
    centroidsAtuais++;

    for(int count = 1; count < this->numeroCentroids; count++)
    {
        totalDistancia = 0;
        this->registrosCentroids.clear();
        this->registrosCentroids.resize(centroidsAtuais);
        for(int i = 0; i < this->registros.size(); i++)
        {
            menorDistancia = -1;
            for(int c = 0; c < centroidsAtuais; c++)
            {
                distancia = calcularDistancia(this->centroids[c], this->registros[i]);
                if(distancia <= menorDistancia || menorDistancia == -1)
                {
                    menorDistancia = distancia;
                    centroid = c;
                }
            }
            totalDistancia += menorDistancia;
            registroDistancia[i] = menorDistancia;
            this->registrosCentroids[centroid].push_back(i);
            this->mapaRegistroCentroide[i] = centroid;
        }
        randomDistancia = rand() % (int)totalDistancia;
        for(unsigned int i = 0; i < this->registros.size(); i++)
        {
            if(randomDistancia < registroDistancia[i])
            {
                centroid = i;
                break;
            }
            randomDistancia -= registroDistancia[i];
        }
        for(int i = 0; i < this->registros[centroid].size(); i++)
        {
            novoCentroid.push_back(this->registros[centroid][i]);
        }
        this->centroids.push_back(novoCentroid);
        novoCentroid.clear();
        centroidsAtuais++;
    }
}

// M�todo que recalcula os centroides, com base na dist�ncia m�dia de todos os registros associados a cada centroide.
vector<vector<float> > KMeans::recalcularCentroids()
{
	vector<vector<float> > novosCentroids;
	vector<float> novoCentroid;
	int posicao;
	float media;
	for(int c = 0; c < this->registrosCentroids.size(); c++)
	{
	    novoCentroid.clear();
	    for(int atr = 0; atr < this->atributos.size(); atr++)
	    {
	        media = 0;
	        for(int i = 0, total = 0; i < this->registrosCentroids.at(c).size(); i++, total++)
            {
                posicao = this->registrosCentroids.at(c).at(i);
                media += this->registros[posicao][atr];
            }
            media = media / this->registrosCentroids.at(c).size();
            novoCentroid.push_back(media);
	    }

        novosCentroids.push_back(novoCentroid);
	}
	return novosCentroids;
}

//M�todo que compara os centroides atuais com os novos centroides gerados pela fun��o 'recalcularCentroids', e retorna
// verdadeiro ou falso pro caso dos centroides serem iguais ou n�o.
bool KMeans::compararCentroids(vector<vector<float> > novosCentroids)
{
    bool centroidsIguais = true;
    bool vetoresIguais;
    for(int c = 0; c < this->numeroCentroids; c++)
    {
        vetoresIguais = false;
        if(!this->compararVetores(this->centroids[c], novosCentroids[c]))
        {
            this->trocarVetores(this->centroids[c], novosCentroids[c]);
            centroidsIguais = false;
        }
    }
    return centroidsIguais;
}

// M�todo que carrega os registros do arquivo Corpus para a mem�ria.
void KMeans::carregarRegistros(Corpus &corpus)
{
    pegarAtributos(corpus);
    vector<float> tempAtributos;
    for (int c = 0; c < corpus.pegarQtdConjExemplos(); c++)
    {
        tempAtributos.clear();
        for (int e = 0; e < corpus.pegarQtdExemplos(c); e++)
        {
            for(int i = 0; i < posAtributos.size(); i++)
            {
                tempAtributos.push_back(atof(corpus(c, e, posAtributos[i]).c_str()));
            }
            this->registros.push_back(tempAtributos);
        }
    }
}

// M�todo que calcula a dist�ncia de cada registro a cada centroid, definindo qual centroid est� mais pr�ximo em cada caso.
void KMeans::definirCluster(vector<float> registro, int posRegistro)
{
    float distancia = 0, centroid = 0, menorDistancia = -1;
    for(int i = 0; i < this->numeroCentroids; i++)
    {
        distancia = calcularDistancia(this->centroids[i], registro);
        if(distancia <= menorDistancia || menorDistancia == -1)
        {
            menorDistancia = distancia;
            centroid = i;
        }
    }
    this->registrosCentroids[centroid].push_back(posRegistro);
    this->mapaRegistroCentroide[posRegistro] = centroid;
}

// M�todo onde o algoritmo KMeans em si � chamado, e exibe na tela as configura��es dos centroides finais.
Classificador* KMeans::executarTreinamento(Corpus &corpus, int atributo)
{
    Classificador *cl;
    if(this->gerarImagem)
        cl = this->executarKMeansImagem(corpus);
    else
        cl = this->executarKMeans(corpus);

    for(int i = 0; i < this->centroids.size(); i++)
    {
        cout << "Centroide: " << i+1 << endl;
        for(int c = 0; c < this->centroids.at(i).size(); c++)
        {
            cout << centroids.at(i).at(c) << " ";
        }
        cout << endl;
    }
    return cl;
}

// M�todo para compara��o de dois vetores de pontos flutuantes
bool KMeans::compararVetores(vector<float> vetor1, vector<float> vetor2)
{
    for(int i = 0; i < vetor1.size(); i++)
    {
        if(vetor1[i] != vetor2[i])
            return false;
    }
    return true;
}

// M�todo para trocar os elementos de dois vetores de pontos flutuantes
void KMeans::trocarVetores(vector<float> &vetor1, vector<float> &vetor2)
{
    float aux;
    for(int i = 0; i < vetor1.size(); i++)
    {
        aux = vetor1[i];
        vetor1[i] = vetor2[i];
        vetor2[i] = aux;
    }
}

// M�todo utilizado para definir as configura��es iniciais da classe que desenha as itera��es do KMeans. Quando chamado,
// esse m�todo altera o boolean 'gerarImagem' para true, fazendo com que as imagens sejam geradas ao executar o algoritmo.
void KMeans::definirConfiguracoesImagem(int limiteX, int limiteY, int escala, int tamanhoPontos, string nomeImagem)
{
    this->gerarImagem = true;
    this->dKmeans.definirConfiguracoes(limiteX, limiteY, escala, tamanhoPontos, nomeImagem);
}

// M�todo que executa o algoritmo KMeans, de acordo com os par�metros estabelecidos
Classificador* KMeans::executarKMeans(Corpus &corpus)
{
    Classificador *cl = NULL;
	bool terminou = false, centroidsIguais = false;

	carregarRegistros(corpus);

	//Verifica o tipo de gerador seleiconado; Se foi o KMeans++ ou o padr�o
	if(this->tipoGeradorCentroids == "KMeansPP")
        this->gerarCentroidsKMeansPP();
    else
        this->gerarCentroids();

	while(!terminou)
	{
        this->reiniciarRegistrosCentroids();
        for(int i = 0; i < this->registros.size(); i++)
        {
            this->definirCluster(registros.at(i), i);
        }

        if(this->iteracoes == true)
        {
            this->numeroIteracoes--;
        }

        if(this->numeroIteracoes != -1 && this->numeroIteracoes < 1)
        {
            terminou = true;
        }
        else
        {
            centroidsIguais = this->compararCentroids(this->recalcularCentroids());
            if(centroidsIguais)
                terminou = true;
        }
	}
	cl = new ClassificadorKMeans(this->centroids, this->posAtributos);
	return cl;
}

// M�todo que executa o algoritmo KMeans, gerando as imagens das itera��es nos pontos espec�ficos.
Classificador* KMeans::executarKMeansImagem(Corpus &corpus)
{
    Classificador *cl = NULL;
	bool terminou = false, centroidsIguais = false;

	carregarRegistros(corpus);
	dKmeans.desenharRegistrosIniciais(this->registros);

	if(this->tipoGeradorCentroids == "KMeansPP")
        this->gerarCentroidsKMeansPP();
    else
        this->gerarCentroids();

	dKmeans.desenharCentroidesIniciais(this->registros, this->centroids);
	while(!terminou)
	{
        this->reiniciarRegistrosCentroids();
        for(int i = 0; i < this->registros.size(); i++)
        {
            this->definirCluster(registros.at(i), i);
        }

        dKmeans.desenharClusters(this->registros, this->centroids, this->mapaRegistroCentroide);

        if(this->iteracoes == true)
        {
            this->numeroIteracoes--;
        }

        if(this->numeroIteracoes != -1 && this->numeroIteracoes < 1)
        {
            terminou = true;
        }
        else
        {
            centroidsIguais = this->compararCentroids(this->recalcularCentroids());
            dKmeans.desenharClusters(this->registros, this->centroids, this->mapaRegistroCentroide);
            if(centroidsIguais)
                terminou = true;
        }

	}
	cl = new ClassificadorKMeans(this->centroids, this->posAtributos);
	return cl;
}
