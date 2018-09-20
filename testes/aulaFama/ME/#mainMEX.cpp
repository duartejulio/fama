#include <iostream>
#include <fstream>

#include "../../../treinador/treinador.h"
#include "../../../treinador/adaboost.h"
#include "../../../stump/stump.h"
#include "../../../classificador/classificador.h"
#include "../../../corpus/corpusmatriz.h"
#include "../../../avaliador/avaliador_acuracia.h"
#include "../../../validador/validadorkdobras.h"

using namespace std;


int main()
{
    vector<string> atributos, classes;
    int atributo, novoatributo, c;
    AvaliadorAcuracia objAvalAcur;

    float acuraciaMedia;

    srand(time(NULL));

    //carrega conjunto de dados
    CorpusMatriz objCorpus(atributos, ',', true, true);
    objCorpus.carregarArquivo( "../../../inputs/adult.data" );
    atributo = objCorpus.pegarPosAtributo("resposta");

    classes.push_back("<=50K");
    classes.push_back(">50K");

    atributos = objCorpus.pegarAtributos();
    atributos.pop_back();

    //treina
    DecisionStump stump(atributos, classes);
    TreinadorAdaboost adab(stump, classes, 30, 0.01, false);

    novoatributo = objCorpus.criarAtributo("me");

    //faz experimento
    int ndobras = 10;
    ValidadorKDobras objValidador(objAvalAcur, ndobras, false);
    vector< vector< float > > v;
    v = objValidador.executarExperimento(adab, objCorpus, atributo, novoatributo);

    acuraciaMedia = 0;
    for (c=0;c<ndobras;c++){
        cout << c << " - " << 100.*v[c][0] << "%\n";
        acuraciaMedia += v[c][0];
    }
    acuraciaMedia /= ndobras;
    cout << "*" << acuraciaMedia << "\n";

    return 0;
}
