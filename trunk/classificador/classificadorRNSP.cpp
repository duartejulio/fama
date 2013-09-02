/*
 * File:   classificadorRNSP.cpp
 * Autores: Anderson Crivela e Alberto Angonese
 *
 * Created on August 14, 2013, 12:04 AM
 */

#include "classificadorRNSP.h"
//#include "../outros/barraprogresso.h"
#include <math.h>
#include <sstream>
#include <iomanip>

template <typename T> T StringToNumber (const string &Text) {
     istringstream ss(Text);
     T result;
     return ss >> result ? result : 0;
}

template <typename T>  string NumberToString ( T Number ) {
     ostringstream ss;
     ss << Number;
     return ss.str();
}

ClassificadorRNSP::ClassificadorRNSP(int classes) {
    this->TAB = "\t";
    this->classes = classes;
    validacao.resize(classes);
    matriz_confusao.resize(classes);
    for (register int i = 0; i < classes; i++)
        matriz_confusao[i].resize(classes);
}

ClassificadorRNSP::ClassificadorRNSP(int classes, int qtdeExemplos) {
    this->TAB = "\t";
    this->classes = classes;
    validacao.resize(classes);
    matriz_confusao.resize(classes);
    for (register int i = 0; i < classes; i++)
        matriz_confusao[i].resize(classes);

    this->qtdeExemplos = qtdeExemplos;
}

void ClassificadorRNSP::limparMatrizConfusao(int classes) {
    for (register int i = 0; i < classes; i++)
        for (register int j = 0; j < classes; j++)
            matriz_confusao[i][j] = 0;
}

ClassificadorRNSP::~ClassificadorRNSP() {
}

bool ClassificadorRNSP::executarClassificacao(Corpus &corpus, int atributo){

    int maior, posicao;
    int i, j, m, n, r, classe;
    int acertos, total_ativados, duplicados;
    ofstream arq_validacao,arq_matriz_confusao;
    string binario;
    this->qtdeExemplos = 10;

    cout << "Realizando classificacao..." << endl;

    //Abrindo arquivo para resumo da validacao
    string nome_arquivo_validacao = "validacao.txt";
    arq_validacao.open(nome_arquivo_validacao.c_str());
    arq_validacao << "n_classes\tn_treinamento\tn_bits\tn_rams\trepticao\tbits_rams\ttamanho_ram\ttotal\tacertos\tduplicados\n";

    string nome_arquivo_matriz_confusao = "matriz_confusao.txt";
    arq_matriz_confusao.open(nome_arquivo_matriz_confusao.c_str());

    int posicaoBinario = corpus.pegarPosAtributo("binario");
    for (unsigned int rede = 0; rede < redes.size(); rede++) {

        limparMatrizConfusao(redes[rede].classes);

        //Efetuando validacao dos padroes:
        acertos = total_ativados = 0;
        for (i = 0; i < redes[rede].classes; i++){
            for (j = 0; j < redes[rede].classes; j++){
                validacao[j] = 0;
            }
            for (j = 0; j < this->qtdeExemplos; j++){
            //for (c = 0; c < corpus.pegarQtdConjExemplos(); c++){
                //for (e = 0; e < corpus.pegarQtdExemplos(c); e++){
                binario = corpus((i*this->qtdeExemplos)+j,0,posicaoBinario);
                classe = StringToNumber<int>(corpus((i*this->qtdeExemplos)+j,0,posicaoBinario+1));
                maior = 0;
                for (m = 0; m < redes[rede].classes; m++){ //para cada discriminador
                    for (n = 0; n < redes[rede].rams; n++){ //para cada ram
                        posicao = 0;
                        for (r = 0; r < redes[rede].bits_enderecamento; r++){//para cada posicao da ram
                            binario[redes[rede].distribuicao_bits[n][r]] == '1' ? posicao += pow(2, redes[rede].bits_enderecamento - r - 1) : 0;
                        }
                        validacao[m] += redes[rede].discriminadores[m][n][posicao];
                    }
                    validacao[m] > maior ? maior = validacao[m] : 0;
                }
                //verificando quais discriminadores foram mais ativados e atualizando matriz de confusão
                for (m = 0; m < redes[rede].classes; m++){
                    if (validacao[m] == maior){
                        matriz_confusao[i][m]++;
                        total_ativados++;
                        if (i == m){
                            acertos++;
                        }
                    }
                }
                //corpus((i*this->qtdeExemplos)+j,0,2,"0");
            }
        }

        //Gravando matriz de confusão
        arq_matriz_confusao << "Matriz: " << redes[rede].rams << " - Repeticao: " << redes[rede].repeticao << endl;
        for (i = 0; i < redes[rede].classes; i++){
            for (j = 0; j < redes[rede].classes; j++){
                arq_matriz_confusao << matriz_confusao[i][j] << TAB;
            }
            arq_matriz_confusao << endl;
        }
        arq_matriz_confusao << endl;

        //Gravando linha no arquivo de resumo da validacao:
        arq_validacao << redes[rede].classes << TAB;
        arq_validacao << redes[rede].totalBitsRam << TAB;
        arq_validacao << redes[rede].rams << TAB;
        arq_validacao << redes[rede].repeticao << TAB;
        arq_validacao << redes[rede].bits_enderecamento << TAB;
        arq_validacao << redes[rede].tamanhoRam << TAB;
        arq_validacao << redes[rede].classes * this->qtdeExemplos << TAB;
        arq_validacao << acertos << TAB;

        duplicados = total_ativados - (redes[rede].classes * this->qtdeExemplos);
        arq_validacao << duplicados << TAB;
        arq_validacao << endl;

        if ( (acertos - duplicados) > maiorAcerto ) {
            this->maiorAcerto = acertos;
            this->maiorMatriz = matriz_confusao;
            this->rams = redes[rede].rams;
            this->maiorRepeticao = redes[rede].repeticao;
        }

//        loadbar(rede+1, redes.size(), 50);

    }
    arq_validacao.close();
    arq_matriz_confusao.close();

    imprimirResultado();

    cout << "Classificacao finalizada..." << endl;
    return true;
}

