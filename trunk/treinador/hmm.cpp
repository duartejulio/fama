#include "hmm.h"

HMM::HMM( string atributoBase ) : Treinador( atributoBase )
{

}

HMM::~HMM()
{
    //dtor
}

Classificador *HMM::executarTreinamento( Corpus &corpus, int atributo )
{
    int atributo_base;
    if( ( atributo_base = corpus.pegarPosAtributo( atributoBase ) ) == -1 )
    {
        cout << "Erro: executarTreinamento!\nAtributo inexistente!" << endl;
        return NULL;
    }

    ClassificadorHMM *objClassificador = new ClassificadorHMM( atributoBase );
    map< string, map< string, double > > matrizTransicao;
    int row = corpus.pegarQtdSentencas(), column, i, j;
    double total = 0.0;

    if ( atributo <= 0 || atributo >= ( int )corpus.pegarQtdAtributos() )
    {
        cout << "Erro:executarTreinamento!\nAtributo inexistente!" << endl;
    	return objClassificador;
    }

    for ( i = 0; i < row; ++i )
    {
        column = corpus.pegarQtdTokens( i );

        objClassificador->ajustarTabFreqObservacoes( corpus.pegarSimbolo(corpus.pegarValor(i,0,atributo)), corpus.pegarSimbolo(corpus.pegarValor(i,0,atributo_base)) );
        objClassificador->ajustarVetInicial( corpus.pegarSimbolo(corpus.pegarValor(i,0,atributo)) );
        if( column != 1 )
        {
            for ( j = 1; j < (column - 1); ++j )
            {
                objClassificador->ajustarTabFreqObservacoes( corpus.pegarSimbolo(corpus.pegarValor(i,j,atributo)), corpus.pegarSimbolo(corpus.pegarValor(i,j,atributo_base)) );
                ++matrizTransicao[corpus.pegarSimbolo(corpus.pegarValor(i,j,atributo))][corpus.pegarSimbolo(corpus.pegarValor(i,j+1,atributo))];
            }
            objClassificador->ajustarTabFreqObservacoes( corpus.pegarSimbolo(corpus.pegarValor(i,j,atributo)), corpus.pegarSimbolo(corpus.pegarValor(i,j,atributo_base)) );
        }
    }

    ///Verificar depois até onde o double mantem a precisão
    map< string, map< string, double > >::iterator linha, linha_end;
    map< string, double >:: iterator coluna, coluna_end;
    //faz conversão para matriz de probabilidades
    linha_end = matrizTransicao.end();
    for( linha = matrizTransicao.begin();  linha != linha_end; ++linha )
    {
        coluna_end = linha->second.end();
        for( coluna = linha->second.begin(); coluna != coluna_end; ++coluna )
            total += coluna->second;
        for( coluna = linha->second.begin(); coluna != coluna_end; ++coluna )
            matrizTransicao[linha->first][coluna->first] = ( coluna->second )/total; //pode haver um erro carregado aqui
        total = 0.0;
    }

    objClassificador->definirMatrizTransicao( matrizTransicao );

    //A principio não precisa de Unknown, sera utilizado a melhor sequencia de estados
    cout << "A, B e Pi criados" << endl;
    return objClassificador;
}
