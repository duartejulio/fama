#include "corpus.h"
#include <sstream>

Corpus::Corpus( vector<string> atributos )
    : atributos( atributos )
{
    qtd_sentencas = 0;
    qtd_simbolos = 0;

    qtd_atributos = atributos.size();
    for( register int i = 0; i < qtd_atributos; ++i )
        posAtributos[atributos[i]] = i;
}

Corpus::~Corpus()
{

}

string Corpus::pegarSimbolo( int indice )
{
    if ( indice < 0 || indice >= ( int )simbolos.size() )
    {
        ostringstream erro;
        erro << "Erro: pegarSimbolo!\nBusca fora dos limites ( "
         << indice << " / " << (int)simbolos.size() << " )!";
        throw erro.str();
    }
    return simbolos[ indice ];
}

int Corpus::pegarIndice( string simbolo )
{
    int aux;
    map< string, int >:: iterator it; //utilizado p/ n precisar varrer o map 2 vezes

    if( ( it = dicionario.find( simbolo ) ) == dicionario.end() ) //mesmo tratamento da criarAtributo
    {
        aux = dicionario[ simbolo ] = dicionario.size() - 1;
        simbolos.push_back( simbolo );
        ++qtd_simbolos;
        return aux;
    }
    return it->second;
}

int Corpus::criarAtributo( string atributo, string valorAtributo )
{
    /**
    *   Verifica se o atributo j� existe.
    *   Se n�o existe cria-se um novo atributo.
    */
    if( posAtributos.find( atributo ) != posAtributos.end() )
    {
        ostringstream erro;
        erro << "Erro: criarAtributo!\nAtributo ja existe ( "
         << atributo << " / " << pegarPosAtributo(atributo) << " )!";
        throw erro.str();
    }

    atributos.push_back( atributo );
    posAtributos[atributo] = qtd_atributos++;

    /**
    *   verifica se valorAtributo j� existe no dicion�rio.
    *   Se n�o existir cria-se um novo valor no dicion�rio.
    */
    if ( dicionario.find( valorAtributo ) == dicionario.end() )
    {
        dicionario[ valorAtributo ] = dicionario.size() - 1;    // nessa linha primeiro cria-se um elemento(ou seja, aumenta o size),
                                                                // depois realiza-se a atribui��o
        simbolos.push_back( valorAtributo );
        ++qtd_simbolos;
    }

    /**
    *   Cria mais uma posi��o(inicializada com valorAtributo) em cada token de frases
    */
    int column;
    int dicionario_valorAtributo = dicionario[ valorAtributo ];

    for( register int i = 0; i < qtd_sentencas; ++i )
    {
        column = frases[i].size();
        for( register int j = 0; j < column; ++j )
            frases[i][j].push_back( dicionario_valorAtributo );
    }

    //cout << "Atributo <\"" << atributo << "\" -> " << "\"" << valorAtributo << "\"" << "> criado com sucesso!" << endl;
    return pegarPosAtributo( atributo );
}

int Corpus::pegarValor( int sentenca, int token, int atributo )
{
    if ( sentenca < 0 || sentenca >= ( int )qtd_sentencas ||
         token < 0 || token >= ( int )frases[sentenca].size() ||
         atributo < 0 || atributo >= ( int )qtd_atributos )
    {
        ostringstream erro;
        erro << "Erro: pegarValor!\nBusca fora dos limites ( "
         << sentenca << " / " << (int)qtd_sentencas << " ) ( "
         << token << " / " << (int)frases[sentenca].size() << " ) ( "
         << atributo << " / " << (int)qtd_atributos << " )!";
        throw erro.str();
    }

    return frases[sentenca][token][atributo];
}

int Corpus::pegarQtdSentencas()
{
    return qtd_sentencas;
}

int Corpus::pegarQtdAtributos()
{
    return qtd_atributos;
}

int Corpus::pegarQtdTokens( int i )
{
    if( i < 0 || i >= ( int )qtd_sentencas )
    {
        ostringstream erro;
        erro << "Erro: pegarQtdTokens!\nBusca fora dos limites ( "
         << i << " / " << (int)qtd_sentencas << " )!";
        throw erro.str();
    }
    return frases[i].size();
}

