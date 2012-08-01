#include "tbl.h"

TBL::TBL( Classificador* classInicial, string arqMoldeRegras, int toleranciaScore )
{
    this->classInicial = classInicial;
    this->toleranciaScore = toleranciaScore;
    carregarMolde( arqMoldeRegras );
}

TBL::~TBL()
{
    delete classInicial;
}

bool TBL::contemEstrutura( multimap< int, vector< int > > estrutura, multimap< int, vector< int > > bestEstrutura )
{
    bool encontrou;
    multimap<int, vector< int > >::iterator linha, linha_end, bp, bp_end;
    pair< multimap<int, vector< int > >::iterator, multimap<int, vector< int > >::iterator > bounds;

    linha_end = bestEstrutura.end();
    for( linha = bestEstrutura.begin(); linha != linha_end; ++linha )
    {
        encontrou = false;
        bounds = estrutura.equal_range( linha->first );
        bp_end = bounds.second;
        for( bp = bounds.first; bp != bp_end; ++bp )
            if( bp->second == linha->second )
            {
                encontrou = true;
                break;
            }
        if( !encontrou ) return false;
    }
    return true;
}

Classificador *TBL::executarTreinamento( Corpus &corpus, int atributo )
{
    ClassificadorTBL *objClassificador = new ClassificadorTBL( classInicial );
    int row = corpus.pegarQtdSentencas(), column, numMoldeRegras = this->moldeRegras.size(), qtdAtributos, maxScore = toleranciaScore, aux, frases_ijReal, tam_fronteira, lim_fronteira, tam_indices;
    bool moldeInvalido, regraInvalida;
    multimap< int, vector< int > > var, bestEstrutura;
    vector< int > vet(2), vetIndices;
    vector< vector< int > > fronteira;
    vector< string > vetString(2);
    //iterators
    int i,j,k,L,M;
    multimap<int, vector< int > >::iterator linha, linha_end;
    multimap< int, int >::iterator itMolde, itMolde_end;
    multimap< multimap< int, vector< int > >, Regra >::iterator bp, bp_end, maxIndice;
    pair< multimap< multimap< int, vector< int > >, Regra >::iterator, multimap< multimap< int, vector< int > >, Regra >::iterator > ret;

    //estrutura de multimap para busca otimizada de regras repetidas
    multimap< multimap< int, vector< int > >, Regra > regrasTemporarias, regrasTemporarias2;
    vector< multimap< int, vector< int > > > regrasArmazenadas;
    vector< multimap< int, int> > moldeRegras( numMoldeRegras );

    //Classificação inicial do corpus
    classInicial->executarClassificacao( corpus, ATRBT_CLASSIFICADO );

    //converter molde de regras
    int tamMinMolde = 999999999, tamMaxMolde = -999999999;
    {   //validade local
        multimap< int, string >::iterator itMolde, itMolde_end;
        for( register int i = 0; i < numMoldeRegras; ++i )
        {
            itMolde_end = this->moldeRegras[i].end();
            for( itMolde = this->moldeRegras[i].begin(); itMolde != itMolde_end; ++itMolde )
            {
                moldeRegras[i].insert( pair< int, int >( itMolde->first, corpus.pegarPosAtributo( itMolde->second ) ) );
                if( itMolde->first < tamMinMolde ) tamMinMolde = itMolde->first;
                if( itMolde->first > tamMaxMolde ) tamMaxMolde = itMolde->first;
            }
        }
    }

    qtdAtributos = corpus.pegarQtdAtributos();

    //cria as regras temporárias e calcula o good de cada regra
    for( i = 0; i < row; ++i )
    {
        column = corpus.pegarQtdTokens( i );
        for( j = 0; j < column; ++j )
            if( ( frases_ijReal = corpus.pegarValor(i,j,atributo) ) != corpus.pegarValor(i,j, qtdAtributos - 1) )
                for( L = 0; L < numMoldeRegras; ++L )
                {
                    moldeInvalido = false;

                    itMolde_end = moldeRegras[L].end();
                    for( itMolde = moldeRegras[L].begin(); itMolde != itMolde_end; ++itMolde )
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
                        for( bp = ret.first; bp != bp_end; ++bp )
                            if( bp->second.resp == frases_ijReal )
                            {
                                ++bp->second.good;
                                moldeInvalido = true;
                                break;
                            }
                        if( !moldeInvalido )
                            regrasTemporarias.insert( pair< multimap< int, vector< int > >, Regra >( var, Regra( frases_ijReal, 1 ) ) );
                    }
                    var.clear();
                }
    }

    cout << "numRegras: " << regrasTemporarias.size() << endl;
    //calcula o bad de todas as regras
    for( i = 0; i < row; ++i )
    {
        column = corpus.pegarQtdTokens( i );
        //cout << (double)i/row << endl;
        for( j = 0; j < column; ++j )
            if( ( frases_ijReal = corpus.pegarValor(i,j,atributo) ) == corpus.pegarValor(i,j,qtdAtributos-1) )
                for( L = 0; L < numMoldeRegras; ++L )
                {
                    moldeInvalido = false;

                    itMolde_end = moldeRegras[L].end();
                    for( itMolde = moldeRegras[L].begin(); itMolde != itMolde_end; ++itMolde )
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
                        for( bp = ret.first; bp != bp_end; ++bp )
                            if( bp->second.resp != frases_ijReal )
                                ++bp->second.bad;
                    }
                    var.clear();
                }
    }

    maxScore = -999999999;
    bp_end = regrasTemporarias.end();
    for( bp = regrasTemporarias.begin(); bp != bp_end; ++bp )
        if( ( aux = bp->second.good - bp->second.bad ) > maxScore )
        {
            maxScore = aux;
            maxIndice = bp;
        }
    //impressão da melhor regra
    cout << "maxScore: " << maxScore << endl;
    bestEstrutura = maxIndice->first;
    linha_end = bestEstrutura.end();
    for( linha = bestEstrutura.begin(); linha != linha_end; ++linha )
        cout << corpus.pegarAtributo(linha->second[0]) << ' ' << linha->first << ' ' << corpus.pegarSimbolo(linha->second[1]) << ' ';
    cout << "=>" << ' ' << corpus.pegarSimbolo(maxIndice->second.resp) << endl;

    while( maxScore >= toleranciaScore && regrasTemporarias.size() > 0 )
    {
        //armazenar regra
        regrasArmazenadas.push_back( maxIndice->first );
        multimap< int, vector< string > > rule;
        bestEstrutura = maxIndice->first;
        linha_end = bestEstrutura.end();
        for( linha = bestEstrutura.begin(); linha != linha_end; ++linha )
        {
            vetString[0] = corpus.pegarAtributo( linha->second[0] );
            vetString[1] = corpus.pegarSimbolo( linha->second[1] );
            rule.insert( pair< int, vector< string > >( linha->first, vetString ) );
        }
        objClassificador->inserirRegra( rule, corpus.pegarSimbolo( maxIndice->second.resp ) );


        //atualizar Corpus com a nova regra
        for( i = 0; i < row; ++i )
        {
            column = corpus.pegarQtdTokens( i );
            for( j = 0; j < column; ++j )
            {
                regraInvalida = false;

                for( linha = bestEstrutura.begin(); linha != linha_end; ++linha )
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
                if( !regraInvalida && corpus.pegarValor(i,j,qtdAtributos-1) != maxIndice->second.resp )
                    vetIndices.push_back( j );
            }

            if( ( tam_indices = vetIndices.size() ) == 0 ) continue;
            //calculo da vizinhança das palavras alteradas
            if( ( aux = vetIndices[0] - tamMaxMolde ) < 0 ) vet[0] = 0;
            else vet[0] = aux;
            if( ( aux = vetIndices[0] - tamMinMolde ) >= column ) vet[1] = column - 1;
            else vet[1] = aux;
            fronteira.push_back( vet );
            for( j = 1; j < tam_indices; ++j )
                if( ( aux = vetIndices[j] - tamMaxMolde ) <= fronteira[tam_fronteira = fronteira.size()-1][1] + 1 )
                    if( ( aux = vetIndices[j] - tamMinMolde ) >= column ) fronteira[tam_fronteira][1] = column - 1;
                    else fronteira[tam_fronteira][1] = aux;
                else
                {
                    vet[0] = aux;
                    if( ( aux = vetIndices[j] - tamMinMolde ) >= column ) vet[1] = column - 1;
                    else vet[1] = aux;
                    fronteira.push_back( vet );
                }

            tam_fronteira = fronteira.size();
            for( k = 0; k < tam_fronteira; ++k )
            {
                lim_fronteira = fronteira[k][1];
                for( j = fronteira[k][0]; j <= lim_fronteira; ++j )
                    if( ( frases_ijReal = corpus.pegarValor(i,j,atributo) ) == corpus.pegarValor(i,j,qtdAtributos-1) )
                        for( L = 0; L < numMoldeRegras; ++L )
                        {
                            moldeInvalido = false;

                            itMolde_end = moldeRegras[L].end();
                            for( itMolde = moldeRegras[L].begin(); itMolde != itMolde_end; ++itMolde )
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
                                for( bp = ret.first; bp != bp_end; ++bp )
                                    if( bp->second.resp != frases_ijReal )
                                        --bp->second.bad;
                            }
                            var.clear();
                        }
                    else
                        for( L = 0; L < numMoldeRegras; ++L )
                        {
                            moldeInvalido = false;

                            itMolde_end = moldeRegras[L].end();
                            for( itMolde = moldeRegras[L].begin(); itMolde != itMolde_end; ++itMolde )
                            {
                                if( ( aux = j - k + itMolde->first ) >= column || aux < 0 )
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
                                for( bp = ret.first; bp != bp_end; ++bp )
                                    if( bp->second.resp == frases_ijReal )
                                        --bp->second.good;
                            }
                            var.clear();
                        }
            }

            for( j = 0; j < tam_indices; ++j )
                corpus.ajustarValor(i,vetIndices[j],qtdAtributos - 1,maxIndice->second.resp);

            for( k = 0; k < tam_fronteira; ++k )
            {
                lim_fronteira = fronteira[k][1];
                for( j = fronteira[k][0]; j <= lim_fronteira; ++j )
                    if( ( frases_ijReal = corpus.pegarValor(i,j,atributo) ) != corpus.pegarValor(i,j,qtdAtributos-1) )
                        for( L = 0; L < numMoldeRegras; ++L ) //aplicar molde de regras na vizinhança da palavra alterada
                        {
                            moldeInvalido = false;

                            itMolde_end = moldeRegras[L].end();
                            for( itMolde = moldeRegras[L].begin(); itMolde != itMolde_end; ++itMolde )
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
                                for( bp = ret.first; bp != bp_end; ++bp )
                                    if( bp->second.resp == frases_ijReal )
                                    {
                                        ++bp->second.good;
                                        moldeInvalido = true;
                                        break;
                                    }
                                if( !moldeInvalido )
                                {
                                    aux = regrasArmazenadas.size();
                                    for( M = 0; M < aux; ++M )
                                        if( contemEstrutura( var, regrasArmazenadas[M] ) )
                                        {
                                            moldeInvalido = true;
                                            break;
                                        }
                                    if( !moldeInvalido )
                                    {
                                        ret = regrasTemporarias2.equal_range( var );
                                        bp_end = ret.second;
                                        for( bp = ret.first; bp != bp_end; ++bp )
                                            if( bp->second.resp == frases_ijReal )
                                            {
                                                moldeInvalido = true;
                                                break;
                                            }
                                        if( !moldeInvalido )
                                            regrasTemporarias2.insert( pair< multimap< int, vector< int > >, Regra >( var, Regra( frases_ijReal, 1 ) ) );
                                    }
                                }
                            }
                            var.clear();
                        }
                    else
                        for( L = 0; L < numMoldeRegras; ++L )
                        {
                            moldeInvalido = false;

                            itMolde_end = moldeRegras[L].end();
                            for( itMolde = moldeRegras[L].begin(); itMolde != itMolde_end; ++itMolde )
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
                                for( bp = ret.first; bp != bp_end; ++bp )
                                    if( bp->second.resp != frases_ijReal )
                                        ++bp->second.bad;
                            }
                            var.clear();
                        }
            }
            vetIndices.clear();
            fronteira.clear();
        }

        if( regrasTemporarias2.size() != 0 )
        {
            for( i = 0; i < row; ++i )
            {
                column = corpus.pegarQtdTokens( i );
                for( j = 0; j < column; ++j )
                    if( ( frases_ijReal = corpus.pegarValor(i,j,atributo) ) == corpus.pegarValor(i,j,qtdAtributos-1) )
                        for( L = 0; L < numMoldeRegras; ++L )
                        {
                            moldeInvalido = false;

                            itMolde_end = moldeRegras[L].end();
                            for( itMolde = moldeRegras[L].begin(); itMolde != itMolde_end; ++itMolde )
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
                                ret = regrasTemporarias2.equal_range( var );
                                bp_end = ret.second;
                                for( bp = ret.first; bp != bp_end; ++bp )
                                    if( bp->second.resp != frases_ijReal )
                                        ++bp->second.bad;
                            }
                            var.clear();
                        }
                    else
                        for( L = 0; L < numMoldeRegras; ++L )
                        {
                            moldeInvalido = false;

                            itMolde_end = moldeRegras[L].end();
                            for( itMolde = moldeRegras[L].begin(); itMolde != itMolde_end; ++itMolde )
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
                                ret = regrasTemporarias2.equal_range( var );
                                bp_end = ret.second;
                                for( bp = ret.first; bp != bp_end; ++bp )
                                    if( bp->second.resp == frases_ijReal )
                                        ++bp->second.good;
                            }
                            var.clear();
                        }
            }

            regrasTemporarias.insert( regrasTemporarias2.begin(), regrasTemporarias2.end() );
            regrasTemporarias2.clear();
        }

        cout << "numRegras: " << regrasTemporarias.size() << endl;

        //remover regras cuja estrutura contem a estrutura da melhor regra
        bp = regrasTemporarias.begin();
        while( bp != regrasTemporarias.end() )
            if( bp->second.good == 0 || contemEstrutura( bp->first, bestEstrutura ) )
                regrasTemporarias.erase( bp++ );
            else ++bp;

        cout << "numRegras: " << regrasTemporarias.size() << endl;

        maxScore = -999999999;
        bp_end = regrasTemporarias.end();
        for( bp = regrasTemporarias.begin(); bp != bp_end; ++bp )
            if( ( aux = bp->second.good - bp->second.bad ) > maxScore )
            {
                maxScore = aux;
                maxIndice = bp;
            }
        //impressão da melhor regra
        cout << "maxScore: " << maxScore << endl;
        bestEstrutura = maxIndice->first;
        linha_end = bestEstrutura.end();
        for( linha = bestEstrutura.begin(); linha != linha_end; ++linha )
            cout << corpus.pegarAtributo(linha->second[0]) << ' ' << linha->first << ' ' << corpus.pegarSimbolo(linha->second[1]) << ' ';
        cout << "=>" << ' ' << corpus.pegarSimbolo(maxIndice->second.resp) << endl;
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
