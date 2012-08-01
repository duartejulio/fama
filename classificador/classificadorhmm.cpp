#include "classificadorhmm.h"

void ClassificadorHMM::definirMatrizTransicao( map< string, map< string, double > > matrizTransicao )
{
    this->matrizTransicao = matrizTransicao;
}

void ClassificadorHMM::ajustarTabFreqObservacoes( string pos, string palavra )
{
    ++tabFreqObservacoes[ pos ][ palavra ];
}

void ClassificadorHMM::ajustarVetInicial( string pos )
{
    ++vetInicial[ pos ];
}

bool ClassificadorHMM::executarClassificacao( Corpus &corpusProva, int atributo )
{
    corpusProva.criarAtributo( "pos", "N" );
    int tam_atributos = corpusProva.pegarQtdAtributos() - 1;
    int row = corpusProva.pegarQtdSentencas(), column, aux;
    vector< int > numPos; //vetor que contem valor dos POS
    map< string, map< string, double > >::iterator linha, linha_end;
    map< string, double >::iterator coluna, coluna_end;

    map< int, map< int, double > > matrizTransicaoInt;
    map< int, map< int, double > > tabFreqObservacoesInt;
    map< int, double > vetInicialInt;


    /// /////////////////////////////////////////////////////////////////////////////////////////////////////
    /// CONVERTER OS MAPS DE STRINGs PARA INTs
    linha_end = matrizTransicao.end();
    for( linha = matrizTransicao.begin(); linha != linha_end; ++linha )
    {
        aux = corpusProva.pegarIndice(linha->first);
        coluna_end = linha->second.end();
        for( coluna = linha->second.begin(); coluna != coluna_end; ++coluna )
            matrizTransicaoInt[ aux ][ corpusProva.pegarIndice(coluna->first) ] = coluna->second;
    }

//    vector< double > total(1000000);
//
//    cout << total[99999] << endl;
//
//    for( linha = tabFreqObservacoes.begin(); linha != tabFreqObservacoes.end(); linha++ )
//    {
//        for( coluna = linha->second.begin(); coluna != linha->second.end(); coluna++ )
//            total[corpusProva.pegarIndice(linha->first)] += coluna->second;
//    }
//    for( linha = tabFreqObservacoes.begin(); linha != tabFreqObservacoes.end(); linha++ )
//    {
//        for( coluna = linha->second.begin(); coluna != linha->second.end(); coluna++ )
//            tabFreqObservacoes[linha->first][coluna->first] = coluna->second/total[corpusProva.pegarIndice(coluna->first)] ;
//    }

    linha_end = tabFreqObservacoes.end();
    for( linha = tabFreqObservacoes.begin(); linha != linha_end; ++linha )
    {
        aux = corpusProva.pegarIndice(linha->first);
        numPos.push_back( aux );
        coluna_end = linha->second.end();
        for( coluna = linha->second.begin(); coluna != coluna_end; ++coluna )
            tabFreqObservacoesInt[ corpusProva.pegarIndice(coluna->first) ][ aux ] = coluna->second;
    }

//    double total = 0.0;
//    map< int, map< int, double > >::iterator linha2;
//    map< int, double >::iterator coluna2;
//
//    for( linha2 = tabFreqObservacoesInt.begin();  linha2!= tabFreqObservacoesInt.end(); linha2++ )
//    {
//        for( coluna2 = linha2->second.begin(); coluna2 != linha2->second.end(); coluna2++ )
//            total += coluna2->second;
//        for( coluna2 = linha2->second.begin(); coluna2 != linha2->second.end(); coluna2++ )
//            tabFreqObservacoesInt[linha2->first][coluna2->first] = ( coluna2->second )/total;
//        total = 0.0;
//    }
    coluna_end = vetInicial.end();
    for( coluna = vetInicial.begin(); coluna != coluna_end; ++coluna )
        vetInicialInt[ corpusProva.pegarIndice(coluna->first) ] = coluna->second;
    /// /////////////////////////////////////////////////////////////////////////////////////////////////////

    map< int, map< int, double > >::iterator linhaInt_end;
    int linhaViterbi, linhaVtbAnt, qtdPos = numPos.size(), maiorIndice = 0;
    double matrizViterbi[2][qtdPos], maiorValor, aux_double;

    //verifica o valor da coluna mais extensa de frases[][]
    for( register int i = 0; i < row; ++i )
        if( ( aux = corpusProva.pegarQtdTokens( i ) ) > maiorIndice ) maiorIndice = aux;
    int caminho[maiorIndice][qtdPos];


    linhaInt_end = tabFreqObservacoesInt.end();
    for ( register int i = 0; i < row; ++i )
    {
        column = corpusProva.pegarQtdTokens( i );
        linhaViterbi = 0;

        ///Verificar depois se transpor a matriz B nao afeta em nada o codigo
        //preenchimento do estado inicial
        if ( tabFreqObservacoesInt.find( aux = corpusProva.pegarValor(i,0,atributo) ) != linhaInt_end )
            for( register int k = 0; k < qtdPos; ++k )
                matrizViterbi[linhaViterbi][k] = log( vetInicialInt[ numPos[k] ] ) + log( tabFreqObservacoesInt[ aux ][ numPos[k] ] );
            //cout << corpusProva.pegarSimbolo( numPos[k] ) << ' ' << matrizViterbi[linhaViterbi][k] << ' ';

        else
            for( register int k = 0; k < qtdPos; ++k )
                matrizViterbi[linhaViterbi][k] = log( vetInicialInt[ numPos[k] ] ); // caso a frequencia seja zero para todos os estados
                     //cout << corpusProva.pegarSimbolo( numPos[k] ) << ' ' << matrizViterbi[linhaViterbi][k] << ' ';               /** PI x B */

        linhaVtbAnt = linhaViterbi; //criado para otimização
        linhaViterbi = 1;
        //varrer as observações
        for( register int j = 1; j < column; ++j )
        {
            //varre os estados
            if ( tabFreqObservacoesInt.find( aux = corpusProva.pegarValor(i,j,atributo) ) != linhaInt_end )
                for( register int k = 0; k < qtdPos; ++k )
                {
                    maiorValor = 0.0;
                    //varre os estados na linha anterior
                    for( register int l = 0; l < qtdPos; ++l )
                        if( ( aux_double = matrizViterbi[ linhaVtbAnt ][l] + log( matrizTransicaoInt[numPos[l]][numPos[k]] )  ) >= maiorValor )
                        {
                            maiorValor = aux_double;
                            maiorIndice = l;
                        }

                    matrizViterbi[linhaViterbi][k] = maiorValor + log( tabFreqObservacoesInt[ aux ][ numPos[k] ] );
                    caminho[j][k] = maiorIndice;
                }
            else
                for( register int k = 0; k < qtdPos; ++k )
                {
                    maiorValor = 0.0;
                    //varre os estados na linha anterior
                    for( register int l = 0; l < qtdPos; ++l )
                        if( ( aux_double = matrizViterbi[ linhaVtbAnt ][l] + log( matrizTransicaoInt[numPos[l]][numPos[k]] ) ) >= maiorValor )
                        {
                            maiorValor = aux_double;
                            maiorIndice = l;
                        }

                    matrizViterbi[linhaViterbi][k] = maiorValor; // caso a frequencia seja zero para todos os estados
                    caminho[j][k] = maiorIndice;
                }
            linhaVtbAnt = linhaViterbi;
            ++linhaViterbi %= 2;
        }

        maiorValor = 0.0;
        for( register int m = 0; m < qtdPos; ++m )
            if( ( aux_double = matrizViterbi[linhaVtbAnt][m] ) >= maiorValor )
            {
                maiorValor = aux_double;
                maiorIndice = m;
            }

        for( register int j = column - 1; j >= 0 ; --j )
        {
            corpusProva.ajustarValor( i, j, tam_atributos, numPos[ maiorIndice ] );
            maiorIndice = caminho[j][ maiorIndice ];
        }
    }

    return true;
}

