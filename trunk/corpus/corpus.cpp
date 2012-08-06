#include "corpus.h"

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
        cout << "Erro: pegarSimbolo!\nBusca fora dos limites!" << endl;
        return NULL;
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

bool Corpus::criarAtributo( string atributo, string valorAtributo )
{
    /**
    *   Verifica se o atributo já existe.
    *   Se não existe cria-se um novo atributo.
    */
    if( posAtributos.find( atributo ) != posAtributos.end() )
    {
        cout << "Erro:criarAtributo!\nAtributo ja existe!" << endl;
        return false;
    }

    atributos.push_back( atributo );
    posAtributos[atributo] = qtd_atributos++;

    /**
    *   verifica se valorAtributo já existe no dicionário.
    *   Se não existir cria-se um novo valor no dicionário.
    */
    if ( dicionario.find( valorAtributo ) == dicionario.end() )
    {
        dicionario[ valorAtributo ] = dicionario.size() - 1;    // nessa linha primeiro cria-se um elemento(ou seja, aumenta o size),
                                                                // depois realiza-se a atribuição
        simbolos.push_back( valorAtributo );
        ++qtd_simbolos;
    }

    /**
    *   Cria mais uma posição(inicializada com valorAtributo) em cada token de frases
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
    return true;
}

int Corpus::pegarValor( int sentenca, int token, int atributo )
{
    if ( sentenca < 0 || sentenca >= ( int )qtd_sentencas ||
         token < 0 || token >= ( int )frases[sentenca].size() ||
         atributo < 0 || atributo >= ( int )qtd_atributos )
    {
        cout << "Erro: pegarValor!\nBusca fora dos limites!" << endl;
        return -1;
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
        cout << "Erro: pegarQtdTokens!\nBusca fora dos limites!" << endl;
        return -1;
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
        cout << "Erro: ajustarValor!\nInsercao cancelada: posicao inexistente!" << endl;
        return false;
    }
    frases[ sentenca ][ token ][ atributo ] = valor;
    return true;
}

string Corpus::pegarAtributo( int indice )
{
    if( indice < 0 || indice >= qtd_atributos )
    {
        cout << "Erro: pegarAtributo!\nBusca fora dos limites!" << endl;
        return NULL;
    }
    return atributos[indice];
}

int Corpus::pegarPosAtributo( string atributo )
{
    map< string, int >::iterator it;

    if( ( it = posAtributos.find( atributo ) ) == posAtributos.end() )
    {
        cout << "Erro: pegarPosAtributo!\nAtributo inexistente!" << endl;
        return -1;
    }
    return it->second;
}

vector< string > Corpus::pegarAtributos()
{
    return atributos;
}

vector< Corpus* > Corpus::splitCorpus( float percTotal )
{
    vector< Corpus* > vetCorpus( 2 );
    vector< bool > vetIndices( qtd_sentencas, false );
    float contador;
    int aux;

    srand( time( NULL ) );
    for( contador = .0; contador/qtd_sentencas < percTotal; ++contador )
        if( !vetIndices[aux = rand()%qtd_sentencas] )
            vetIndices[aux] = true;
        else
        {
            while( !vetIndices[++aux%=qtd_sentencas] );
            vetIndices[aux] = true;
        }
    //não esquecer de dar delete nestas variáveis
    vetCorpus[0] = this->clone();
    vetCorpus[0]->frases.clear();
    vetCorpus[1] = this->clone();
    vetCorpus[1]->frases.clear();

    for( register int i = 0; i < qtd_sentencas; i++ )
        if( vetIndices[i] )
            vetCorpus[1]->frases.push_back( frases[i] );
        else
            vetCorpus[0]->frases.push_back( frases[i] );

    vetCorpus[0]->qtd_sentencas = vetCorpus[0]->frases.size();
    vetCorpus[1]->qtd_sentencas = vetCorpus[1]->frases.size();

    return vetCorpus;
}

vector< Corpus* > Corpus::splitCorpus( int dobras )
{
    vector< Corpus* > vetCorpus( dobras );
    int aux, i;
    for( i = 0; i < dobras; ++i )
    {
        vetCorpus[i] = this->clone();
        vetCorpus[i]->frases.clear();
    }

    for( i = 0; i < dobras; ++i )
    {
        aux = (i + 1)*qtd_sentencas/dobras;
        for( register int j = i*qtd_sentencas/dobras; j < aux; ++j )
            vetCorpus[i]->frases.push_back( frases[j] );
    }

    for( i = 0; i < dobras; ++i )
        vetCorpus[i]->qtd_sentencas = vetCorpus[i]->frases.size();

    return vetCorpus;
}

void Corpus::operator += ( Corpus &lde )
{
    for( register int i = 0; i < lde.qtd_sentencas; ++i )
        frases.push_back( lde.frases[i] );
    qtd_sentencas += lde.qtd_sentencas;
}

void Corpus::limpaFrases()
{
    frases.clear();
    qtd_sentencas = 0;
}
