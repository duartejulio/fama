#include "classificador_provavel.h"
#include "../corpus/corpus.h"

#include <map>
#include <fstream>

using namespace std;

bool ClassificadorProvavel::executarClassificacao(Corpus &corpusProva, int atributo)
{
    map<string, map<string, float> >::iterator itAtr;
    map<string, float> probSoma;
    map<string, float>::iterator itProb;

    float prob;
    string cand, valor, atrStr;
    int frase, token, atr;

    for (frase = 0; frase < corpusProva.pegarQtdSentencas(); ++frase)
    {
        for (token = 0; token < corpusProva.pegarQtdTokens(frase); ++token)
        {
            for (atr = 0; atr < corpusProva.pegarQtdAtributos(); ++atr)
            {
                atrStr = corpusProva.pegarAtributo(atr);
                if ((itAtr = probabilidades.find(atrStr)) == probabilidades.end()) continue;
                valor = corpusProva.pegarSimbolo(corpusProva.pegarValor(frase, token, atr));
                try
                {
                    prob = (itAtr->second).at(valor);
                    cand = (candidatos[atrStr][valor]);
                    if (probSoma.find(cand) != probSoma.end())
                        probSoma[cand] += prob;
                    else
                        probSoma.insert(pair<string, int>(cand, 0.0));
                }
                catch (exception e)
                {
                    cout << e.what() << " on token" << token << " (" << frase << ")\t"
                         << atrStr << '(' << atr << ") " << valor << endl;
                }
            }
            if (probSoma.empty())
            {
                if (!corpusProva.ajustarValor(frase, token, atributo, corpusProva.pegarIndice(unknown)))
                    return false;
            }
            else
            {
                prob = 0.0;
                for (itProb = probSoma.begin(); itProb != probSoma.end(); ++itProb)
                {
                    if (itProb->second > prob)
                    {
                        cand = itProb->first;
                        prob = itProb->second;
                    }
                    probSoma.erase(itProb);
                }
                if (prob)
                {
                    if (!corpusProva.ajustarValor(frase, token, atributo, corpusProva.pegarIndice(cand)))
                        return false;
                }
                else
                {
                    if (!corpusProva.ajustarValor(frase, token, atributo, corpusProva.pegarIndice(unknown)))
                        return false;
                }
            }
            //cout << "" << frase << " e " << token << " classificados.\n";
        }
    }

    return true;
}

/*std::vector<std::vector<string> > ClassificadorProvavel::executarAlgoritmo(Corpus &corpus)
{
    vector<vector<string> > retorno = vector<vector<string> >(corpus.pegarQtdSentencas());
    map<string, map<string, float> >::iterator itAtr;
    map<string, float> probSoma;
    map<string, float>::iterator itProb;

    float prob;
    string cand, valor, atrStr;
    int frase, token, atr;

    for (frase = 0; frase < corpus.pegarQtdSentencas(); ++frase)
    {
        retorno[frase] = vector<string>(corpus.pegarQtdTokens(frase));
        for (token = 0; token < corpus.pegarQtdTokens(frase); ++token)
        {
            for (atr = 0; atr < corpus.pegarQtdAtributos(); ++atr)
            {
                atrStr = corpus.pegarAtributo(atr);
                if ((itAtr = probabilidades.find(atrStr)) == probabilidades.end()) continue;
                valor = corpus.pegarSimbolo(corpus.pegarValor(frase, token, atr));
                try
                {
                    prob = (itAtr->second).at(valor);
                    cand = (candidatos[atrStr][valor]);
                    if (probSoma.find(cand) != probSoma.end())
                        probSoma[cand] += prob;
                    else
                        probSoma.insert(pair<string, int>(cand, 0.0));
                }
                catch (exception e)
                {
                    cout << e.what() << " on token" << token << " (" << frase << ")\t"
                         << atrStr << '(' << atr << ") " << valor << endl;
                }
            }
            if (probSoma.empty())
            {
                retorno[frase][token] = unknown;
            }
            else
            {
                prob = 0.0;
                for (itProb = probSoma.begin(); itProb != probSoma.end(); ++itProb)
                {
                    if (itProb->second > prob)
                    {
                        cand = itProb->first;
                        prob = itProb->second;
                    }
                    probSoma.erase(itProb);
                }
                if (prob)
                {
                    retorno[frase][token] = cand;
                }
                else
                {
                    retorno[frase][token] = unknown;
                }
            }
            //cout << "" << frase << " e " << token << " classificados.\n";
        }
    }
    return retorno;
}*/

bool ClassificadorProvavel::gravarConhecimento( string arquivo )
{
    ofstream saida (arquivo.c_str());

    if (!saida.is_open())
        return false;
    map<string, map<string, float> >::iterator it;
    map<string, float>::iterator it2;

    for (it = probabilidades.begin(); it != probabilidades.end(); ++it)
    {
        saida << "atr " << it->first << endl;
        for(it2 = (it->second).begin(); it2 != (it->second).end(); ++it2)
        {
            saida << it2->first << ' ' << candidatos[it->first][it2->first] << ' ' << it2->second << endl;
        }
    }
    saida.close();
    return true;
}

bool ClassificadorProvavel::carregarConhecimento( string arquivo )
{
    ifstream entrada(arquivo.c_str());

    if (!entrada.is_open())
        return false;

    map<string, map<string, float> >::iterator itProb = probabilidades.begin();
    map<string, map<string, string> >::iterator itCand = candidatos.begin();

    string in1, in2;
    float freq;
    entrada >> in1;
    if (in1 != "atr")
    {
        entrada.close();
        return false;
    }
    while (!entrada.eof())
    {

        entrada >> in2;
        itProb = probabilidades.insert(itProb, pair<string, map<string, float> >(in2, map<string, float>()));
        itCand = candidatos.insert(itCand, pair<string, map<string, string> >(in2, map<string, string>()));
        entrada >> in1;
        while (in1 != "atr")
        {
            entrada >> in2 >> freq;
            (itProb->second)[in1] = freq;
            (itCand->second)[in1] = in2;
            entrada >> in1;
        }
    }

    entrada.close();
    return true;
}

string ClassificadorProvavel::descricaoConhecimento()
{
    return "Pega o valor mais provável de cada atributo, compara com todos os atributos, e pega o resultado.";
}