bool ClassificadorHMM::gravarConhecimento( string arquivo )
{
    ofstream arqout( arquivo.c_str() );
    if( !arqout.is_open() ) //verifica se arquivo conseguiu ser aberto
    {
        cout << "Erro:gravarConhecimento!\nFalha na abertura do arquivo!" << endl;
        return false;
    }

    map< string, map< string, double > >::iterator linha, linha_end;
    map< string, double >::iterator coluna, coluna_end;

    linha_end = matrizTransicao.end();
    for( linha = matrizTransicao.begin(); linha != linha_end; ++linha )
    {
        arqout << linha->first << ' ';
        coluna_end = linha->second.end();
        for( coluna = linha->second.begin(); coluna != coluna_end; ++coluna )
            arqout << coluna->first << ' ' << coluna->second << ' ';
        arqout << endl;
    }
    arqout << endl;

    linha_end = tabFreqObservacoes.end();
    for( linha = tabFreqObservacoes.begin(); linha != linha_end; ++linha )
    {
        arqout << linha->first << ' ';
        coluna_end = linha->second.end();
        for( coluna = linha->second.begin(); coluna != coluna_end; ++coluna )
            arqout << coluna->first << ' ' << coluna->second << ' ';
        arqout << endl;
    }
    arqout << endl;

    coluna_end = vetInicial.end();
    for( coluna = vetInicial.begin(); coluna != coluna_end; ++coluna )
        arqout << coluna->first << endl << coluna->second << endl;

    arqout.close();
    cout << "Arquivo <" << arquivo << "> gravado com sucesso!" << endl;
    return true;
}

