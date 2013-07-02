#include <iostream>

#include "../../../treinador/treinador.h"
#include "../../../classificador/classificador.h"
#include "../../../corpus/corpusmatriz.h"
#include "../../../avaliador/avaliador_acuracia.h"
#include "../../../validador/validadorkdobras.h"

using namespace std;

class ClassificadorMaisEsperto:public Classificador{
private:
    string resposta;
public:
    ClassificadorMaisEsperto(string resp):Classificador(){
        resposta = resp;
    }
    bool executarClassificacao(Corpus &corpus, int atributo){
        int c, e;

        for (c = 0; c < corpus.pegarQtdConjExemplos(); c++)
            for (e = 0; e < corpus.pegarQtdExemplos(c); e++)
                corpus(c,e,atributo,resposta);
        return true;
    }
    bool gravarConhecimento( string arquivo ){return false;}
    bool carregarConhecimento( string arquivo ){return false;};
};

class TreinadorMaisEspero:public Treinador{
private:
    string positivo, negativo;
public:
    TreinadorMaisEspero(string pos, string neg){
        positivo = pos;
        negativo = neg;
    }

    Classificador *executarTreinamento( Corpus &corpus, int atributo ){
        int c, e;
        int contador[2] = {0,0};
        string val;

        for (c = 0; c < corpus.pegarQtdConjExemplos(); c++){
            for (e = 0; e < corpus.pegarQtdExemplos(c); e++){
                val = corpus(c,e,atributo);
                if (val==positivo)
                    contador[1]++;
                else
                if (val==negativo)
                    contador[0]++;
                else
                    cout << "Classe Estranha\n";
            }
        }
        Classificador *cl;
        if (contador[0] > contador[1]){
            cl = new ClassificadorMaisEsperto(negativo);
            cout << "Resp:" << negativo << "\n";
        }
        else{
            cl = new ClassificadorMaisEsperto(positivo);
            cout << "Resp:" << positivo << "\n";
        }

        return cl;
    }

};

int main()
{
    vector<string> atributos;
    int atributo, novoatributo, c;
    Classificador *cl;

    float media;

    //carrega conjunto de dados
    CorpusMatriz objCorpus(atributos, ',', true, true);
    objCorpus.carregarArquivo( "../../../inputs/adult.data" );

    atributo = objCorpus.pegarPosAtributo("resposta");

    //treina
    TreinadorMaisEspero tme("<=50K",">50K");
    cl = tme.executarTreinamento(objCorpus, atributo);

    //classifica
    novoatributo = objCorpus.criarAtributo("me");
    cl->executarClassificacao(objCorpus, novoatributo);

    //avalia
    AvaliadorAcuracia objAvalAcur;
    cout << 100 * objAvalAcur.calcularDesempenho( objCorpus, atributo, novoatributo)[0] << "\n";

    //faz experimento
    ValidadorKDobras objValidador(objAvalAcur, 10);
    vector< vector< float > > v = objValidador.executarExperimento(tme, objCorpus, atributo, novoatributo);

    media = 0;
    for (c=0;c<10;c++){
        cout << c << " - " << v[c][0] << "\n";
        media += v[c][0];
    }
    cout << "*" << media/10 << "\n";

    return 0;
}
