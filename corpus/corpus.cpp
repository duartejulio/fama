#include "corpus.h"
#include <stdlib.h> //retrocompatibilidade
#include <time.h>

bool eh_numero(string val){
    int i, tam;
    tam = val.size();
    for (i=0;i<tam;i++)
        if (val[i]!='.' && (val[i]<'0' || val[i] > '9'))
            return false;
    return true;
}

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

Corpus* Corpus::construirJanela( void *popUp )
{
    ostringstream erro;
    erro << "Construtor de janela nao definido\n";
    throw erro.str();
    return this;
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
    *   Verifica se o atributo já existe. Em caso afirmativo, retorna a posição do atributo.
    *   Se não existe cria-se um novo atributo.
    */
    map< string, int >:: iterator it;

    if( ( it = posAtributos.find( atributo ) ) != posAtributos.end() )
    {
        /*ostringstream erro;
        erro << "Erro: criarAtributo!\nAtributo ja existe ( "
         << atributo << " / " << pegarPosAtributo(atributo) << " )!";
        throw erro.str();*/
        return it->second;
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
    return pegarPosAtributo( atributo );
}

bool Corpus::removerAtributo( string atributo )
{
    map< string, int >::iterator it;
    if( ( it = posAtributos.find( atributo ) ) == posAtributos.end() ) return false;

    int column;
    for( register int i = 0; i < qtd_sentencas; ++i )
    {
        column = frases[i].size();
        for( register int j = 0; j < column; ++j )
            frases[i][j].erase( frases[i][j].begin() + it->second );
    }

    atributos.erase( atributos.begin() + it->second );
    posAtributos.erase( it );
    --qtd_atributos;

    for( register int i = 0; i < qtd_atributos; i++ )
        posAtributos[atributos[i]] = i;

    return true;
}

bool Corpus::removerAtributo( int indice )
{
    if( indice >= qtd_atributos || indice < 0 ) return false;

    int column;
    for( register int i = 0; i < qtd_sentencas; ++i )
    {
        column = frases[i].size();
        for( register int j = 0; j < column; ++j )
            frases[i][j].erase( frases[i][j].begin() + indice );
    }

    posAtributos.erase( posAtributos.find( atributos[indice] ) );
    atributos.erase( atributos.begin() + indice );
    --qtd_atributos;

    for( register int i = 0; i < qtd_atributos; i++ )
        posAtributos[atributos[i]] = i;

    return true;
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

void Corpus::operator()(int sentenca, int token, int atributo, string valor){
    ajustarValor(sentenca, token, atributo, pegarIndice(valor));
}

string Corpus::operator()(int sentenca, int token, int atributo){
    return pegarSimbolo(pegarValor(sentenca,token,atributo));
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

    //a responsabilidade de liberar essa memória é passada a quem
    //chamou o método
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

    //a responsabilidade de liberar essa memória é passada a quem
    //chamou o método
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
        vetCorpus[c]->qtd_sentencas = vetCorpus[c]->frases.size();

    return vetCorpus;
}

int Corpus::pegarQtdTotalExemplos(){
    register int c, nExemplosTotal = 0, nConjExemplos = pegarQtdConjExemplos();

    for (c=0; c < nConjExemplos; c++)
        nExemplosTotal += pegarQtdExemplos(c);

    return nExemplosTotal;
}

Corpus* Corpus::gerarSubCorpus( vector< vector< bool > > vetMascara )
{
    Corpus *subCorpus;
    vector< vector<int> > frase;
    register int j, qtd_tokens;

    if( vetMascara.size() != ( unsigned )qtd_sentencas )
    {
        ostringstream erro;
        erro << "Erro: gerarSubCorpus!\nMascara invalida! ( "
         << (int)vetMascara.size() << " / " << qtd_sentencas << " )";
        throw erro.str();
        return NULL;
    }

    //a responsabilidade de liberar essa memória é passada a quem
    //chamou o método
    subCorpus = this->clone();
    subCorpus->frases.clear();

    for( register int i = 0; i < qtd_sentencas; ++i ){
        qtd_tokens = pegarQtdExemplos(i);
        if( vetMascara[i].size() != ( unsigned )qtd_tokens )
        {
            ostringstream erro;
            erro << "Erro: gerarSubCorpus!\nMascara invalida! ( " << i << " - "
             << (int)vetMascara[i].size() << " / " << qtd_tokens << " )";
            throw erro.str();
            return NULL;
        }

        for( j = 0; j < qtd_tokens; ++j )
            if( vetMascara[i][j] )
                break;

        if (j < qtd_tokens){
            vector< vector<int> > frase;
            for(; j < qtd_tokens; ++j )
                if( vetMascara[i][j] )
                    frase.push_back(frases[i][j]);
            subCorpus->frases.push_back( frase);
        }
    }

    subCorpus->qtd_sentencas = subCorpus->frases.size();

    return subCorpus;
}

bool Corpus::discreto(int atributo, vector<string> &possiveisValores){
    float f;
    string val;
    bool continuo;
    int e, c, qtdExemplos;
    map<string, int> valores;
    map<string, int>::iterator iter;

    possiveisValores.clear();

    continuo = true;

    for (c=0; c<qtd_sentencas; c++){
        qtdExemplos = frases[c].size();
        for (e=0; e<qtdExemplos; e++){
            val = pegarSimbolo(pegarValor(c, e, atributo));
            if (!eh_numero(val))
                continuo = false;
            valores[val] = 1;
        }
    }

    if (continuo)
        return false;

    for(iter = valores.begin(); iter != valores.end(); ++iter)
        possiveisValores.push_back(iter->first);

    return true;
}

bool Corpus::discreto(string atributo, vector<string> &possiveisValores){
    return discreto(pegarPosAtributo(atributo), possiveisValores);
}

Corpus* Corpus::reamostrar (vector<double>* distribuicao, bool porFrase) {
    Corpus* alvo = this->clone();
    if (distribuicao == NULL)
        return alvo;
    alvo->frases.clear();

    if (!porFrase) {
        vector<double>* novo = new vector<double>(this->qtd_sentencas);
        double soma; int k = 0;
        for (int i = 0; i < this->qtd_sentencas; i++) {
            soma = 0.0;
            for(int j = 0; j < this->pegarQtdTokens(i); j++)
                soma += distribuicao->at(k++);
            novo->at(i) = soma;
        }
        distribuicao = novo;
    }

    srand(time(NULL));

    //Calcular qual exemplo vai cair
    double random;
    int total = this->pegarQtdTotalExemplos();
    for (int i = 0; i < this->qtd_sentencas; i++) {
        //Por limitaçoes do rand, calcular quantas vezes for possivel para que a soma possa chegar no ultimo elemento
        random = 0.0;
        for (int j = 0; j < total/RAND_MAX; j++)
            random += (double)rand();
        //Normalizando random
        random /= total;
        //Aqui calcula qual exemplo pegar
        //Vai diminuindo o random do peso do exemplo iterado, e, se o valor do random for menor ou igual a zero, significa
        //que ele o exemplo da iteraçao atual deve entrar
        int exemplo = 0;
        for (;random>0;random -= distribuicao->at(exemplo++));
        alvo->frases.push_back(this->frases.at(exemplo));
    }

    if (!porFrase)
        delete distribuicao;

    return alvo;
}
