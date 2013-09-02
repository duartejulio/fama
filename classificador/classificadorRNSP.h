/*
 * File:   classificadorRNSP.h
 * Autores: Anderson Crivela e Alberto Angonese
 *
 * Created on August 14, 2013, 12:04 AM
 */

#ifndef CLASSIFICADORRNSP_H
#define	CLASSIFICADORRNSP_H

#include "classificador.h"
#include <fstream>

class ClassificadorRNSP : public Classificador {
public:
    ClassificadorRNSP(int classes, int qtdExemplos);
    ClassificadorRNSP(int classes);
    virtual ~ClassificadorRNSP();
    virtual bool executarClassificacao( Corpus &corpusProva, int atributo );
    virtual bool gravarConhecimento( string arquivo );
    virtual bool carregarConhecimento( string arquivo );
    const char* TAB;

private:
    vector< vector<int> > matriz_confusao;
    vector<int> validacao;
    struct RedeNeural {
        int classes;
        int rams;
        int bits_enderecamento;
        int tamanhoRam;
        int totalBitsRam;
        int repeticoes;
        int repeticao;
        vector< vector<int> > distribuicao_bits;
        vector< vector< vector<int> > > discriminadores;
    };
    vector< vector<int> > maiorMatriz;
    vector<RedeNeural> redes;
    int classes, rams, qtdeExemplos, maiorRepeticao;
    double maiorAcerto;
    string conhecimento;

    void limparMatrizConfusao(int classes);
    void imprimirResultado();

    friend class TreinadorRNSP;

};

#endif	/* CLASSIFICADORRNSP_H */

