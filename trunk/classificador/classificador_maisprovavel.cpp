#include "classificador_maisprovavel.h"

bool ClassificadorMaisProvavel::executarClassificacao( Corpus &corpusProva, int atributo )
{
    corpusProva.criarAtributo( "pos", "N" );
    int tam_atributos = corpusProva.pegarQtdAtributos() - 1, row = corpusProva.pegarQtdSentencas(), column;
    map< string, string >::iterator it, it_end;
    int valorUnknow = corpusProva.pegarIndice( unknown ); //otimização p/ corpus com mtos unknown

    ///complexidade m²log(n), m tamanho do corpus, n tamanho do conhecimento
    ///melhor p/ textos pequenos
//    for ( register int i = 0; i < row; i++ )
//    {
//        column = corpusProva.pegarQtdTokens( i );
//        for ( register int j = 0; j < column; j++ )
//            if( ( it = controlePalavras.find( corpusProva.pegarSimbolo( corpusProva.pegarValor( i, j, 0 ) ) ) ) != controlePalavras.end() )
//                corpusProva.ajustarValor( i, j, tam_atributos - 1, corpusProva.pegarIndice( it->second ) );
//            else
//                corpusProva.ajustarValor( i, j, tam_atributos - 1, valorUnknow );
//    }

    ///Complexidade nlog(n) + m², com gasto de memória bem maior
    ///melhor p/ textos grandes ( teste pratico este foi melhor )
    vector< int > vetorControlePal( corpusProva.pegarQtdSimbolos(), valorUnknow );
    int aux;

    it_end = controlePalavras.end();
    for( it = controlePalavras.begin(); it != it_end; ++it )
    {
        aux = corpusProva.pegarIndice( it->first ); //utiliza aux pq o tamanho do dicionario pode mudar
        vetorControlePal.resize( corpusProva.pegarQtdSimbolos(), valorUnknow );
        vetorControlePal[ aux ] = corpusProva.pegarIndice( it->second );
    }

    for ( register int i = 0; i < row; ++i )
    {
        column = corpusProva.pegarQtdTokens( i );
        for ( register int j = 0; j < column; ++j )
            corpusProva.ajustarValor( i, j, tam_atributos, vetorControlePal[ corpusProva.pegarValor( i, j, atributo ) ] );
    }

    cout << "Classificacao MaisProvavel: executada" <<endl;
    return true;
}

void ClassificadorMaisProvavel::ajustarcontrolePalavras( string indice, string valor )
{
    controlePalavras[ indice ] = valor;
}

void ClassificadorMaisProvavel::ajustarUnknown( string val )
{
    unknown = val;
}

bool ClassificadorMaisProvavel::gravarConhecimento( string arquivo )
{
    ofstream arqout( arquivo.c_str() );
    if( !arqout.is_open() ) //verifica se arquivo conseguiu ser aberto
    {
        cout << "Erro:gravarConhecimento!\nFalha na abertura do arquivo!" << endl;
        return false;
    }
    map< string, string >::iterator it, it_end;

    arqout << unknown << endl;
    it_end = controlePalavras.end();
    for( it = controlePalavras.begin(); it != it_end; ++it )
    {
        arqout << it->first << endl;
        arqout << it->second << endl;
    }

    arqout.close();
    cout << "Arquivo <" << arquivo << "> gravado com sucesso!" << endl;
    return true;
}

bool ClassificadorMaisProvavel::carregarConhecimento( string arquivo )
{
    ///Falta robustecer esse código

    ifstream arqin( arquivo.c_str() );
    if( !arqin.is_open() ) //verifica se arquivo conseguiu ser aberto
    {
        cout << "Erro:carregarConhecimento!\nFalha na abertura do arquivo!" << endl;
        return false;
    }
    string aux;

    arqin >> unknown;
    while( arqin >> aux && arqin.good() )
        arqin >> controlePalavras[ aux ];

    if( arqin.bad() && !arqin.eof() )    //caso de erro na leitura do arquivo
    {
        cout << "Erro:carregarConhecimento!\nErro na leitura do arquivo!" << endl;
        arqin.close();
        return false;
    }

    arqin.close();
    cout << "Arquivo <" << arquivo << "> carregado com sucesso!" << endl;
    return true;
}
