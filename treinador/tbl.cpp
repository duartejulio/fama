#include "tbl.h"

bool contemEstrutura( multimap< int, vector< int > > estrutura, multimap< int, vector< int > > bestEstrutura )
{
    bool encontrou;
    multimap<int, vector< int > >::iterator linha, linha_end, bp, bp_end;
    pair< multimap<int, vector< int > >::iterator, multimap<int, vector< int > >::iterator > bounds;

    linha_end = bestEstrutura.end();
    for( linha = bestEstrutura.begin(); linha != linha_end; linha++ )
    {
        encontrou = false;
        bounds = estrutura.equal_range( linha->first );
        bp_end = bounds.second;
        for( bp = bounds.first; bp != bp_end; bp++ )
            if( bp->second == linha->second )
            {
                encontrou = true;
                break;
            }
        if( !encontrou ) return false;
    }
    return true;
}

TBL::TBL( Classificador* classInicial, string arqMoldeRegras, int toleranciaScore )
{
    this->classInicial = classInicial;
    this->toleranciaScore = toleranciaScore;
    carregarMolde( arqMoldeRegras );
}

TBL::~TBL()
{
    //dtor
}

Classificador *TBL::executarTreinamento( Corpus &corpus, int atributo )
{
    ClassificadorTBL *objClassificador = new ClassificadorTBL( classInicial );
    int row = corpus.pegarQtdSentencas(), column, numMoldeRegras = this->moldeRegras.size(), numRegras, numRegrasOld, qtdAtributos, maxScore = toleranciaScore, maxIndice, aux, frases_ijReal, frases_ijAjuste;
    bool moldeInvalido, regraInvalida, utilizaPos;
    multimap< int, vector< int > > var;
    vector< int > vet(2);
    vector< string > vetString(2);
    //iterators
    int i,j,k,L,M;
    multimap<int, vector< int > >::iterator linha, linha_end;
    multimap< int, int >::iterator itMolde, itMolde_end;
    vector< Regra >::iterator it_regras;
    multimap< multimap< int, vector< int > >, int >::iterator bp, bp_end;
    pair< multimap< multimap< int, vector< int > >, int >::iterator, multimap< multimap< int, vector< int > >, int >::iterator > ret;

    //estrutura de multimap para busca otimizada de regras repetidas
    multimap< multimap< int, vector< int > >, int > regrasTemporarias;
    vector< multimap< int, vector< int > > > regrasArmazenadas;
    vector< Regra > regras;
    vector< multimap< int, int> > moldeRegras( numMoldeRegras );

    //Classificação inicial do corpus
    classInicial->executarClassificacao( corpus, ATRBT_CLASSIFICADO );

    //converter molde de regras
    int tamMinMolde = 0, tamMaxMolde = 0;
    {   //validade local
        multimap< int, string >::iterator itMolde, itMolde_end;
        for( register int i = 0; i < numMoldeRegras; i++ )
        {
            itMolde_end = this->moldeRegras[i].end();
            for( itMolde = this->moldeRegras[i].begin(); itMolde != itMolde_end; itMolde++ )
            {
                moldeRegras[i].insert( pair< int, int >( itMolde->first, corpus.pegarPosAtributo( itMolde->second ) ) );
                if( itMolde->first < tamMinMolde ) tamMinMolde = itMolde->first;
                if( itMolde->first > tamMaxMolde ) tamMaxMolde = itMolde->first;
            }
        }
    }

    qtdAtributos = corpus.pegarQtdAtributos();

    //cria primeiras regras
    for( i = 0; i < row; i++ )
    {
        column = corpus.pegarQtdTokens( i );
        for( j = 0; j < column; j++ )
            if( ( frases_ijReal = corpus.pegarValor(i,j,atributo) ) != corpus.pegarValor(i,j, qtdAtributos - 1) )
            {
                for( L = 0; L < numMoldeRegras; L++ )
                {
                    moldeInvalido = false;

                    itMolde_end = moldeRegras[L].end();
                    for( itMolde = moldeRegras[L].begin(); itMolde != itMolde_end; itMolde++ )
                    {
                        if( ( aux = j + itMolde->first ) >= column || aux < 0 )
                        {
                            moldeInvalido = true;
                            break;
                        }
                        vet[0] = itMolde->second;
                        vet[1] = corpus.pegarValor(i, aux, vet[0]);
                        var.insert( pair< int, vector< int > >( itMolde->first, vet ) );
                    }
                    if( !moldeInvalido )
                    {
                        ret = regrasTemporarias.equal_range( var );
                        bp_end = ret.second;
                        for( bp = ret.first; bp != bp_end; bp++ )
                            if( bp->second == frases_ijReal )
                            {
                                moldeInvalido = true;
                                break;
                            }
                        if( !moldeInvalido )
                        {
                            regrasTemporarias.insert( pair< multimap< int, vector< int > >, int >( var, frases_ijReal ) );
                            Regra r( var, frases_ijReal );
                            regras.push_back( r );
                        }
                    }
                    var.clear();
                }
            }
    }

    numRegras = regras.size();
    cout << "numRegras: " << numRegras << endl;

//    for( i = 0; i < row; i++ )
//    {
//        column = corpus.pegarQtdTokens( i );
//        for( j = 0; j < column; j++ )
//        {
//            frases_ijReal = corpus.pegarValor(i,j,atributo);
//            frases_ijAjuste = corpus.pegarValor(i,j,qtdAtributos-1);
//            for( L = 0; L < numRegras; L++ )
//            {
//                regraInvalida = false;
//
//                linha_end = regras[L].estrutura.end();
//                for( linha = regras[L].estrutura.begin(); linha != linha_end; linha++ )
//                {
//                    //tirar esse if em um loop individual?
//                    if( ( aux = j + linha->first ) >= column || aux < 0 )
//                    {
//                        regraInvalida = true;
//                        break;
//                    }
//                    if( corpus.pegarValor(i,aux,linha->second[0]) != linha->second[1] )
//                    {
//                        regraInvalida = true;
//                        break;
//                    }
//                }
//                if( !regraInvalida )
//                {
//                    if( frases_ijReal == regras[L].resp && frases_ijReal != frases_ijAjuste )
//                        regras[L].good++;
//                    if( frases_ijReal != regras[L].resp && frases_ijReal == frases_ijAjuste )
//                        regras[L].bad++;
//                }
//            }
//        }
//    }

    //salvarEstado("outputs/saveScore.txt",regras);
    carregarEstado("inputs/saveScore.txt",regras);

    maxScore = -999999999;
    for( L = 0; L < numRegras; L++ )
        if( ( aux = regras[L].good - regras[L].bad ) > maxScore )
        {
            maxScore = aux;
            maxIndice = L;
        }
    //impressão da melhor regra
    cout << "maxScore: " << maxScore << endl;
    linha_end = regras[maxIndice].estrutura.end();
    for( linha = regras[maxIndice].estrutura.begin(); linha != linha_end; linha++ )
        cout << corpus.pegarAtributo(linha->second[0]) << ' ' << linha->first << ' ' << corpus.pegarSimbolo(linha->second[1]) << ' ';
    cout << "=>" << ' ' << corpus.pegarSimbolo(regras[maxIndice].resp) << endl;

    while( maxScore >= toleranciaScore && regras.size() > 0 )
    {
        //armazenar regra
        regrasArmazenadas.push_back( regras[maxIndice].estrutura );
        multimap< int, vector< string > > rule;
        linha_end = regras[maxIndice].estrutura.end();
        for( linha = regras[maxIndice].estrutura.begin(); linha != linha_end; linha++ )
        {
            vetString[0] = corpus.pegarAtributo( linha->second[0] );
            vetString[1] = corpus.pegarSimbolo( linha->second[1] );
            rule.insert( pair< int, vector< string > >( linha->first, vetString ) );
        }
        objClassificador->inserirRegra( rule, corpus.pegarSimbolo( regras[maxIndice].resp ) );


        //atualizar Corpus com a nova regra
        for( i = 0; i < row; i++ )
        {
            column = corpus.pegarQtdTokens( i );
            for( j = 0; j < column; j++ )
            {
                regraInvalida = false;

                linha_end = regras[maxIndice].estrutura.end();
                for( linha = regras[maxIndice].estrutura.begin(); linha != linha_end; linha++ )
                {
                    //tirar esse if em um loop individual?
                    if( ( aux = j + linha->first ) >= column || aux < 0 )
                    {
                        regraInvalida = true;
                        break;
                    }
                    if( corpus.pegarValor(i,aux,linha->second[0]) != linha->second[1] )
                    {
                        regraInvalida = true;
                        break;
                    }
                }
                if( !regraInvalida && corpus.pegarValor(i,j,qtdAtributos-1) != regras[maxIndice].resp )
                {
                    //decremento do bad e do good da vizinhança da palavra alterada
                    ///trocar k com L é melhor?
                    for( k = tamMinMolde; k <= tamMaxMolde; k++ )
                    {
                        if( j - k < 0 || j - k >= column ) continue;
                        frases_ijReal = corpus.pegarValor(i,j-k,atributo);
                        frases_ijAjuste = corpus.pegarValor(i,j-k, qtdAtributos - 1);
                        for( L = 0; L < numRegras; L++ )
                        {
                            if( regras[L].estrutura.begin()->first > k || regras[L].estrutura.rbegin()->first < k ) continue;
                            utilizaPos = moldeInvalido = false;

                            linha_end = regras[L].estrutura.end();
                            for( linha = regras[L].estrutura.begin(); linha != linha_end; linha++ )
                            {
                                //tirar esse if em um loop individual?
                                if( ( aux = j - k + linha->first ) >= column || aux < 0 )
                                {
                                    moldeInvalido = true;
                                    break;
                                }
                                if( corpus.pegarValor(i,aux,linha->second[0]) != linha->second[1] )
                                {
                                    moldeInvalido = true;
                                    break;
                                }
                                else//verifica se regra realmente é influenciada pela nova classificação
                                    if( aux == j ) utilizaPos = true;
                            }
                            if( !moldeInvalido && utilizaPos )
                            {
                                if( frases_ijReal == regras[L].resp && frases_ijReal != frases_ijAjuste )
                                    regras[L].good--;
                                if( frases_ijReal != regras[L].resp && frases_ijReal == frases_ijReal )
                                    regras[L].bad--;
                            }
                        }
                    }

                    corpus.ajustarValor(i,j,qtdAtributos - 1,regras[maxIndice].resp);

                    //criação das novas regras e incremento do good e do bad
                    ///trocar k com L é melhor?
                    for( k = tamMinMolde; k <= tamMaxMolde; k++ )
                    {
                        if( j - k < 0 || j - k >= column )continue;
                        if( ( frases_ijReal = corpus.pegarValor(i,j-k,atributo) ) != ( frases_ijAjuste = corpus.pegarValor(i,j-k,qtdAtributos-1) ) )
                        {
                            //aplicar molde de regras na vizinhança da palavra alterada
                            for( L = 0; L < numMoldeRegras; L++ )
                            {
                                //verifica se o molde realmente se encaixa na vizinhança
                                if( moldeRegras[L].begin()->first > k || moldeRegras[L].rbegin()->first < k ) continue;
                                utilizaPos = moldeInvalido = false;

                                itMolde_end = moldeRegras[L].end();
                                for( itMolde = moldeRegras[L].begin(); itMolde != itMolde_end; itMolde++ )
                                {
                                    if( ( aux = j - k + itMolde->first ) >= column || aux < 0 )
                                    {
                                        moldeInvalido = true;
                                        break;
                                    }
                                    if( aux == j ) utilizaPos = true;
                                    vet[0] = itMolde->second;
                                    vet[1] = corpus.pegarValor(i, aux, vet[0]);
                                    var.insert( pair< int, vector< int > >( itMolde->first, vet ) );
                                }
                                if( !moldeInvalido && utilizaPos )
                                {
                                    numRegrasOld = regrasArmazenadas.size();
                                    for( M = 0; M < numRegrasOld; M++ )
                                    {
                                        if( contemEstrutura( var, regrasArmazenadas[M] ) )
                                        {
                                            moldeInvalido = true;
                                            break;
                                        }
                                    }
                                    if( !moldeInvalido )
                                    {
                                        ret = regrasTemporarias.equal_range( var );
                                        bp_end = ret.second;
                                        for( bp = ret.first; bp != bp_end; bp++ )
                                            if( bp->second == frases_ijReal )
                                            {
                                                moldeInvalido = true;
                                                break;
                                            }
                                        if( !moldeInvalido )
                                        {
                                            regrasTemporarias.insert( pair< multimap< int, vector< int > >, int >( var, frases_ijReal ) );
                                            Regra r( var, frases_ijReal );
                                            regras.push_back( r );
                                        }
                                    }
                                }
                                var.clear();
                            }
                        }
                        for( L = 0; L < numRegras; L++ )
                        {
                            //verifica se a regra realmente se encaixa na vizinhança
                            if( regras[L].estrutura.begin()->first > k || regras[L].estrutura.rbegin()->first < k ) continue;
                            utilizaPos = moldeInvalido = false;

                            linha_end = regras[L].estrutura.end();
                            for( linha = regras[L].estrutura.begin(); linha != linha_end; linha++ )
                            {
                                //tirar esse if em um loop individual?
                                if( ( aux = j - k + linha->first ) >= column || aux < 0 )
                                {
                                    moldeInvalido = true;
                                    break;
                                }
                                if( corpus.pegarValor(i,aux,linha->second[0]) != linha->second[1] )
                                {
                                    moldeInvalido = true;
                                    break;
                                }
                                else//verifica se regra realmente é influenciada pela nova classificação
                                    if( aux == j) utilizaPos = true;
                            }
                            if( !moldeInvalido && utilizaPos )
                            {
                                if( frases_ijReal == regras[L].resp && frases_ijReal != frases_ijAjuste )
                                    regras[L].good++;
                                if( frases_ijReal != regras[L].resp && frases_ijReal == frases_ijReal )
                                    regras[L].bad++;
                            }
                        }
                    }
                }
            }
        }

        numRegrasOld = numRegras;
        numRegras = regras.size();
        cout << "numRegras: " << numRegras << endl;

        for( i = 0; i < row; i++ )
        {
            column = corpus.pegarQtdTokens( i );
            for( j = 0; j < column; j++ )
            {
                frases_ijReal = corpus.pegarValor(i,j,atributo);
                frases_ijAjuste = corpus.pegarValor(i,j,qtdAtributos-1);
                for( L = numRegrasOld; L < numRegras; L++ )
                {
                    regraInvalida = false;

                    linha_end = regras[L].estrutura.end();
                    for( linha = regras[L].estrutura.begin(); linha != linha_end; linha++ )
                    {
                        //tirar esse if em um loop individual?
                        if( ( aux = j + linha->first ) >= column || aux < 0 )
                        {
                            regraInvalida = true;
                            break;
                        }
                        if( corpus.pegarValor(i,aux,linha->second[0]) != linha->second[1] )
                        {
                            regraInvalida = true;
                            break;
                        }
                    }
                    if( !regraInvalida )
                    {
                        if( frases_ijReal == regras[L].resp && frases_ijReal != frases_ijAjuste )
                            regras[L].good++;
                        if( frases_ijReal != regras[L].resp && frases_ijReal == frases_ijAjuste )
                            regras[L].bad++;
                    }
                }
            }
        }



        //remover regras cuja estrutura contem a estrutura da melhor regra
        multimap< int, vector< int > > bestEstrutura  = regras[maxIndice].estrutura;
        i = 0;
        j = numRegras - 1;
        while( i < j )
            if( contemEstrutura( regras[i].estrutura, bestEstrutura ) )
            {
                swap( regras[i], regras[j] );
                j--;
            }
            else i++;

        regras.erase( regras.begin()+i+1, regras.end() );

        numRegras = regras.size();

        maxScore = -999999999;
        for( L = 0; L < numRegras; L++ )
            if( ( aux = regras[L].good - regras[L].bad ) > maxScore )
            {
                maxScore = aux;
                maxIndice = L;
            }
        //impressão da melhor regra
        cout << "maxScore: " << maxScore << endl;
        linha_end = regras[maxIndice].estrutura.end();
        for( linha = regras[maxIndice].estrutura.begin(); linha != linha_end; linha++ )
            cout << corpus.pegarAtributo(linha->second[0]) << ' ' << linha->first << ' ' << corpus.pegarSimbolo(linha->second[1]) << ' ';
        cout << "=>" << ' ' << corpus.pegarSimbolo(regras[maxIndice].resp) << endl;
    }

    return objClassificador;
}

