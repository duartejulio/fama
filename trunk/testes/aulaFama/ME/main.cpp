#include <iostream>
#include <fstream>

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
    bool executarClassificacao(Corpus &corpus, int atributo){
        int c, e;

        for (c = 0; c < corpus.pegarQtdConjExemplos(); c++)
            for (e = 0; e < corpus.pegarQtdExemplos(c); e++)
                corpus(c,e,atributo,resposta);

        return true;
    }
    bool gravarConhecimento( string arquivo ){
        ofstream out;
        out.open(arquivo.c_str());
        out << resposta;
        out.close();
        return true;
    }
    bool carregarConhecimento( string arquivo ){
        ifstream in;
        in.open(arquivo.c_str());
        in >> resposta;
        in.close();
        return true;
    };
    friend class TreinadorMaisEspero;
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

        ClassificadorMaisEsperto *cl = new ClassificadorMaisEsperto;
        if (contador[0] > contador[1])
            cl->resposta = negativo;
        else
            cl->resposta = positivo;

        cout << "Resp:" << cl->resposta << "\n";

        return cl;
    }

};

int main()
{
    vector<string> atributos;
    int atributo, novoatributo, c;
    Classificador *cl,*cl2;

    float media;

    //carrega conjunto de dados
    CorpusMatriz objCorpus(atributos, ',', true, true);
    objCorpus.carregarArquivo( "../../../inputs/adult.data" );
    atributo = objCorpus.pegarPosAtributo("resposta");

    //treina
    TreinadorMaisEspero tme("<=50K", ">50K");
    cl = tme.executarTreinamento(objCorpus, atributo);
    cl->gravarConhecimento("xpto");

    cl2 = new ClassificadorMaisEsperto;
    cl2->carregarConhecimento("xpto");

    //classifica
    novoatributo = objCorpus.criarAtributo("me");
    cl2->executarClassificacao(objCorpus, novoatributo);

    //avalia
    AvaliadorAcuracia objAvalAcur;
    cout << 100 * objAvalAcur.calcularDesempenho(objCorpus, atributo, novoatributo)[0] << "\n";

    //faz experimento
    int ndobras = 20;
    ValidadorKDobras objValidador(objAvalAcur, ndobras);
    vector< vector< float > > v = objValidador.executarExperimento(tme, objCorpus, atributo, novoatributo);

    media = 0;
    for (c=0;c<ndobras;c++){
        cout << c << " - " << v[c][0] << "\n";
        media += v[c][0];
    }
    cout << "*" << media/ndobras << "\n";

    return 0;
}
