#include "tbl.h"

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
    map< int, map< int, int > > var;
    //iterators
    int i,j,k,L;
    map<int, map< int, int > >::iterator linha, linha_end;
    map< int, int >::iterator it, it_end;
    vector< map< int, map< int, int > > >::iterator it_regras;
    vector< int >::iterator it_respRegras, it_good, it_bad;
    multimap< map< int, map< int, int > >, int >:: iterator bp, bp_end;
    pair< multimap< map< int, map< int, int > >, int >:: iterator, multimap< map< int, map< int, int > >, int >:: iterator > ret;

    //estrutura de multimap para busca otimizada de regras repetidas
    multimap< map< int, map< int, int > >, int > regrasTemporarias;

    set< map< int, map< int, int > > > regrasArmazenadas;
    vector< map< int, map< int, int > > > regras;
    vector< int > respRegras, good, bad;//se for feita mais de uma classificação simultanea respRegras tem que ser atualizado para map e respMolde tem que ser criado
    vector< map< int, int> > moldeRegras( numMoldeRegras );

    //Classificação inicial do corpus
    classInicial->executarClassificacao( corpus, ATRBT_CLASSIFICADO );

    //converter molde de regras
    int tamMinMolde = 0, tamMaxMolde = 0;
    map< int, string >::iterator itMolde, itMolde_end;
    for( register int i = 0; i < numMoldeRegras; i++ )
    {
        itMolde_end = this->moldeRegras[i].end();
        for( itMolde = this->moldeRegras[i].begin(); itMolde != itMolde_end; itMolde++ )
        {
            moldeRegras[i][itMolde->first] = corpus.pegarPosAtributo( itMolde->second );
            if( itMolde->first < tamMinMolde ) tamMinMolde = itMolde->first;
            if( itMolde->first > tamMaxMolde ) tamMaxMolde = itMolde->first;
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

                    it_end = moldeRegras[L].end();
                    for( it = moldeRegras[L].begin(); it != it_end; it++ )
                    {
                        if( ( aux = j + it->first ) >= column || aux < 0 )
                        {
                            moldeInvalido = true;
                            break;
                        }
                        var[it->first][it->second] = corpus.pegarValor(i, aux, it->second);
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
                            regrasTemporarias.insert( pair< map< int, map< int, int > >, int >( var, frases_ijReal ) );
                            regras.push_back( var );
                            respRegras.push_back( frases_ijReal );
                        }
                    }
                    var.clear();
                }
            }
    }

    numRegras = regras.size();
    good.resize( numRegras );
    bad.resize( numRegras );
    cout << "numRegras: " << numRegras << endl;

    for( i = 0; i < row; i++ )
    {
        column = corpus.pegarQtdTokens( i );
        for( j = 0; j < column; j++ )
        {
            frases_ijReal = corpus.pegarValor(i,j,atributo);
            frases_ijAjuste = corpus.pegarValor(i,j,qtdAtributos-1);
            for( L = 0; L < numRegras; L++ )
            {
                regraInvalida = false;

                linha_end = regras[L].end();
                for( linha = regras[L].begin(); linha != linha_end; linha++ )
                {
                    //tirar esse if em um loop individual?
                    if( ( aux = j + linha->first ) >= column || aux < 0 )
                    {
                        regraInvalida = true;
                        break;
                    }
                    it_end = linha->second.end();
                    for( it = linha->second.begin(); it != it_end; it++ )
                        if( corpus.pegarValor(i,aux,it->first) != it->second )
                        {
                            regraInvalida = true;
                            break;
                        }
                    if( regraInvalida ) break;
                }
                if( !regraInvalida )
                {
                    if( frases_ijReal == respRegras[L] && frases_ijReal != frases_ijAjuste )
                        good[L]++;
                    if( frases_ijReal != respRegras[L] && frases_ijReal == frases_ijAjuste )
                        bad[L]++;
                }
            }
        }
    }

    //salvarEstado("outputs/saveScore.txt",good,bad);
    //carregarEstado("inputs/saveScore.txt",good,bad);

    maxScore = -999999999;
    for( L = 0; L < numRegras; L++ )
        if( ( aux = good[L] - bad[L] ) > maxScore )
        {
            maxScore = aux;
            maxIndice = L;
        }
    //impressão da melhor regra
    cout << "maxScore: " << maxScore << endl;
    linha_end = regras[maxIndice].end();
    for( linha = regras[maxIndice].begin(); linha != linha_end; linha++ )
    {
        it_end = linha->second.end();
        for( it = linha->second.begin(); it != it_end; it++ )
            cout << corpus.pegarAtributo(it->first) << ' ' << linha->first << ' ' << corpus.pegarSimbolo(it->second) << ' ';
    }
    cout << "=>" << ' ' << corpus.pegarSimbolo(respRegras[maxIndice]) << endl;


    while( maxScore >= toleranciaScore && regras.size() > 0 )
    {
        //armazenar regra
        regrasArmazenadas.insert( regras[maxIndice] );
        map< int, map< string, string > > rule;
        linha_end = regras[maxIndice].end();
        for( linha = regras[maxIndice].begin(); linha != linha_end; linha++ )
        {
            it_end = linha->second.end();
            for( it = linha->second.begin(); it != it_end; it++ )
                rule[linha->first][corpus.pegarAtributo( it->first )] = corpus.pegarSimbolo( it->second );
        }
        objClassificador->inserirRegra( rule, corpus.pegarSimbolo( respRegras[maxIndice] ) );


        //atualizar Corpus com a nova regra
        for( i = 0; i < row; i++ )
        {
            column = corpus.pegarQtdTokens( i );
            for( j = 0; j < column; j++ )
            {
                regraInvalida = false;

                linha_end = regras[maxIndice].end();
                for( linha = regras[maxIndice].begin(); linha != linha_end; linha++ )
                {
                    //tirar esse if em um loop individual?
                    if( ( aux = j + linha->first ) >= column || aux < 0 )
                    {
                        regraInvalida = true;
                        break;
                    }
                    it_end = linha->second.end();
                    for( it = linha->second.begin(); it != it_end; it++ )
                        if( corpus.pegarValor(i,aux,it->first) != it->second )
                        {
                            regraInvalida = true;
                            break;
                        }
                    if( regraInvalida ) break; //break externo
                }
                if( !regraInvalida && corpus.pegarValor(i,j,qtdAtributos-1) != respRegras[maxIndice] )
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
                            if( regras[L].begin()->first > k || regras[L].rbegin()->first < k ) continue;
                            utilizaPos = moldeInvalido = false;

                            linha_end = regras[L].end();
                            for( linha = regras[L].begin(); linha != linha_end; linha++ )
                            {
                                //tirar esse if em um loop individual?
                                if( ( aux = j - k + linha->first ) >= column || aux < 0 )
                                {
                                    moldeInvalido = true;
                                    break;
                                }
                                it_end = linha->second.end();
                                for( it = linha->second.begin(); it != it_end; it++ )
                                    if( corpus.pegarValor(i,aux,it->first) != it->second )
                                    {
                                        moldeInvalido = true;
                                        break;
                                    }
                                    else//verifica se regra realmente é influenciada pela nova classificação
                                        if( aux == j ) utilizaPos = true;
                                if( moldeInvalido ) break;
                            }
                            if( !moldeInvalido && utilizaPos )
                            {
                                if( frases_ijReal == respRegras[L] && frases_ijReal != frases_ijAjuste )
                                    good[L]--;
                                if( frases_ijReal != respRegras[L] && frases_ijReal == frases_ijReal )
                                    bad[L]--;
                            }
                        }
                    }

                    corpus.ajustarValor(i,j,qtdAtributos - 1,respRegras[maxIndice]);

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

                                it_end = moldeRegras[L].end();
                                for( it = moldeRegras[L].begin(); it != it_end; it++ )
                                {
                                    if( ( aux = j - k + it->first ) >= column || aux < 0 )
                                    {
                                        moldeInvalido = true;
                                        break;
                                    }
                                    if( aux == j ) utilizaPos = true;
                                    var[it->first][it->second] = corpus.pegarValor(i, aux, it->second);
                                }
                                if( !moldeInvalido && utilizaPos )
                                {
                                    if( regrasArmazenadas.find( var ) == regrasArmazenadas.end() )
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
                                            regrasTemporarias.insert( pair< map< int, map< int, int > >, int >( var, frases_ijReal ) );
                                            regras.push_back( var );
                                            respRegras.push_back( frases_ijReal );
                                        }
                                    }
                                }
                                var.clear();
                            }
                        }
                        for( L = 0; L < numRegras; L++ )
                        {
                            //verifica se a regra realmente se encaixa na vizinhança
                            if( regras[L].begin()->first > k || regras[L].rbegin()->first < k ) continue;
                            utilizaPos = moldeInvalido = false;

                            linha_end = regras[L].end();
                            for( linha = regras[L].begin(); linha != linha_end; linha++ )
                            {
                                //tirar esse if em um loop individual?
                                if( ( aux = j - k + linha->first ) >= column || aux < 0 )
                                {
                                    moldeInvalido = true;
                                    break;
                                }
                                it_end = linha->second.end();
                                for( it = linha->second.begin(); it != it_end; it++ )
                                    if( corpus.pegarValor(i,aux,it->first) != it->second )
                                    {
                                        moldeInvalido = true;
                                        break;
                                    }
                                    else//verifica se regra realmente é influenciada pela nova classificação
                                        if( aux == j) utilizaPos = true;
                                if( moldeInvalido ) break;
                            }
                            if( !moldeInvalido && utilizaPos )
                            {
                                if( frases_ijReal == respRegras[L] && frases_ijReal != frases_ijAjuste )
                                    good[L]++;
                                if( frases_ijReal != respRegras[L] && frases_ijReal == frases_ijReal )
                                    bad[L]++;
                            }
                        }
                    }
                }
            }
        }

        numRegrasOld = numRegras;
        numRegras = regras.size();
        good.resize( numRegras );
        bad.resize( numRegras );
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

                    linha_end = regras[L].end();
                    for( linha = regras[L].begin(); linha != linha_end; linha++ )
                    {
                        //tirar esse if em um loop individual?
                        if( ( aux = j + linha->first ) >= column || aux < 0 )
                        {
                            regraInvalida = true;
                            break;
                        }
                        it_end = linha->second.end();
                        for( it = linha->second.begin(); it != it_end; it++ )
                            if( corpus.pegarValor(i,aux,it->first) != it->second )
                            {
                                regraInvalida = true;
                                break;
                            }
                        if( regraInvalida ) break;
                    }
                    if( !regraInvalida )
                    {
                        if( frases_ijReal == respRegras[L] && frases_ijReal != frases_ijAjuste )
                            good[L]++;
                        if( frases_ijReal != respRegras[L] && frases_ijReal == frases_ijAjuste )
                            bad[L]++;
                    }
                }
            }
        }


        //remover regras cujo good virou zero e remover regras com molde igual a melhor regra
        var = regras[maxIndice];
        it_regras = regras.begin();
        it_respRegras = respRegras.begin();
        it_good = good.begin();
        it_bad = bad.begin();
        while( it_regras != regras.end() )
            if( *it_good <= 0 || *it_regras == var  )
            {
                it_regras = regras.erase( it_regras );
                it_respRegras = respRegras.erase( it_respRegras );
                it_good = good.erase( it_good );
                it_bad = bad.erase( it_bad );
            }
            else
            {
                it_regras++;
                it_respRegras++;
                it_good++;
                it_bad++;
            }
        numRegras = regras.size();


        //bad[maxIndice] = 999999999;
        maxScore = -999999999;
        for( L = 0; L < numRegras; L++ )
            if( ( aux = good[L] - bad[L] ) > maxScore )
            {
                maxScore = aux;
                maxIndice = L;
            }
        //impressão da melhor regra
        cout << "maxScore: " << maxScore << endl;
        linha_end = regras[maxIndice].end();
        for( linha = regras[maxIndice].begin(); linha != linha_end; linha++ )
        {
            it_end = linha->second.end();
            for( it = linha->second.begin(); it != it_end; it++ )
                cout << corpus.pegarAtributo(it->first) << ' ' << linha->first << ' ' << corpus.pegarSimbolo(it->second) << ' ';
        }
        cout << "=>" << ' ' << corpus.pegarSimbolo(respRegras[maxIndice]) << endl;
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
    map< int, string > indiceAtributo;


    while( arqin.good() )
    {
        arqin.get( ch );//caso inicial p/ diferenciar de \n
        palavra1.push_back( ch );
        while( ch != '\n' && arqin.good() )
        {
            for( arqin.get( ch ); ch != ' '; arqin.get( ch ) )
                palavra1.push_back( ch );
            arqin >> posicao;
            indiceAtributo[posicao] = palavra1;
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

//bool TBL::salvarEstado( string saveFile, vector<int> good, vector<int> bad )
//{
//    ofstream arqout( saveFile.c_str() );
//    if( !arqout.is_open() ) //verifica se arquivo conseguiu ser aberto
//    {
//        cout << "Erro:salvarEstado!\nFalha na abertura do arquivo!" << endl;
//        return false;
//    }
//
//    int numRegras = good.size();
//
//    for( register int i = 0; i < numRegras; i++ )
//    {
//        arqout << good[i] << ' ' << bad[i] << endl;
//    }
//
//    arqout.close();
//    cout << "Estado <" << saveFile << "> salvo com sucesso!" << endl;
//    return true;
//}
//
//bool TBL::carregarEstado( string saveFile, vector<int> &good, vector<int> &bad )
//{
//    ifstream arqin( saveFile.c_str() );
//    if( !arqin.is_open() ) //verifica se arquivo conseguiu ser aberto
//    {
//        cout << "Erro:carregarEstado!\nFalha na abertura do arquivo!" << endl;
//        return false;
//    }
//
//    int numRegras = good.size(), g, b;
//
//    for( register int i = 0; i < numRegras; i++ )
//    {
//        arqin >> g;
//        good[i] = g;
//        arqin >> b;
//        bad[i] = b;
//    }
//
//    if( arqin.bad() && !arqin.eof() )    //caso de erro na leitura do arquivo
//    {
//        cout << "Erro:carregarEstado!\nErro na leitura do arquivo!" << endl;
//        arqin.close();
//        return false;
//    }
//
//    arqin.close();
//    cout << "Estado <" << saveFile << "> carregado com sucesso!" << endl;
//    return true;
//}
