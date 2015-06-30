#include "avaliador_prob.h"

vector<float> AvaliadorProvavel::calcularDesempenho( Corpus &corpus, int atributo_padrao, int atributo_teste )
{
    vector<float> porcentagem(corpus.pegarQtdSentencas()+1);
    int acertos, acertosM = 0, frase, token, total = 0;
    for (frase = 0; frase < corpus.pegarQtdSentencas(); ++frase)
    {
		acertos = 0;
		for (token = 0; token < corpus.pegarQtdExemplos(frase); ++token)
		{
			if (corpus.pegarValor(frase, token, atributo_padrao) == corpus.pegarValor(frase, token, atributo_teste))
			{
				acertos++;
				acertosM++;
			}
		}
		porcentagem[frase+1] = acertos/(float)token;
		total += token;
	}
	porcentagem[0] = acertosM/(float)total;
	return porcentagem;
}
