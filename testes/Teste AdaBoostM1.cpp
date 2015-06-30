#include <iostream>
#include <vector>
#include <exception>
#include <iomanip>

#include "classificador/classificador_provavel.h"
#include "corpus/corpusmatriz.h"
#include "treinador/treinador_provavel.h"
#include "validador/validadorkdobras.h"
#include "treinador/treinador_adaboost.h"
#include "treinador/treinador_stump.h"
#include "classificador/classificador_adaboost.h"
#include "avaliador/avaliador_prob.h"
#include "treinador/treinador_stump.h"
#include "classificador/classificador_stump.h"
#include "treinador/treinador_adaboost_m1.h"
#include <set>

using namespace std;

int main()
{
    string entrada1, entrada2;
    char separador;
    vector<string> opcoes;
    vector<string>::iterator it;
    int tab;
    try
    {
        cout << "Primeira implementação do FAMA... Criando corpus.\nDigite o nome do arquivo do corpus: ";
        cin >> entrada1;
        //entrada1 = "malware5.dat";
        cout << "Digite o caracter separador: ";
        cin >> separador;
        CorpusMatriz objCorpus(vector<string>(), separador, true, true);
        objCorpus.carregarArquivo(entrada1.c_str());
        cout << "Corpus criado!\n" << endl;

        opcoes = objCorpus.pegarAtributos();

        cout << "Criar treinador, e pegar posicao que vai ser testada. Possíveis atributos: \n";
        for (it = opcoes.begin(), tab = 0; it != opcoes.end(); ++it, ++tab)
        {
            cout << *it ;
            if (tab % 10 && tab)
                cout << '\t';
            else
                cout << '\n';
        }
        cout << "Opcao: ";
        cin >> entrada2;
        //entrada2 = "Malware";
        int gabarito = objCorpus.pegarPosAtributo(entrada2);
        int minha_resposta = objCorpus.criarAtributo("gabarito", "desconhecido");
        set<string> fora;
        fora.insert("gabarito");
        TreinadorAdaboostM1 treinador(new DecisionStump(NULL, fora), true, 10, "gabarito", "desconhecido");
        //DecisionStump treinador;

        Classificador *objClass;

        cout << "Executando treinamento...\n";
        objClass = treinador.executarTreinamento(objCorpus, gabarito);
        objClass->gravarConhecimento("know.txt");
        cout << "Treinamento executado, agora vamos para a prova.\n" << endl;

        cout << "Classificando...\n";
        objClass->executarClassificacao(objCorpus, minha_resposta);
        entrada1 += ".copy";
        objCorpus.gravarArquivo(entrada1.c_str());
        cout << "Classificado com sucesso. Veja o resultado no arquivo " << entrada1 << endl << endl;

        cout << "Executar avaliacao...\n";
        AvaliadorProvavel vf;
        vector<float> percentual = vf.calcularDesempenho(objCorpus, gabarito, minha_resposta);

        cout << "Avaliacao executada, agora vamos aos resultados.\n";
        /*for (unsigned int i = 1; i < percentual.size(); ++i)
        {
            cout << "Frase " << i << ": " << 100*percentual[i] << endl;
        }*/
        cout << "RESULTADO: " << setprecision(4) << 100*percentual[0] << "%." << endl;

        //treinador.setarDistribuicao(NULL);

        cout << "\nExecutar a validação. Validador K-Dobras.\nDigite o número de experimentos: ";
        cin >> tab;
        ValidadorKDobras valid(vf, tab);
        vector<vector<float> > dobras = valid.executarExperimento(treinador, objCorpus, gabarito, minha_resposta);
        for (int i = 0; i < tab; i++)
        {
            cout << "Dobra " << i << ": " << setprecision(4) << 100*dobras[i][0] << "%." << endl;
        }
    }
    catch (string e)
    {
        cout << "ERRO: " << e << endl;
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
    }
    return 0;
}