bool TBL::carregarMolde( string arqMoldeRegras )
{
    ifstream arqin( arqMoldeRegras.c_str() );
    if( !arqin.is_open() ) //verifica se arquivo conseguiu ser aberto
    {
        cout << "Erro:carregarMolde!\nFalha na abertura do arquivo!" << endl;
        return false;
    }

    string palavra1;
    int posicao;
    char ch ;
    multimap< int, string > indiceAtributo;


    while( arqin.good() )
    {
        arqin.get( ch );//caso inicial p/ diferenciar de \n
        palavra1.push_back( ch );
        while( ch != '\n' && arqin.good() )
        {
            for( arqin.get( ch ); ch != ' ' && ch != ':'; arqin.get( ch ) )
                palavra1.push_back( ch );
            arqin >> posicao;
            indiceAtributo.insert( pair< int, string >( posicao, palavra1 ) );
            palavra1.clear();
            arqin.get( ch );
        }
        moldeRegras.push_back( indiceAtributo );
        indiceAtributo.clear();
    }


    if( arqin.bad() && !arqin.eof() )    //caso de erro na leitura do arquivo
    {
        cout << "Erro:carregarMolde!\nErro na leitura do arquivo!" << endl;
        arqin.close();
        return false;
    }

    arqin.close();
    cout << "Molde de Regras <" << arqMoldeRegras << "> carregado com sucesso!" << endl;
    return true;
}

