#include "validadorkdobras_deslizante.h"
#include "../corpus/corpusmatriz.h"

ValidadorKFoldDeslizante::ValidadorKFoldDeslizante( Avaliador &avaliador, int dobras ) :
Validador( avaliador, dobras )
{
    srand( time( NULL ) );
}

ValidadorKFoldDeslizante::~ValidadorKFoldDeslizante()
{
    //dtor
}

vector< vector< float > > ValidadorKFoldDeslizante::executarExperimento22(Classificador *classificador,
                                                                         Corpus &corpus,
                                                                         int atributoTreino,
                                                                         int atributoTeste,
                                                                         int tam_janela_deslizante) {
    //Classificador *classificador;
    int i, j, qtd_linhas = corpus.pegarQtdSentencas();
    vector< vector< float > > resultado;
    vector< Corpus* > vetCorpus;
    vector< int > vetMascara(qtd_linhas);
    int tam_dobra, iniciotreino, fimtreino, inicioteste, fimteste;

    /* criando uma dobra por registro, ignorando dobras do construtor */
    numeroIteracoes = corpus.pegarQtdSentencas() - tam_janela_deslizante;
    //numeroIteracoes = tam_janela_deslizante;

    tam_dobra = 1;

    //ATENÇÃO: numeroIteracoes=dobras
    iniciotreino = 0;
    for (i=0; i<numeroIteracoes; i++){

        iniciotreino = i;
        fimtreino = i + tam_janela_deslizante - 1;
        inicioteste = fimtreino + 1;
        fimteste = inicioteste;

        for( j = 0; j < qtd_linhas; ++j )
        {
            if ((j >= iniciotreino) && (j<=fimtreino)) {
                vetMascara[j] = 0;} //treina com k blocos
            else if ((j >= inicioteste) && (j<=fimteste)) {
                vetMascara[j] = 1;} //classifica com k+1 bloco
            else {
                vetMascara[j] = 2;} //ignora outros
        }

        vetCorpus = corpus.splitCorpus(vetMascara, 3); //intCorpus = 3 (treino, teste, outros_ignorar)

        //classificador = treinador.executarTreinamento( *vetCorpus[0], atributoTreino );
        classificador->executarClassificacao( *vetCorpus[1], atributoTeste );



        //resultado.push_back( avaliador->calcularDesempenho( *vetCorpus[1], atributoTreino, atributoTeste ) );

        int iConsiderar = corpus.pegarPosAtributo("considerar");
        resultado.push_back( avaliador->calcularDesempenho2( *vetCorpus[1], atributoTreino, atributoTeste, iConsiderar ) );


        delete vetCorpus[0];
        delete vetCorpus[1];
        delete vetCorpus[2];



    }

    return resultado;
}



vector< vector< float > > ValidadorKFoldDeslizante::executarExperimento( Treinador &treinador,
                                                                         Corpus &corpus,
                                                                         int atributoTreino,
                                                                         int atributoTeste ) {
    Classificador *classificador;
    int i, j, qtd_linhas = corpus.pegarQtdSentencas();
    vector< vector< float > > resultado;
    vector< Corpus* > vetCorpus;
    vector< int > vetMascara(qtd_linhas);
    int sobra_dobras, tam_dobra, tam_janela_deslizante, iniciotreino, fimtreino, inicioteste, fimteste;

    tam_janela_deslizante = 3; //quantidade maxima de blocos a serem usados no processo formando a janela deslizante

    if (tam_janela_deslizante >= numeroIteracoes){
        ostringstream erro;
        erro << "Erro: janela deslizante nao pode ser maior ou igual ao numero de blocos!\n ( "
         "janela: " << tam_janela_deslizante << " blocos: " << numeroIteracoes << " )!";
        throw erro.str();
    }

    tam_dobra = (qtd_linhas/numeroIteracoes);
    sobra_dobras = (qtd_linhas%numeroIteracoes);

    //ATENÇÃO: numeroIteracoes=dobras
    iniciotreino = 0;
    for (i=1; i<numeroIteracoes; i++){
        if (i>tam_janela_deslizante){
            iniciotreino+=tam_dobra; //marca onde comeca a contagem para treino e teste
        }
        fimtreino = (i * tam_dobra) - 1;
        inicioteste = fimtreino + 1;
        fimteste = inicioteste + tam_dobra-1;
        if (i == (numeroIteracoes - 1)) {
            fimteste += sobra_dobras;
        }

        for( j = 0; j < qtd_linhas; ++j )
        {
            if ((j >= iniciotreino) && (j<=fimtreino)) {
                vetMascara[j] = 0;} //treina com k blocos
            else if ((j >= inicioteste) && (j<=fimteste)) {
                vetMascara[j] = 1;} //classifica com k+1 bloco
            else {
                vetMascara[j] = 2;} //ignora outros
        }

        vetCorpus = corpus.splitCorpus(vetMascara, 3); //intCorpus = 3 (treino, teste, outros_ignorar)

        //int saidacorpus;
        /*
        Corpus* corpusTesteZero = vetCorpus[0];
        Corpus* corpusTesteUm = vetCorpus[1];
        Corpus* corpusTesteDois = vetCorpus[2];

        std::stringstream out0, out1, out2;
        out0 << "../outputs/#corpus0_iteracao" << i << ".txt";
        corpusTesteZero->gravarArquivo(out0.str());
        out0.clear();

        out1 << "../outputs/#corpus1_iteracao" << i << ".txt";
        corpusTesteUm->gravarArquivo(out1.str());
        out1.clear();

        out2 << "../outputs/#corpus2_iteracao" << i << ".txt";
        corpusTesteDois->gravarArquivo(out2.str());
        out2.clear();
        */


        classificador = treinador.executarTreinamento( *vetCorpus[0], atributoTreino );
        classificador->executarClassificacao( *vetCorpus[1], atributoTeste );
        resultado.push_back( avaliador->calcularDesempenho( *vetCorpus[1], atributoTreino, atributoTeste ) );

        //teste , retirar isto!!!!!!!
        //somente para validar métodos de treino e classificacao independente da validacao cruzada
        //classificador = treinador.executarTreinamento( corpus, atributoTreino );
        //classificador->executarClassificacao( corpus, atributoTeste );
        //resultado.push_back( avaliador->calcularDesempenho( corpus, atributoTreino, atributoTeste ) );

        delete vetCorpus[0];
        delete vetCorpus[1];
        delete vetCorpus[2];

        delete classificador;

    }

    return resultado;
}

