#include <iostream>
#include <map>
#include <vector>
#include <cstdio>
#include <cstdlib>

#include "../corpus/corpusmatriz.h"
#include "../avaliador/avaliador_acuracia_respostas_adicionais.h"
#include "../validador/validadorkdobras.h"
#include "../treinador/naivebayes.h"

using namespace std;

    //Funcao para tratar a duplicidade de classes
bool existeNoArray(vector<string> matriz, string palavra){
    unsigned int contador = matriz.size();

    bool existe = false;
    for (unsigned int j = 0; j < contador; j++) {
        if (matriz[j] == palavra) {
            existe = true;
            break;
        }
    }

    return existe;
}

int main()
{
    vector<string> atributos, classes, atributosTreino;
    map<string,int> count;
    string recuperaClasse;
    vector<unsigned int> tagsAdicionais;
    unsigned int nConjExemplos, e, c, iResposta, iSaida, dobras = 5, qntTagsAdicionais = 4;

    //carrega conjunto de dados
    CorpusMatriz objCorpus(atributos, ',', false);
    objCorpus.carregarArquivo( "../inputs/recom/corpus_10_palavras_3.data" );

    //indice do atributo a aprender
    iResposta = objCorpus.pegarPosAtributo("tag01");
    //cout <<iResposta<<"\n";

    //quantidade de conjuntos de exemplos
    cout << (nConjExemplos = objCorpus.pegarQtdConjExemplos()) << " exemplos\n";

    //indica classes alvo
    for (c = 0; c < nConjExemplos; c++)
        for (e = 0; e < (unsigned)objCorpus.pegarQtdExemplos(c); e++)
            for (unsigned a = 0; a < 1; a++){
                recuperaClasse = objCorpus(c,e,a);
                count[recuperaClasse]++;
                if (existeNoArray(classes,recuperaClasse) == false){
                    classes.push_back(recuperaClasse);
                    //cout << objCorpus(c,e,a) << "\n" ;
                }
            }
    cout << "\ntotal de tags " << classes.size() << "\n\n";
//    for (c=0;c<classes.size();c++)
//        cout << classes[c] << " - " << count[classes[c]] << endl;

//    cout << "1";
    atributos = objCorpus.pegarAtributos();

     //Alimenta vetor com as classes adicionais a serem avaliadas pelo avaliador de acuracia
    for (unsigned  i = 1; i <= qntTagsAdicionais; i++){
        tagsAdicionais.push_back(i);
    }
    // atributos que devem ser utilizados pelo treinamento
    for (unsigned i = qntTagsAdicionais + 1; i < atributos.size(); i++){
        atributosTreino.push_back(atributos[i]);
    }

    NaiveBayes objNB(atributosTreino, classes);
    AvaliadorAcuraciaRespostasAdicionais objAvalAcur(tagsAdicionais);
    iSaida = objCorpus.criarAtributo("saida", "O");

    //
    Classificador *cl = objNB.executarTreinamento(objCorpus, iResposta);
    cl->executarClassificacao(objCorpus, iSaida);
    cout << cl->descricaoConhecimento();
    objCorpus.gravarArquivo("#teste.txt");

    //
/*
    ValidadorKDobras objValidador(objAvalAcur, dobras);
    vector< vector< float > > v = objValidador.executarExperimento(objNB, objCorpus, iResposta, iSaida);
    float media = 0;
    for (c=0;c<dobras;c++){
        cout <<"dobra "<< c << " = " << v[c][0] << endl;
        media += v[c][0];
    }
    cout << "-------------\nAcuracia Final = " << media/dobras << endl;
*/
    //Apenas para parar a execucao e nao fechar automaticamente o console caso seja necessario
    cin.get();
    return 0;
}