bool TBL::salvarEstado( string saveFile, vector< Regra > regras )
{
    ofstream arqout( saveFile.c_str() );
    if( !arqout.is_open() ) //verifica se arquivo conseguiu ser aberto
    {
        cout << "Erro:salvarEstado!\nFalha na abertura do arquivo!" << endl;
        return false;
    }

    int numRegras = regras.size();

    for( register int i = 0; i < numRegras; i++ )
    {
        arqout << regras[i].good << ' ' << regras[i].bad << endl;
    }

    arqout.close();
    cout << "Estado <" << saveFile << "> salvo com sucesso!" << endl;
    return true;
}

bool TBL::carregarEstado( string saveFile, vector< Regra > &regras )
{
    ifstream arqin( saveFile.c_str() );
    if( !arqin.is_open() ) //verifica se arquivo conseguiu ser aberto
    {
        cout << "Erro:carregarEstado!\nFalha na abertura do arquivo!" << endl;
        return false;
    }

    int numRegras = regras.size(), g, b;

    for( register int i = 0; i < numRegras; i++ )
    {
        arqin >> g;
        regras[i].good = g;
        arqin >> b;
        regras[i].bad = b;
    }

    if( arqin.bad() && !arqin.eof() )    //caso de erro na leitura do arquivo
    {
        cout << "Erro:carregarEstado!\nErro na leitura do arquivo!" << endl;
        arqin.close();
        return false;
    }

    arqin.close();
    cout << "Estado <" << saveFile << "> carregado com sucesso!" << endl;
    return true;
}