bool ClassificadorHMM::carregarConhecimento( string arquivo )
{
    ifstream arqin( arquivo.c_str() );
    if( !arqin.is_open() ) //verifica se arquivo conseguiu ser aberto
    {
        cout << "Erro:carregarConhecimento!\nFalha na abertura do arquivo!" << endl;
        return false;
    }
    string palavra1, palavra2;
    char ch;
    double acumulador;


    arqin >> palavra1;
    while( arqin.good() )
    {
        arqin.get( ch ); //exclui espaço vazio
        arqin.get( ch );
        while( ch != ' ' && ch != '\n' )
        {
            palavra2.push_back( ch );
            arqin.get( ch );
        }
        if( ch == '\n' )
        {
            arqin.get( ch );
            if( ch == '\n' ) break;
            palavra1.clear();
            while( ch != ' ' )
            {
                palavra1.push_back( ch );
                arqin.get( ch );
            }
            arqin.get( ch );
            while( ch != ' ' )
            {
                palavra2.push_back( ch );
                arqin.get( ch );
            }
        }
        arqin >> acumulador;
        //utilizado para poder carregar mais de um conhecimento
        matrizTransicao[palavra1][palavra2] += acumulador;
        palavra2.clear();
    }

    arqin >> palavra1;
    while( arqin.good() )
    {
        arqin.get( ch ); //exclui espaço vazio
        arqin.get( ch );
        while( ch != ' ' && ch != '\n' )
        {
            palavra2.push_back( ch );
            arqin.get( ch );
        }
        if( ch == '\n' )
        {
            arqin.get( ch );
            if( ch == '\n' ) break;
            palavra1.clear();
            while( ch != ' ' )
            {
                palavra1.push_back( ch );
                arqin.get( ch );
            }
            arqin.get( ch );
            while( ch != ' ' )
            {
                palavra2.push_back( ch );
                arqin.get( ch );
            }
        }
        arqin >> acumulador;
        tabFreqObservacoes[palavra1][palavra2] += acumulador;
        palavra2.clear();
    }

    while( arqin >> palavra1 && arqin.good() )
    {
        arqin >> acumulador;
        vetInicial[ palavra1 ] += acumulador;
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
