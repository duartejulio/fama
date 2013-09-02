/*
 * File:   main.cpp
 * Autores: Anderson Crivela e Alberto Angonese
 *
 * Created on August 14, 2013, 12:04 AM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>

#include "../corpus/corpusmatriz.h"
#include "../treinador/treinadorRNSP.h"
#include "../classificador/classificador.h"
#include "../classificador/classificadorRNSP.h"
#include "../avaliador/avaliador_acuracia.h"
#include "../validador/validadorkdobras.h"

using namespace std;

static void executarRedeNeural(string arquivoTreinamento, string arquivoValidacao, int totalbits, int repeticoes) {

    const int classes = 8;
    const int bits = 3;

    vector<string> atributos;
    atributos.push_back("binario");
    atributos.push_back("classe");

    int atributo;
    Classificador *cl,*cl2;

    //carrega conjunto de dados
    CorpusMatriz objCorpus(atributos, ',', true, true);
    objCorpus.carregarArquivo(arquivoTreinamento);

    //atributo = objCorpus.pegarPosAtributo("binario");
    atributo = objCorpus.pegarPosAtributo("classe");

    //treinamento
    TreinadorRNSP rnsp(totalbits,classes,bits,repeticoes);
    cl = rnsp.executarTreinamento(objCorpus, atributo);
    cl->gravarConhecimento("../inputs/treinamento.txt");

    int qtdeExemplos = 10;
    cl2 = new ClassificadorRNSP(classes, qtdeExemplos);
    cl2->carregarConhecimento("../inputs/treinamento.txt");

    CorpusMatriz objCorpusProva(atributos, ',', true, true);
    objCorpusProva.carregarArquivo(arquivoValidacao);

    int novoatributo = objCorpusProva.criarAtributo("rnsp");
    cl2->executarClassificacao(objCorpusProva, novoatributo);

}

int main() {

    int opcao;
    bool ativo = true;
    string arquivoTreinamento, arquivoValidacao;

    int totalbits;
    int repeticoes = 10;

    while (ativo != false) {
        cout << "**************************************************************************\n";
        cout << "*** IDENTIFICADOR DE EMOCOES BASEADO EM EXPRESSOES FACIAIS UTILIZANDO  ***\n";
        cout << "***                    REDE NEURAL SEM PESOS                           ***\n";
        cout << "***          (8 DISCRIMINADORES E 3 BITS DE ENDERECAMENTO)             ***\n";
        cout << "**************************************************************************\n";
        cout << " 1 - Boca (50 bits)\n";
        cout << " 2 - Boca (200 bits)\n";
        cout << " 3 - Boca (800 bits).\n";
        cout << " 4 - Olho direito (64 bits)\n";
        cout << " 5 - Olho direito (400 bits)\n";
        cout << " 6 - Olho direito  (1600 bits).\n";
        cout << " 7 - Nariz (48 bits)\n";
        cout << " 8 - Nariz (192 bits)\n";
        cout << " 9 - Nariz (768 bits).\n";
        cout << " 0 - Sair.\n";
        cout << "**************************************************************************\n";
        cout << " Entre com a opcao desejada: ";

        cin >> opcao;

        switch (opcao) {
            case 1:
                totalbits = 50;
                arquivoTreinamento = "../inputs/treinamento_boca_50_bits.txt";
                arquivoValidacao = "../inputs/validacao_boca_50_bits.txt";
                cout << " Entre com o numero de repeticoes: ";
                cin >> repeticoes;
                executarRedeNeural(arquivoTreinamento, arquivoValidacao, totalbits, repeticoes);
                //repeticoes = 10;
                break;
            case 2:
                totalbits = 200;
                arquivoTreinamento = "../inputs/treinamento_boca_200_bits.txt";
                arquivoValidacao = "../inputs/validacao_boca_200_bits.txt";
                cout << "Entre com o numero de repeticoes: ";
                cin >> repeticoes;
                executarRedeNeural(arquivoTreinamento, arquivoValidacao, totalbits, repeticoes);
                //repeticoes = 10;
                break;
            case 3:
                totalbits = 800;
                arquivoTreinamento = "../inputs/treinamento_boca_800_bits.txt";
                arquivoValidacao = "../inputs/validacao_boca_800_bits.txt";
                cout << " Entre com o numero de repeticoes: ";
                cin >> repeticoes;
                executarRedeNeural(arquivoTreinamento, arquivoValidacao, totalbits, repeticoes);
                //repeticoes = 10;
                break;
            case 4:
                totalbits = 64;
                arquivoTreinamento = "../inputs/treinamento_olho_direito_64_bits.txt";
                arquivoValidacao = "../inputs/validacao_olho_direito_64_bits.txt";
                cout << "Entre com o numero de repeticoes: ";
                cin >> repeticoes;
                executarRedeNeural(arquivoTreinamento, arquivoValidacao, totalbits, repeticoes);
                //repeticoes = 10;
                break;
            case 5:
                totalbits = 400;
                arquivoTreinamento = "../inputs/treinamento_olho_direito_400_bits.txt";
                arquivoValidacao = "../inputs/validacao_olho_direito_400_bits.txt";
                cout << " Entre com o numero de repeticoes: ";
                cin >> repeticoes;
                executarRedeNeural(arquivoTreinamento, arquivoValidacao, totalbits, repeticoes);
                //repeticoes = 10;
                break;
            case 6:
                totalbits = 1600;
                arquivoTreinamento = "../inputs/treinamento_olho_direito_1600_bits.txt";
                arquivoValidacao = "../inputs/validacao_olho_direito_1600_bits.txt";
                cout << "Entre com o numero de repeticoes: ";
                cin >> repeticoes;
                executarRedeNeural(arquivoTreinamento, arquivoValidacao, totalbits, repeticoes);
                //repeticoes = 10;
                break;
            case 7:
                totalbits = 48;
                arquivoTreinamento = "../inputs/treinamento_nariz_48_bits.txt";
                arquivoValidacao = "../inputs/validacao_nariz_48_bits.txt";
                cout << "Entre com o numero de repeticoes: ";
                cin >> repeticoes;
                executarRedeNeural(arquivoTreinamento, arquivoValidacao, totalbits, repeticoes);
                //repeticoes = 10;
                break;
            case 8:
                totalbits = 192;
                arquivoTreinamento = "../inputs/treinamento_nariz_192_bits.txt";
                arquivoValidacao = "../inputs/validacao_nariz_192_bits.txt";
                cout << "Entre com o numero de repeticoes: ";
                cin >> repeticoes;
                executarRedeNeural(arquivoTreinamento, arquivoValidacao, totalbits, repeticoes);
                //repeticoes = 10;
                break;
            case 9:
                totalbits = 768;
                arquivoTreinamento = "../inputs/treinamento_nariz_768_bits.txt";
                arquivoValidacao = "../inputs/validacao_nariz_768_bits.txt";
                cout << " Entre com o numero de repeticoes: ";
                cin >> repeticoes;
                executarRedeNeural(arquivoTreinamento, arquivoValidacao, totalbits, repeticoes);
                //repeticoes = 10;
                break;
            case 0:
                cout << "Fim.\n";
                ativo = false;
                break;
            default:
                cout << "Opcao invalida. \n";
                cout << "Escolha novamente.\n";
                cin >> opcao;
                break;
        }
    }

    return 0;
}


