#include "avaliador_entidade.h"

AvaliadorEntidade::AvaliadorEntidade(string entidadeConsiderar):
        entidadeConsiderar(entidadeConsiderar)
{
    //ctor
}

AvaliadorEntidade::~AvaliadorEntidade()
{
    //dtor
}

vector<float> AvaliadorEntidade::calcularDesempenho( Corpus &corpus, int atributo_padrao, int atributo_teste )
{
    int qtdConjExemplos = corpus.pegarQtdConjExemplos(), qtdExemplos;
    string tipoAtual, lastTipo;
    int janelaI, i, j, vez, acertos;
    vector<Entidade> entidadesPadrao, entidadesTeste;

    for (vez=0;vez<2;vez++){
        lastTipo = "O";
        for (i = 0; i < qtdConjExemplos; ++i ){
            qtdExemplos = corpus.pegarQtdExemplos(i);

            j = 0;
            while(j <= qtdExemplos){
                if (j==qtdExemplos)
                    tipoAtual = "O";
                else
                    tipoAtual = corpus(i,j,vez?atributo_teste:atributo_padrao);

                if (tipoAtual=="O"){
                    if (lastTipo!="O"){
                        vez?entidadesTeste.push_back(Entidade(lastTipo, i, janelaI, j)):
                        entidadesPadrao.push_back(Entidade(lastTipo, i, janelaI, j));
                        lastTipo = "O";
                    }
                }
                else{
                    tipoAtual = tipoAtual.substr(2,tipoAtual.length()-2);
                    if (lastTipo == "O"){
                        janelaI = j;
                    }
                }
                lastTipo = tipoAtual;
                j++;
            }
        }
    }
    int tamTeste = entidadesTeste.size(), tamPadrao = entidadesPadrao.size(),
     ePadrao, eTeste;

    acertos = 0;
    for (ePadrao = 0; ePadrao < tamPadrao; ePadrao++)
        for (eTeste = 0; eTeste < tamTeste; eTeste++){
            if (entidadeConsiderar=="O" || entidadesTeste[eTeste].tipo==entidadeConsiderar
                 || entidadesPadrao[ePadrao].tipo==entidadeConsiderar){
                if (entidadesTeste[eTeste]==entidadesPadrao[ePadrao]){
                    acertos++;
                    break;
                }
            }
        }

    vector<float> vectorResult;
    vectorResult.push_back(acertos/(float)tamPadrao);
    vectorResult.push_back(acertos);
    vectorResult.push_back(tamPadrao);
    vectorResult.push_back(tamTeste);

/*    cout << entidadesPadrao.size();
    for (int c=0;c<entidadesPadrao.size();c++){
        cout << entidadesPadrao[c].tipo << " " << entidadesPadrao[c].conjunto << " "
        << entidadesPadrao[c].janelaI << " " << entidadesPadrao[c].janelaF << endl ;
    }
*/


    //vectorAcuracia.push_back( (float)acertos / totalTokens );

    return vectorResult;
}

