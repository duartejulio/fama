#ifndef PROCESSADORSH_H
#define PROCESSADORSH_H

#include "processador.h"

class ProcessadorSerieHistorica
{
        int janela;
        string atributo;
        bool attcriados;
		float *diferenca_i;
        bool criarNovosAtributos();
        vector<string> novosAtributos;

    public:
        ProcessadorSerieHistorica(int janela, string atributo);
        vector<string> processarCorpus(Corpus&);
        ~ProcessadorSerieHistorica();
		void atualizarJanela(int janela);
		void atualizarAtributo(string att);
		void criarAtributosAuxiliares(Corpus&, int janela);

};

#endif // PROCESSADORSH_H

