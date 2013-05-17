#ifndef VALIDADORKDOBRASBVMF_H
#define VALIDADORKDOBRASBVMF_H

#include "validador.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

class ValidadorKFoldDeslizante : public Validador
{
    public:
        ValidadorKFoldDeslizante( Avaliador &avaliador, int dobras );
        virtual ~ValidadorKFoldDeslizante();
        vector< vector< float > > executarExperimento( Treinador &treinador, Corpus &corpus, int atributoTreino, int atributoTeste );
        vector< vector< float > > executarExperimento2( Treinador &treinador, Corpus &corpus, int atributoTreino, int atributoTeste, int tam_janela_deslizante );

};

#endif // VALIDADORKDOBRASBVMF_H
