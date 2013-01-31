#include <cmath>
#include <sstream>
#include <string.h>
#include "libsvm.h"
#include "../libsvm/svm.h"
//#include "../libsvm/libsvm.dll"
//#import "../libsvm/libsvm.dll" no_namespace rename("EOF", "EndOfFile")

LibSvm::LibSvm(vector<string> atr, vector<string> cla, string valord, struct svm_parameter par):Treinador(){
    atributos = atr;
    classes = cla;
    valor_dia = valord;
    param = par;
}



void LibSvm::atualizarValorD(string valor) {
     valor_dia = valor;
}

void LibSvm::atualizarAtributosTreino(vector<string> atr) {
     atributos = atr;
}

Classificador* LibSvm::executarTreinamento( Corpus &corpus, int atributo ){

	unsigned int nExemplos, nConjExemplos, nAtributos, e, c;
    char model_file_name[1024]; //nome do arquivo de modelo
    int nTotalExemplos;
    struct svm_model *model; //modelo

    //determina números de conjuntos de exemplos e atributos do corpus
    nConjExemplos = corpus.pegarQtdConjExemplos();
    nAtributos = atributos.size();
    nTotalExemplos = 0;

    //obtendo o total de registros geral
    for (c=0; c < nConjExemplos; c++){
        nExemplos = corpus.pegarQtdExemplos(c);
        for (e=0; e < nExemplos; e++){
            nTotalExemplos += 1;
        }
    }

/******************************************************************************************************************
Integração com LibSvm: Verificando Parâmetros e Passando da classe Corpus para a estrutura svm_problem
******************************************************************************************************************/
    //aplicar regras de negocio aqui depois para validar os parametros.
    if (!verificarParametros(param)) {
        //gerar exceção e exibir mensagem, caso erro
    }
    // gerando a classe problema do libsvm a partir do corpus
    struct svm_problem problema;

    if (gerarClasseProblemaSvm(corpus, atributo, nTotalExemplos, nAtributos, nConjExemplos, problema)) {

         // setando nome do arquivo de modelo a ser gravado
         strcpy(model_file_name, "out_model_svm.model");

         //treinando com os parametros para gerar o modelo
         model = svm_train(&problema, &param);

         // gerando arquivo de modelo do libsvm
         svm_save_model(model_file_name,model);
    }

    return new ClassificadorLibSvm(classes, atributos, problema, model, valor_dia);



}

bool LibSvm::verificarParametros(svm_parameter param) {

    return true;

}

bool LibSvm::gerarClasseProblemaSvm(Corpus &corpus,
                                            int atributo,
                                            int nTotalExemplos,
                                            unsigned int nAtributos,
                                            unsigned int nConjExemplos,
                                            struct svm_problem &prob) {


    struct svm_node *x_node; //nó atributos
    //struct svm_problem prob; //problema (corpus)
    unsigned int nExemplos, i, a, e, c, v, iregistro, iValorDia ;

    float val;

    prob.l = nTotalExemplos; //total de exemplos no geral
    prob.y = new double[nTotalExemplos]; //vetor de resposta
    prob.x = new struct svm_node* [nTotalExemplos]();


    iregistro = 0;

    //a transformacao no svm_problem se dá a partir de um corpus, que pode ter mais de um conjunto de exemplos
    for (c=0; c < nConjExemplos; c++){
        nExemplos = corpus.pegarQtdExemplos(c);
        for (e=0; e < nExemplos; e++){
            v = corpus.pegarValor(c, e, atributo);
            (std::istringstream)(corpus.pegarSimbolo(v)) >> val >> std::dec;
            prob.y[iregistro] = val;

            //alocando vetor de atributos (total att + y + finalizador svm_node) = maximo
            x_node = new struct svm_node[nAtributos + 1 + 1];

            int aux_a = 0;
            prob.x[iregistro] = x_node;

            //o primeiro valor do nó svm_node = valor do dia
            iValorDia = corpus.pegarPosAtributo(valor_dia);
            v = corpus.pegarValor(c, e, iValorDia);
            (std::istringstream)(corpus.pegarSimbolo(v)) >> val >> std::dec;
            x_node[0].index = 1;
            x_node[0].value = val;
            aux_a += 1;

            // próximos valores do nó svm_node = diferenças
            for (a=0; a<nAtributos;a++){
                i = corpus.pegarPosAtributo(atributos[a]);
                v = corpus.pegarValor(c, e, i);
                (std::istringstream)(corpus.pegarSimbolo(v)) >> val >> std::dec;
                if (val != 0.0) {
                    x_node[aux_a].index = (a + 2); //1o. é do att valor em D
                    x_node[aux_a].value = val;
                    //add o no com os valores da i-ésima linha de registro
                    //prob.x[iregistro][aux_a] = &x_node[aux_a];

                    aux_a += 1;
                }
            }
            //finalizador
            x_node[aux_a].index = (-1);
            //x_node[aux_a].value = 0.0;

            iregistro += 1; //incrementa o indice do i-ésimo elemento, considerando todos os registros de todos os conjuntos

        }
     }

    //somente para teste. mostrar o conteudo do svm_problem !!!!!!!!!!!!!!!!!!!!!!!1
//     int reg_i, att_i_x;
//     for (reg_i=0; reg_i<prob.l; reg_i++){
//        cout << "registro " << reg_i << "\n";
//        int qtdatt = sizeof(prob.x)/sizeof(int);
//        for (att_i_x=0; att_i_x<(qtdatt); att_i_x++){
//             cout << "    atributo " << att_i_x << " index:=" << prob.x[reg_i][att_i_x].index << " value:=" << prob.x[reg_i][att_i_x].value << "\n";
//        }
//     }


    return true;


}
