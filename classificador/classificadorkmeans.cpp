#include "classificadorkmeans.h"
ClassificadorKMeans::ClassificadorKMeans()
{

}

ClassificadorKMeans::~ClassificadorKMeans()
{

}


// Método construtor que recebe como parâmetro os centroides gerados pelo KMeans e quais atributos utilizados
ClassificadorKMeans::ClassificadorKMeans(vector<vector<float> > centroids, vector<int> atributos)
{
    vector<float> centroid;

    for(int i = 0; i < centroids.size(); i++)
    {
        centroid.clear();
        for(int a = 0; a < centroids[i].size(); a++)
        {
            centroid.push_back(centroids[i][a]);
        }
        this->centroids.push_back(centroid);
    }

    for(int i = 0; i < atributos.size(); i++)
    {
        this->atributos.push_back(atributos[i]);
    }

}

// Método que executa a classificação dos registros, atribuindo ao atributo 'cluster', o cluster no qual o registro se localiza
bool ClassificadorKMeans::executarClassificacao(Corpus &corpusProva, int atributo)
{
    int cluster, centroid;
    float menorDistancia, distancia;
    vector<float> registro;
    ostringstream ss;
    cluster = corpusProva.criarAtributo("cluster");
    for(int c = 0; c < corpusProva.pegarQtdConjExemplos(); c++)
    {
        for(int e = 0; e < corpusProva.pegarQtdExemplos(c); e++)
        {
            registro.clear();
            for(int a = 0; a < this->atributos.size(); a++)
            {
                registro.push_back(atof(corpusProva(c,e,this->atributos[a]).c_str()));
            }
            menorDistancia = -1;
            for(int k = 0; k < this->centroids.size(); k++)
            {
                distancia = this->calcularDistancia(registro, this->centroids[k]);
                if(distancia <= menorDistancia || menorDistancia == -1)
                {
                    menorDistancia = distancia;
                    centroid = k;
                }
            }
            centroid++;
            ss.str("");
            ss.clear();
            ss << centroid;
            corpusProva(c, e, cluster, ss.str());
        }
    }
    return true;
}
// Método que armazena os valores de cada centroide gerado pelo KMeans
bool ClassificadorKMeans::gravarConhecimento(string arquivo)
{
    ofstream out;
    out.open(arquivo.c_str());
    for(int c = 0; c < this->centroids.size(); c++)
    {
        for(int a = 0; a < this->atributos.size(); a++)
        {
            if(a > 0)
                out << " ";
            out << this->centroids[c][a];
        }
        out << "\n";
    }

    out.close();
    return true;
}

bool ClassificadorKMeans::carregarConhecimento(string arquivo)
{
    ifstream in;
    in.open(arquivo.c_str());
    for(int c = 0; c < this->centroids.size(); c++)
    {
        for(int a = 0; a < this->atributos.size(); a++)
        {
            in >> this->centroids[c][a];
        }
    }
    in.close();
    return true;
}

// Método que, assim como definido também na classe KMeans, retorna a distância euclidiana entre dois pontos (definidos por dois vetores de pontos flutuantes)
float ClassificadorKMeans::calcularDistancia(vector<float> ponto1, vector<float> ponto2)
{
    float distancia = 0;
    for(int i = 0; i < ponto1.size(); i++)
    {
        distancia += pow((ponto1[i] - ponto2[i]), 2);
    }
    distancia = sqrt(distancia);
    return distancia;
}
