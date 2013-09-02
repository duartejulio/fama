/*
 * File:   treinadorRNSP.cpp
 * Autores: Anderson Crivela e Alberto Angonese
 *
 * Created on August 14, 2013, 12:04 AM
 */
#include "treinadorRNSP.h"
#include <math.h>
#include <ostream>
#include <iostream>
#include <sys/time.h>
//#include "../outros/barraprogresso.h"

template <typename T>  string NumberToString ( T Number ) {
     ostringstream ss;
     ss << Number;
     return ss.str();
}

template <typename T> T StringToNumber (const string &Text) {
     istringstream ss(Text);
     T result;
     return ss >> result ? result : 0;
}

TreinadorRNSP::TreinadorRNSP(int totalbits, int classes, int bits_enderecamento, int repeticoes) {
    this->totalBitsRam = totalbits;
    this->classes = classes;
    this->bits_enderecamento = bits_enderecamento;
    this->repeticoes = repeticoes;
    this->rams = totalbits/bits_enderecamento;
    this->tamanhoRam = pow(2,bits_enderecamento);

    //Alocando memória para os vetores
    distribuidos.resize(totalBitsRam);

    distribuicao_bits.resize(this->rams);
    for (register int i = 0; i < this->rams; ++i) {
        distribuicao_bits[i].resize(this->bits_enderecamento);
    }

    discriminadores.resize(this->classes);
    for (register int i = 0; i < this->classes; ++i) {
        this->discriminadores[i].resize(this->rams);
        for (register int j = 0; j < this->rams; ++j) {
            this->discriminadores[i][j].resize(this->tamanhoRam);
        }
    }
    //Fim alocacao
}

TreinadorRNSP::~TreinadorRNSP() {

}

/* Executa o treinamento de redes neurais sem peso */
Classificador *TreinadorRNSP::executarTreinamento( Corpus &corpus, int atributo ) {

    const char* SPACE = " ";

    int repeticao, h, i, j, m, n, posicao;
    ostringstream saida;

    cout << "Iniciando o treinamento..." << endl;

    for (repeticao = 0; repeticao < this->repeticoes; repeticao++){

        distribuirBitsAleatoriamente();

        for (h = 1; h <= this->rams; h++){

            //Zerando a matriz dos discriminadores
            limparDiscriminadores();

            //Preenchendo as RAMS
            int c,e,classe;
            string binario;
            for (c = 0; c < corpus.pegarQtdConjExemplos(); c++){
                for (e = 0; e < corpus.pegarQtdExemplos(c); e++){
                    //binario = corpus(c,e,atributo);
                   //classe = StringToNumber<int>(corpus(c,e,atributo+1));
                   binario = corpus(c,e,0);
                   classe = StringToNumber<int>(corpus(c,e,atributo));

                    //Faz o treinamento pada cada padrão da classe
                    for (m = 0; m < h; m++){
                        posicao = 0;
                        for (n = 0; n < this->bits_enderecamento; n++) {
                            binario[distribuicao_bits[m][n]] == '1' ? posicao += pow(2, this->bits_enderecamento - n - 1) : 0;
                        }
                        discriminadores[classe][m][posicao] += 1;
                    }
                }
            }

             //Gravando parâmetros gerais do treinamento
             saida << this->classes << SPACE;
             saida << this->totalBitsRam << SPACE;
             saida << h << SPACE;
             saida << this->bits_enderecamento << SPACE;
             saida << this->tamanhoRam << SPACE;
             saida << repeticao+1 << SPACE;

             //Gravando a distribuição
             for (i = 0; i < h; i++){
                 for (j = 0; j < this->bits_enderecamento; j++){
                     saida << distribuicao_bits[i][j] << SPACE;
                 }
             }
             //Gravando as RAMS
             for (i = 0; i < this->classes; i++){
                 for (j = 0; j < h; j++){
                     for (m = 0; m < this->tamanhoRam; m++){
                         saida << discriminadores[i][j][m] << SPACE;
                     }
                 }
             }
             saida << endl;
         }
      //  loadbar(repeticao+1, this->repeticoes, 50);
     }

    ClassificadorRNSP *cl;
    cl = new ClassificadorRNSP(this->classes);
    cl->conhecimento = saida.str();

    cout << endl << "Treinamento finalizado..." << endl;

    return cl;
}

/* Faz a distribuicao aleatoria de bits conforme a quantidade de
 * bits de endereçamento.  */
void TreinadorRNSP::distribuirBitsAleatoriamente() {

    int aux;

    for (register int i = 0; i < this->totalBitsRam; i++){
        distribuidos[i] = 0;
    }

    timeval t1;
    gettimeofday(&t1, NULL);
    srand(t1.tv_usec * t1.tv_sec);
    for (register int i = 0; i < this->rams; i++){
        for (register int j = 0; j < this->bits_enderecamento; j++){
            aux = rand() % this->totalBitsRam;
            this->distribuicao_bits[i][j] = aux;
            this->distribuidos[aux] == 1 ? j--: distribuidos[aux] = 1;
        }
    }
}

/* Zera a todos os discriminadores  */
void TreinadorRNSP::limparDiscriminadores() {
    for (register int i = 0; i < this->classes; i++){
        for (register int j = 0; j < this->rams; j++){
            for (register int m = 0; m < this->tamanhoRam; m++){
                this->discriminadores[i][j][m] = 0;
            }
        }
    }
}

