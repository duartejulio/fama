#include "avaliador_acuracia_respostas_adicionais.h"

AvaliadorAcuraciaRespostasAdicionais::AvaliadorAcuraciaRespostasAdicionais(vector<unsigned int> atr)
{
    //ctor
	atributos = atr;

}

AvaliadorAcuraciaRespostasAdicionais::~AvaliadorAcuraciaRespostasAdicionais()
{
    //dtor

}

vector<float> AvaliadorAcuraciaRespostasAdicionais::calcularDesempenho( Corpus &corpus, int atributo_padrao, int atributo_teste )
{
    /**
    *
    *   Calcula a porcentagem de acerto para um determinado atributo
    *
    */


    vector<float> vectorAcuracia;
    int row = corpus.pegarQtdSentencas(), column, acertos = 0, totalTokens = 0;

    for ( register int i = 0; i < row; ++i )
    {
        column = corpus.pegarQtdTokens( i );

        for ( register int j = 0; j < column; ++j )
        {
			cout << "Compara Tag Principal - "<< corpus.pegarValor(i,j,atributo_padrao) << " = " << corpus.pegarValor(i,j,atributo_teste)<< "\n";

            if ( corpus.pegarValor(i,j,atributo_padrao) == corpus.pegarValor(i,j,atributo_teste) ){
                ++acertos;
			}else{
				//cout <<"Numero de atributos adicionais - "<< atributos.size()<<"\n";
				for (unsigned c=0;c<atributos.size();c++){
					//cout << atributos[c];
					cout << "Compara Tag Adicional - "<< corpus.pegarValor(i,j,atributo_teste) << " = " << corpus.pegarValor(i,j,atributos[c]) << "\n";
					if ( corpus.pegarValor(i,j,atributo_teste) == corpus.pegarValor(i,j,atributos[c]) ){
						++acertos;
						break;
					}

			}
			}

			cout << "\n\n";



            ++totalTokens;
        }
    }


    vectorAcuracia.push_back( (float)acertos / totalTokens );

    return vectorAcuracia;
}

vector<float> AvaliadorAcuraciaRespostasAdicionais::calcularDesempenho2( Corpus &corpus, int atributo_padrao, int atributo_teste, int atributo_considerar )
{
    /**
    *
    *   Calcula a porcentagem de acerto para um determinado atributo
    *
    */
    vector<float> vectorAcuracia;
    int row = corpus.pegarQtdSentencas(), column, acertos = 0, totalTokens = 0;
    bool considerar = false;

    for ( register int i = 0; i < row; ++i )
    {
        column = corpus.pegarQtdTokens( i );

        for ( register int j = 0; j < column; ++j )
        {
            if ( corpus.pegarValor(i,j,atributo_padrao) == corpus.pegarValor(i,j,atributo_teste) )
                ++acertos;

            if (corpus.pegarValor(i,j,atributo_considerar) == corpus.pegarIndice("1")) {
                considerar=true;
            }
            else
            {
                considerar=false;
            }

            ++totalTokens;

        }
    }

    if (!considerar){
        vectorAcuracia.push_back( -1 );
    }else{
        vectorAcuracia.push_back( (float)acertos / totalTokens );
    }


    return vectorAcuracia;
}
