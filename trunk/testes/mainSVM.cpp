#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>

#include "../corpus/corpusmatriz.h"
#include "../avaliador/avaliador_acuracia.h"
#include "../validador/validadorkdobras.h"
#include "../treinador/libsvm.h"

using namespace std;

int main()
{
    vector<string> atributos, classes, atributosTreino;
    unsigned int nConjExemplos, e, c0, c1, c2, c, iResposta, iSaida, total, dobras = 8;

    //carrega conjunto de dados
    CorpusMatriz objCorpus(atributos, ',', true);
    objCorpus.carregarArquivo( "../inputs/iris2.txt" );

    //indice do atributo a aprender
    iResposta = objCorpus.pegarPosAtributo("class");

    //quantidade de conjuntos de exemplos
    cout << (nConjExemplos = objCorpus.pegarQtdConjExemplos()) << " exemplos\n";

    //indica classes alvo
    classes.push_back("0");
    classes.push_back("1");
    classes.push_back("2");

    //calcula priori das classes
    c0 = c1 = c2 = total = 0;
    for (c = 0; c < nConjExemplos; c++){
        for (e = 0; e < (unsigned)objCorpus.pegarQtdExemplos(c); e++){
            if (objCorpus.pegarIndice(classes[0]) == objCorpus.pegarValor(c, e, iResposta))
                c0++;
            else
            if (objCorpus.pegarIndice(classes[1]) == objCorpus.pegarValor(c, e, iResposta))
                c1++;
            else
                c2++;
            total++;
        }
    }

    cout << 100.*c0/total << " / " << 100.*c1/total << " / " << 100.*c2/total << endl;
    atributos = objCorpus.pegarAtributos();
/*
    //mostra o corpus
    for (c = 0; c < nConjExemplos; c++){
        cout << c << endl;
        for (e = 0; e < (unsigned)objCorpus.pegarQtdExemplos(c); e++){
            cout << "\t" << e << " ";
            for (unsigned a = 0; a < atributos.size(); a++)
                cout << objCorpus(c,e,a) << " ";
            cout << endl;
        }
        cout << endl;
    }
*/
    //remove atributos que nao devem ser utilizados pelo treinamento
    for (unsigned int i=0; i < atributos.size(); i++)
        if (i!=iResposta)
            atributosTreino.push_back(atributos[i]);

    struct svm_parameter param;
    param.svm_type = C_SVC;
    param.kernel_type = LINEAR; //RBF;
    param.degree = 3;
    param.gamma = 0;
    param.coef0 = 0;
    param.nu = 0.5;
    param.cache_size = 100;
    param.C = 1;
    param.eps = 1e-3;
    param.p = 0.1;
    param.shrinking = 1;
    param.probability = 0;
    param.nr_weight = 0;
    param.weight_label = NULL;
    param.weight = NULL;

    LibSvm objSVM(atributosTreino, classes, param);
    AvaliadorAcuracia objAvalAcur;
    iSaida = objCorpus.criarAtributo("saida", "O");
/*
    Classificador *cl = objSVM.executarTreinamento(objCorpus, iResposta);

    cl->executarClassificacao(objCorpus, iSaida);
    objCorpus.gravarArquivo("#teste.txt");
    cout << objAvalAcur.calcularDesempenho(objCorpus, iResposta, iSaida)[0];
*/
    ValidadorKDobras objValidador(objAvalAcur, dobras);
    vector< vector< float > > v = objValidador.executarExperimento(objSVM, objCorpus, iResposta, iSaida);
    float media = 0;
    for (c=0;c<dobras;c++){
        cout << c << " - " << v[c][0] << endl;
        media += v[c][0];
    }
    cout << "*" << media/dobras << endl;

    return 0;
}
