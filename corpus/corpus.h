#ifndef CORPUS_H
#define CORPUS_H

#include <iostream>
#include <vector>
#include <map>
#include <cstdio>
#include <cstdlib>

using namespace std;

class Corpus
{
    public:
        Corpus( vector<string> atributos = vector<string>() );
        virtual ~Corpus();
        virtual bool carregarArquivo( string arquivo ) = 0;
        virtual bool gravarArquivo( string arquivo ) = 0;
        virtual Corpus* clone() = 0;
        string pegarSimbolo( int indice );
        int pegarIndice( string simbolo );
        int criarAtributo( string atributo, string valorAtributo = "O");
        int pegarValor( int sentenca, int token, int atributo );
        int pegarQtdSentencas();
        int pegarQtdConjExemplos(){return pegarQtdSentencas();}
        int pegarQtdAtributos();
        int pegarQtdTokens( int i );
        int pegarQtdExemplos(int i){return pegarQtdTokens(i);}
        int pegarQtdSimbolos();
        bool ajustarValor( int sentenca, int token, int atributo, int valor );
        string pegarAtributo( int indice );
        int pegarPosAtributo( string atributo );
        vector<string> pegarAtributos();
        vector< Corpus* > splitCorpus( vector< bool > vetMascara );
    protected:
        map<string,int> posAtributos;
        vector<string> atributos;
        vector<string> simbolos;
        vector< vector< vector<int> > > frases;
        map<string,int> dicionario;
        int qtd_sentencas;
        int qtd_atributos;
        int qtd_simbolos;
};

#endif // CORPUS_H