vector< vector< float > > ValidadorKFoldDeslizante::executarExperimento2(Treinador &treinador,
                                                                         Corpus &corpus,
                                                                         int atributoTreino,
                                                                         int atributoTeste,
                                                                         int tam_janela_deslizante) {
    Classificador *classificador;
    int i, j, qtd_linhas = corpus.pegarQtdSentencas();
    vector< vector< float > > resultado;
    vector< Corpus* > vetCorpus;
    vector< int > vetMascara(qtd_linhas);
    int tam_dobra, iniciotreino, fimtreino, inicioteste, fimteste;

    /* criando uma dobra por registro, ignorando dobras do construtor */
    numeroIteracoes = corpus.pegarQtdSentencas() - tam_janela_deslizante;
    //numeroIteracoes = tam_janela_deslizante;

    tam_dobra = 1;

    //ATENÇÃO: numeroIteracoes=dobras
    iniciotreino = 0;
    for (i=0; i<numeroIteracoes; i++){

        iniciotreino = i;
        fimtreino = i + tam_janela_deslizante - 1;
        inicioteste = fimtreino + 1;
        fimteste = inicioteste;

        for( j = 0; j < qtd_linhas; ++j )
        {
            if ((j >= iniciotreino) && (j<=fimtreino)) {
                vetMascara[j] = 0;} //treina com k blocos
            else if ((j >= inicioteste) && (j<=fimteste)) {
                vetMascara[j] = 1;} //classifica com k+1 bloco
            else {
                vetMascara[j] = 2;} //ignora outros
        }

        vetCorpus = corpus.splitCorpus(vetMascara, 3); //intCorpus = 3 (treino, teste, outros_ignorar)

        classificador = treinador.executarTreinamento( *vetCorpus[0], atributoTreino );
        classificador->executarClassificacao( *vetCorpus[1], atributoTeste );
        resultado.push_back( avaliador->calcularDesempenho( *vetCorpus[1], atributoTreino, atributoTeste ) );


        delete vetCorpus[0];
        delete vetCorpus[1];
        delete vetCorpus[2];

        delete classificador;

    }

    return resultado;
}

vector< vector< float > > ValidadorKFoldDeslizante::executarExperimento3( Treinador &treinador,
                                                                         Corpus &corpus,
                                                                         int atributoTreino,
                                                                         int atributoTeste,
                                                                         int tam_treino) {
    Classificador *classificador;
    int j, qtd_linhas = corpus.pegarQtdSentencas();
    vector< vector< float > > resultado;
    vector< Corpus* > vetCorpus;
    vector< int > vetMascara(qtd_linhas);
    int iniciotreino, fimtreino, inicioteste, fimteste;

    iniciotreino = 0;
    fimtreino = tam_treino - 1;
    inicioteste = fimtreino + 1;
    fimteste = corpus.pegarQtdSentencas() - 1;

    for( j = 0; j < qtd_linhas; ++j )
    {
        if ((j >= iniciotreino) && (j<=fimtreino)) {
            vetMascara[j] = 0;} //treina com k blocos
        else if ((j >= inicioteste) && (j<=fimteste)) {
            vetMascara[j] = 1;} //classifica com k+1 bloco
    }

    vetCorpus = corpus.splitCorpus(vetMascara, 2); //intCorpus = 2 (treino, teste)

    classificador = treinador.executarTreinamento( *vetCorpus[0], atributoTreino );
    classificador->executarClassificacao( *vetCorpus[1], atributoTeste );
    resultado.push_back( avaliador->calcularDesempenho( *vetCorpus[1], atributoTreino, atributoTeste ) );


    delete vetCorpus[0];
    delete vetCorpus[1];

    delete classificador;

    return resultado;
}