void ClassificadorRNSP::imprimirResultado() {
    string classes[] = {"Raiva","Despre","Nojo","Medo","Felici","Neutro","Triste","Surpr"};
    cout << "-----------------------------------------------------------------------------\n";
    cout << endl << "           Matriz de confusao da melhor configuracao:   " << this->rams << " - " << this->maiorRepeticao << endl;
    cout << "-----------------------------------------------------------------------------\n";
    cout << TAB;
    for (int i = 0; i < this->classes; i++)
        cout << classes[i] << TAB ;
    cout << endl;
    for (int i = 0; i < this->classes; i++) {
        cout << classes[i] << TAB;
        for (int j = 0; j < this->classes; j++) {
            cout << this->maiorMatriz[i][j] << TAB;
        }
        cout << endl;
    }
    cout << "-----------------------------------------------------------------------------\n";
    cout.setf(ios::fixed, ios::floatfield);
    cout.setf(ios::showpoint);
    cout << "Percentual de acertos: " << setprecision(2) <<  (this->maiorAcerto/(this->qtdeExemplos*this->classes))*100 << endl;
    cout << "-----------------------------------------------------------------------------\n";
}

bool ClassificadorRNSP::gravarConhecimento( string arquivo ){

    cout << "Gravando conhecimento..." << endl;

    ofstream out;
    out.open(arquivo.c_str());
    out << conhecimento;
    out.close();

    cout << "Conhecimento gravado..." << endl;

    return true;
}

bool ClassificadorRNSP::carregarConhecimento( string arquivo ){
    ifstream in;
    stringstream buffer;
    string linha;
    RedeNeural rede;

    cout << "Carregando conhecimento..." << endl;

    in.open(arquivo.c_str());
    while (getline(in,linha)) {
        buffer << linha;
        buffer >> rede.classes;
        buffer >> rede.totalBitsRam;
        buffer >> rede.rams;
        buffer >> rede.bits_enderecamento;
        buffer >> rede.tamanhoRam;
        buffer >> rede.repeticao;

        rede.distribuicao_bits.resize(rede.rams);
        for (int i = 0; i < rede.rams; i++){
            rede.distribuicao_bits[i].resize(rede.bits_enderecamento);
            for (int j = 0; j < rede.bits_enderecamento; j++){
                buffer >> rede.distribuicao_bits[i][j];
            }
        }

        rede.discriminadores.resize(rede.classes);
        for (int i = 0; i < rede.classes; i++){
            rede.discriminadores[i].resize(rede.rams);
            for (int j = 0; j < rede.rams; j++){
                rede.discriminadores[i][j].resize(rede.tamanhoRam);
                for (int m = 0; m < rede.tamanhoRam; m++){
                    buffer >> rede.discriminadores[i][j][m];
                }
            }
        }
        redes.push_back(rede);
    }
    in.close();

    cout << "Conhecimento carregado..." << endl;

    return true;
};


