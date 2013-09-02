/*
 * File:   treinadorRNSP.h
 * Autores: Anderson Crivela e Alberto Angonese
 *
 * Created on August 14, 2013, 12:04 AM
 */

#ifndef TREINADORRNSP_H
#define	TREINADORRNSP_H

#include "treinador.h"
#include "../classificador/classificadorRNSP.h"

class TreinadorRNSP : public Treinador
{
    private:
        int classes;
        int rams;
        int bits_enderecamento;
        int tamanhoRam;
        int totalBitsRam;
        int repeticoes;
        void distribuirBitsAleatoriamente();
        void limparDiscriminadores();

    public:
        vector< vector <vector<int> > > discriminadores;
        vector< vector<int> > distribuicao_bits;
        vector<int> distribuidos;
        TreinadorRNSP(int totalbits, int classes, int bits_enderecamento, int repeticoes);
        virtual ~TreinadorRNSP();
        virtual Classificador *executarTreinamento( Corpus &corpus, int atributo );
};

#endif	/* TREINADORRNSP_H */
