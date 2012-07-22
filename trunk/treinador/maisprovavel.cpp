#include "maisprovavel.h"

MaisProvavel::MaisProvavel( int toleranciaUnknow )
{
    this->toleranciaUnknow = toleranciaUnknow;
}

MaisProvavel::~MaisProvavel()
{
    //dtor
}

Classificador *MaisProvavel::executarTreinamento( Corpus &corpus, int atributo )
{
    ///Faz classificação com base na probabilidade associada a determinada palavra
    ///(int) atributo eh o numero associado a palavra que ele vai aprender a classificar

    /**
    *
    *  AQUI PREENCHEMOS tabelaFreq.
    *  O parametro (int)atributo representa a posição no token do atributo
    *  que será classificado. Ex: Se quisermos classificar segundo "pos" fazemos (atributo = 1).
    *
    */
    ClassificadorMaisProvavel *objClassificador = new ClassificadorMaisProvavel();
    map< int, map< int, int > > tabelaFreq;
    int row = corpus.pegarQtdSentencas(), column;

    ///Fazer tratamento com try e catch
    if ( atributo <= 0 || atributo >= ( int )corpus.pegarQtdAtributos() )
    {
        cout << "Erro:executarTreinamento!\nAtributo inexistente!" << endl;
    	return objClassificador;
    }

    for ( register int i = 0; i < row; i++ )
    {
        column = corpus.pegarQtdTokens( i );

    	for ( register int j = 0; j < column; j++ )
            ++tabelaFreq[ corpus.pegarValor(i,j,0) ][ corpus.pegarValor(i,j,atributo) ];
    }

    cout << "Tabela de Frequencias gerada" << endl;

    /**
    *  Determina a classificação de maior frequência para cada palavra
    */
    map< int, map< int, int > >::iterator linha, linha_end;
    map< int, int >::iterator coluna, coluna_end;

    int maxOfRow, maxAtributo, NumUnknow;
    bool flag;
    //controlePalavras.resize( corpus.pegarQtdSimbolos() ); // ASSOCIA palavra COM maxAtributo
    //map< int, int > controlePalavras; // ASSOCIA palavra COM maxAtributo (utilizado caso o vetor seja esparso)
    map< int, int > listaUnknow;

    linha_end = tabelaFreq.end();
    for ( linha = tabelaFreq.begin(); linha != linha_end; linha++ )
    {
        maxOfRow = -1;
        coluna_end = linha->second.end();
        for ( coluna = linha->second.begin(); coluna != coluna_end; coluna++ )
            if( coluna->second > maxOfRow )
            {
                maxOfRow = coluna->second;
                maxAtributo = coluna->first;
            }

        if( maxOfRow > toleranciaUnknow )
            objClassificador->ajustarcontrolePalavras( corpus.pegarSimbolo( linha->first ), corpus.pegarSimbolo( maxAtributo ) );
        else
        {
            listaUnknow[ maxAtributo ]++;
            //controlePalavras[ linha->first ] = -1; //usado p/ indicar que esta palavra virou desconhecida
        }
    }

    maxOfRow = -1;
    //procura maior classificação de desconhecido
    coluna_end = listaUnknow.end();
    for( coluna = listaUnknow.begin(); coluna != coluna_end; coluna++ )
        if( coluna->second > maxOfRow )
        {
            flag = true;  //indica que entrou aqui pelo menos uma vez
            maxOfRow = coluna->second;
            NumUnknow = coluna->first;
        }

    //tratamento para o caso do corpus não conter nenhuma palavra que seja unknown
    if( flag )
        objClassificador->ajustarUnknown( corpus.pegarSimbolo( NumUnknow ) );
    else
        objClassificador->ajustarUnknown( "NPROP" );

    cout << "Vetor de Frequencias gerado" << endl;
    return objClassificador;

    /**
    *  Cria um novo atributo "teste" e usa o map controlePalavras
    *  para alterá-lo com o valor correto
    */


//    /// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//    /**
//    *  Cria um novo atributo "teste";
//    *  Determina a classificação de maior frequência para cada palavra,
//    *  criando o vector controleAtributos
//    */
//    int tam_simbolos = corpus.pegarQtdSimbolos();
//    int maxOfRow, maxAtributo;
//    vector<int> controleAtributos( tam_simbolos ); // ASSOCIA cada atributo(inclusive palavra) COM maxAtributo
//
//    corpus.criarAtributo( "teste", "TESTE" );
//
//    cout << "Atributo teste gerado" << endl;
//    system("pause");
//
//    int tam_atributos = corpus.pegarQtdAtributos();
//    int frases_ij0;
//
//
//
//    for ( register int i = 0; i < row; i++ )
//    {
//        column = corpus.pegarQtdTokens( i );
//
//        for ( register int j = 0; j < column; j++ )
//        {
//            if ( controleAtributos[ frases_ij0 = corpus.pegarValor( i, j, 0 ) ] == 0 )
//            {
//                maxOfRow = -1;
//
//                for ( register int k = 0; k < tam_simbolos; k++ )
//                	maxOfRow = ( tabelaFreq[ frases_ij0 ][ k ] > maxOfRow ? tabelaFreq[ frases_ij0 ][ k ], maxAtributo = k : maxOfRow );
//
//                controleAtributos[ frases_ij0 ] = maxAtributo;
//            }
//
//            corpus.ajustarValor( i, j, tam_atributos - 1, controleAtributos[ frases_ij0 ] );
//        }
//    }
}