int Corpus::pegarQtdSimbolos()
{
    return qtd_simbolos;
}

bool Corpus::ajustarValor( int sentenca, int token, int atributo, int valor )
{
    if ( sentenca < 0 || sentenca >= ( int )qtd_sentencas ||
         token < 0 || token >= ( int )frases[sentenca].size() ||
         atributo < 0 || atributo >= ( int )qtd_atributos )
    {
        ostringstream erro;
        erro << "Erro: ajustarValor!\nInsercao cancelada: posicao inexistente ( "
         << sentenca << " / " << (int)qtd_sentencas << " ) ( "
         << token << " / " << (int)frases[sentenca].size() << " ) ( "
         << atributo << " / " << (int)qtd_atributos << " )!";
        throw erro.str();
    }
    frases[ sentenca ][ token ][ atributo ] = valor;
    return true;
}

string Corpus::pegarAtributo( int indice )
{
    if( indice < 0 || indice >= qtd_atributos )
    {
        ostringstream erro;
        erro << "Erro: pegarAtributo!\nAtributo Inexistente! ( "
         << indice << " / " << qtd_atributos << " )";
        throw erro.str();
    }
    return atributos[indice];
}

int Corpus::pegarPosAtributo( string atributo )
{
    map< string, int >::iterator it;

    if( ( it = posAtributos.find( atributo ) ) == posAtributos.end() )
    {
        ostringstream erro;
        erro << "Erro: pegarAtributo!\nAtributo Inexistente! ( "
         << atributo << " )";
        throw erro.str();
    }
    return it->second;
}

vector< string > Corpus::pegarAtributos()
{
    return atributos;
}

vector< Corpus* > Corpus::splitCorpus( vector< bool > vetMascara )
{
    vector< Corpus* > vetCorpus( 2 );
    if( vetMascara.size() != ( unsigned )qtd_sentencas )
    {
        ostringstream erro;
        erro << "Erro: splitCorpus!\nMascara invalida! ( "
         << (int)vetMascara.size() << " / " << qtd_sentencas << " )";
        throw erro.str();
        return vetCorpus;
    }

    //a responsabilidade de liberar essa mem�ria � passada a quem
    //chamou o m�todo
    vetCorpus[0] = this->clone();
    vetCorpus[0]->frases.clear();
    vetCorpus[1] = this->clone();
    vetCorpus[1]->frases.clear();

    for( register int i = 0; i < qtd_sentencas; ++i )
        if( vetMascara[i] ) vetCorpus[1]->frases.push_back( frases[i] );
        else vetCorpus[0]->frases.push_back( frases[i] );

    vetCorpus[0]->qtd_sentencas = vetCorpus[0]->frases.size();
    vetCorpus[1]->qtd_sentencas = vetCorpus[1]->frases.size();

    return vetCorpus;
}

vector< Corpus* > Corpus::splitCorpus( vector< int > vetMascara, int nCorpus )
{
    register int i, c;

    vector< Corpus* > vetCorpus( nCorpus );
    if( vetMascara.size() != ( unsigned )qtd_sentencas )
    {
        ostringstream erro;
        erro << "Erro: splitCorpus!\nMascara invalida! ( "
         << (int)vetMascara.size() << " / " << qtd_sentencas << " )";
        throw erro.str();
    }

    //a responsabilidade de liberar essa mem�ria � passada a quem
    //chamou o m�todo
    for ( c = 0; c < nCorpus; ++c ){
        vetCorpus[c] = this->clone();
        vetCorpus[c]->frases.clear();
    }

    for( i = 0; i < qtd_sentencas; ++i ){
        c = vetMascara[i];
        if (c < 0 || c > nCorpus){
            ostringstream erro;
            erro << "Erro: splitCorpus!\nValor de Mascara invalida! ( "
             << (int)c << " / " << nCorpus << " )";
            throw erro.str();
        }
        vetCorpus[c]->frases.push_back( frases[i] );
    }

    for ( c = 0; c < nCorpus; ++c )
        vetCorpus[c]->qtd_sentencas = vetCorpus[0]->frases.size();

    return vetCorpus;
}
