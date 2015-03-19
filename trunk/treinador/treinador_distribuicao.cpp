#include "treinador/treinador_distribuicao.h"

TreinadorDistribuicao::~TreinadorDistribuicao()
{
	if (distribuicao != NULL)
		delete distribuicao;
}
