#include <iostream>
#include <fstream>

#include "../../../treinador/knn.h"
#include "../../../corpus/corpusmatriz.h"
#include "../../../treinador/treinador.h"
#include "../../../classificador/classificador.h"
#include "../../../avaliador/avaliador_acuracia.h"
#include "../../../validador/validadorkdobras.h"

using namespace std;

int main()
{
    vector<string> atributos, classes;
    int atributo, novoatributo, c;
    Classificador *cl;//,*cl2;
    AvaliadorAcuracia objAvalAcur;

    float media;

    srand(time(NULL));

    //carrega conjunto de dados
    CorpusMatriz objCorpus(atributos, ',', true, true);
    objCorpus.carregarArquivo( "../../../inputs/adult.data.medium");
    atributo = objCorpus.pegarPosAtributo("resposta");

    classes.push_back("<=50K");
    classes.push_back(">50K");

    //atributos = objCorpus.pegarAtributos();
    //atributos.pop_back();
    atributos.push_back("age");
    atributos.push_back("fnlwgt");
    atributos.push_back("education-num");
    atributos.push_back("capital-gain");
    atributos.push_back("capital-loss");
    atributos.push_back("hours-per-week");

    //treina
    TreinadorKNN knn(atributos,classes,true,5);

    novoatributo = objCorpus.criarAtributo("me");

    cl = knn.executarTreinamento(objCorpus, atributo);
    cout << cl->descricaoConhecimento() << endl;
//    cl->gravarConhecimento("xpto");

//    cl2 = new ClassificadorMaisEsperto;
//    cl->carregarConhecimento("xpto");

    //classifica

//    cl2->executarClassificacao(objCorpus, novoatributo);
    cl->executarClassificacao(objCorpus, novoatributo);

    objCorpus.gravarArquivo("#testeout.txt");

    //avalia
    cout << 100 * objAvalAcur.calcularDesempenho(objCorpus, atributo, novoatributo)[0] << "%\n";

    //faz experimento
    int ndobras = 10;
    ValidadorKDobras objValidador(objAvalAcur, ndobras, false);
    vector< vector< float > > v;
    try{
        v = objValidador.executarExperimento(knn, objCorpus, atributo, novoatributo);
    }
    catch(string s){
        cout << "*" << s << endl;
        return 1;
    }
    catch(...){
        cout << "Erro desconhecido" << endl;
        return 2;
    }
    media = 0;
    for (c=0;c<ndobras;c++){
        cout << c << " - " << 100.*v[c][0] << "%\n";
        media += v[c][0];
    }
    cout << "*" << media/ndobras << "\n";

    return 0;
}
