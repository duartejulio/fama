#include "classificadortbl.h"

ClassificadorTBL::ClassificadorTBL( Classificador* classInicial, string atributoChute, vector< multimap< int, vector< string > > > regras, vector< string > respRegras )
{
    this->classInicial = classInicial;
    this->atributoChute = atributoChute;
    this->regras = regras;
    this->respRegras = respRegras;
}

ClassificadorTBL::ClassificadorTBL( Classificador* classInicial, string arquivo )
{
    this->classInicial = classInicial;
    carregarConhecimento( arquivo );
}

ClassificadorTBL::ClassificadorTBL( Classificador* classInicial )
{
    this->classInicial = classInicial;
}

ClassificadorTBL::~ClassificadorTBL()
{
    //dtor
}

bool ClassificadorTBL::executarClassificacao( Corpus &corpusProva, int atributo )
{
    int atributo_chute = corpusProva.criarAtributo( atributoChute );

    /*if( ( atributo_chute = corpusProva.pegarPosAtributo( atributoChute ) ) == -1 )
    {
        cout << "Erro: executarClassificacao!\nAtributo inexistente!" << endl;
        return NULL;
    }*/


    //Classificação inicial
    if( !classInicial->executarClassificacao( corpusProva, atributo_chute ) )
    {
        cout << "Erro: executarClassificacao!\nClassificacao BLS nao executada!" << endl;
        return NULL;
    }

    int row = corpusProva.pegarQtdSentencas(), column, numRegras = regras.size(), resp;
    int i, j, L;
    bool regraInvalida;
    multimap< int, vector< string > >::iterator linha, linha_end;
    multimap< int, vector< int > >::iterator linhaInt, linhaInt_end, linhaInt_inicio;
    multimap< int, vector< int > >::reverse_iterator linhaInt_ultimo;

    //conversão de string para int
    vector< multimap< int, vector< int > > > regrasInt;
    multimap< int, vector< int > > var;
    vector< int > vet( 2 );
    vector< int > respRegrasInt;

    for( L = 0; L < numRegras; ++L )
    {
        linha_end = regras[L].end();
        for( linha = regras[L].begin(); linha != linha_end; ++linha )
        {
            vet[0] = corpusProva.pegarPosAtributo( linha->second[0] );
            vet[1] = corpusProva.pegarIndice( linha->second[1] );
            var.insert( pair< int, vector< int > >( linha->first, vet ) );
        }
        regrasInt.push_back( var );
        respRegrasInt.push_back( corpusProva.pegarIndice( respRegras[L] ) );
        var.clear();
    }

    for( L = 0; L < numRegras; ++L )
    {
        linhaInt_end = regrasInt[L].end();
        linhaInt_inicio = regrasInt[L].begin();
        linhaInt_ultimo = regrasInt[L].rbegin();
        resp = respRegrasInt[L];
        for( i = 0; i < row; ++i )
        {
            column = corpusProva.pegarQtdTokens( i );
            for( j = 0; j < column; ++j )
            {
                if( j + linhaInt_inicio->first < 0 || j + linhaInt_ultimo->first >= column ) continue;
                regraInvalida = false;

                for( linhaInt = linhaInt_inicio; linhaInt != linhaInt_end; ++linhaInt )
                    if( corpusProva.pegarValor(i,j+linhaInt->first,linhaInt->second[0]) != linhaInt->second[1] )
                    {
                        regraInvalida = true;
                        break;
                    }
                if( !regraInvalida )
                    corpusProva.ajustarValor(i,j,atributo_chute,resp);
            }
        }
    }

    //copia resposta do atributo_chute no atributo e apaga o atributo_chute
    if( atributo_chute != atributo )
    {
        for( i = 0; i < row; ++i )
        {
            column = corpusProva.pegarQtdTokens( i );
            for( j = 0; j < column; ++j )
                corpusProva.ajustarValor( i, j, atributo, corpusProva.pegarValor( i, j, atributo_chute ) );
        }
        corpusProva.removerAtributo( atributo_chute );
    }

    cout << "Classificacao TBL: executada" <<endl;
    return true;
}

bool ClassificadorTBL::gravarConhecimento( string arquivo )
{
    ofstream arqout( arquivo.c_str() );
    if( !arqout.is_open() ) //verifica se arquivo conseguiu ser aberto
    {
        cout << "Erro:gravarConhecimento!\nFalha na abertura do arquivo!" << endl;
        return false;
    }
    arqout << atributoChute;

    int numRegras = regras.size();
    multimap< int, vector< string > >::iterator linha, linha_end;

    for( register int i = 0; i < numRegras; ++i )
    {
        linha_end = regras[i].end();
        for( linha = regras[i].begin(); linha != linha_end; ++linha )
            arqout << linha->second[0] << ' ' << linha->first << ' ' << linha->second[1] << ' ';
        arqout << "=> " << respRegras[i] << endl;
    }

    arqout.close();
    cout << "Arquivo <" << arquivo << "> gravado com sucesso!" << endl;
    return true;
}

bool ClassificadorTBL::carregarConhecimento( string arquivo )
{
    ifstream arqin( arquivo.c_str() );
    if( !arqin.is_open() ) //verifica se arquivo conseguiu ser aberto
    {
        cout << "Erro:carregarConhecimento!\nFalha na abertura do arquivo!" << endl;
        return false;
    }
    arqin >> atributoChute;

    string palavra1, palavra2;
    int posicao;
    char ch ;
    multimap< int, vector< string > > atributoValor;
    vector< string > vetString(2);
    arqin.get( ch );//caso inicial p/ diferenciar de \n

    while( arqin.good() )
    {
        palavra1.push_back( ch );
        while( ch != '\n' && arqin.good() )
        {
            for( arqin.get( ch ); ch != ' '; arqin.get( ch ) )
                palavra1.push_back( ch );
            /*if( palavra1.compare( "=>" ) )
            {
                palavra1.clear();
                while( ch != '\n' )
                {
                    for( arqin.get( ch ); ch != ' '; arqin.get( ch ) )
                        palavra1.push_back( ch );
                    for( arqin.get( ch ); ch != ' ' && ch != '\n'; arqin.get( ch ) )
                        palavra2.push_back( ch );
                    atributoValor2[palavra1] = palavra2;
                    palavra1.clear();
                    palavra2.clear();
                }
            }*/
            if( palavra1 == "=>" )
            {
                for( arqin.get( ch ); ch != ' ' && ch != '\n' && arqin.good(); arqin.get( ch ) )
                    palavra2.push_back( ch );
                respRegras.push_back( palavra2 );
            }
            else
            {
                arqin >> posicao;
                arqin.get( ch );
                for( arqin.get( ch ); ch != ' '; arqin.get( ch ) )
                    palavra2.push_back( ch );
                vetString[0] = palavra1;
                vetString[1] = palavra2;
                atributoValor.insert( pair< int, vector< string > >( posicao, vetString ) );
                //palavra1.clear();
                //palavra2.clear();
            }
            palavra1.clear();
            palavra2.clear();
        }
        regras.push_back( atributoValor );
        atributoValor.clear();
        arqin.get( ch );
    }

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
