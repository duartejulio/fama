#ifndef TREINADORDISTRIBUICAO_H
#define TREINADORDISTRIBUICAO_H

#include "treinador.h"
#include <cstdio>

class TreinadorDistribuicao : public Treinador
{
	public:
        /// <summary>
        /// Construtor default.
        /// Seta o valor distribuição para nulo.
        /// </summary>
        TreinadorDistribuicao() : distribuicao(NULL) {}
        /// <summary>
        /// Construtor com determinada distribuição.
        /// </summary>
        /// <param name="dist"> Distribuição (ponteiro para vector de doubles).
        /// Atenção para a quantidade de exemplos da distribuição.
        /// </param>
        TreinadorDistribuicao(vector<double> *dist) : distribuicao(dist) {}
		/** Default destructor */
        virtual ~TreinadorDistribuicao();
		/** Access distribuicao
		 * \return The current value of distribuicao
		 */
        vector<double> *pegarDistribuicao() { return distribuicao; }
        /** @brief Ajusta o valor da distribuição do treinador.
         *  @param val Nova distribuição.
         *  @
		 */
        void setarDistribuicao(vector<double> *val) { delete distribuicao; distribuicao = val; }
		virtual Classificador *executarTreinamento( Corpus &corpus, int atributo ) = 0;
	protected:
		vector<double> *distribuicao; //!< Member variable "distribuicao"
};

#endif // TREINADORDISTRIBUICAO_H
