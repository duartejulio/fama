#include "treinador_provavel.h"
#include "../corpus/corpusmatriz.h"
#include "../classificador/classificador.h"


#include <map>

using namespace std;

Classificador* TreinadorProvavel::executarTreinamento(Corpus& corpus, int atributo)
{
    map<int, map<int, map<int,int> > > prob;
    map<string, map<string, float> > probFloat;
    map<string, map<string, string> > candidatos;
    map<int, map<int, int> >::iterator itAtr;
    map<int, int>::iterator itVal;

    string nomeAtr;
    string valAtr;

	int maior, total, maiorVal;
    if (considerar)
    {
        if (considerar->size() != (unsigned)corpus.pegarQtdAtributos())
		{
			considerar->resize(corpus.pegarQtdAtributos(), true);
		}
    }
	else
	{
		considerar = new vector<bool>(corpus.pegarQtdAtributos(), true);
	}

    int frase, token, atr, atr_valor, atrFinal_valor;
    for(atr = 0; atr < corpus.pegarQtdAtributos(); ++atr)
    {
		nomeAtr = corpus.pegarAtributo(atr);
        if (atr == atributo || !(*considerar)[atr]) continue;
        prob.insert(pair<int, map<int, map<int, int> > >(atr, map<int, map<int, int> >()));
        probFloat.insert(pair<string, map<string, float> >(nomeAtr, map<string, float>()));
        candidatos.insert(pair<string, map<string, string> >(nomeAtr, map<string, string>()));
        for (frase = 0; frase < corpus.pegarQtdSentencas(); ++frase)
        {
            for (token = 0; token < corpus.pegarQtdTokens(frase); ++token)
            {
                atr_valor = corpus.pegarValor(frase, token, atr);
                atrFinal_valor = corpus.pegarValor(frase, token, atributo);
                if ((prob[atr].find(atr_valor)) == (prob[atr].end()))
                    prob[atr].insert(pair<int, map<int, int> >(atr_valor, map<int, int>()));
                if (((prob[atr][atr_valor]).find(atrFinal_valor)) == ((prob[atr][atr_valor]).end()))
                    prob[atr][atr_valor].insert(pair<int, int>(atrFinal_valor,1));
                else
                    ++(prob[atr][atr_valor][atrFinal_valor]);
            }
        }
        for(itAtr = (prob[atr]).begin(); itAtr != (prob[atr]).end(); ++itAtr)
        {
			maior = 0; maiorVal = 0; total = 0;
            for (itVal = (itAtr->second).begin(); itVal != (itAtr->second).end(); ++itVal)
            {
                total += itVal->second;
                if (itVal->second > maiorVal)
                {
					maiorVal = itVal->second;
					maior = itVal->first;
                }
            }
            if (maiorVal > 0)
            {
				valAtr = corpus.pegarSimbolo(itAtr->first);
				probFloat[nomeAtr][valAtr] =  maiorVal/(float)total;
				candidatos[nomeAtr][valAtr] = corpus.pegarSimbolo(maior);
            }
        }
    }
    return new ClassificadorProvavel(probFloat, candidatos, unknown);
}
