#ifndef AVALIADOR_ENTIDADE_H
#define AVALIADOR_ENTIDADE_H

#include "avaliador.h"

struct Entidade{
    string tipo;
    int conjunto, janelaI, janelaF;
    Entidade(string tipo, int conjunto, int janelaI, int janelaF):
    tipo(tipo),conjunto(conjunto),janelaI(janelaI), janelaF(janelaF){

    }

    bool operator==(struct Entidade &e){
        return (tipo == e.tipo && conjunto == e.conjunto &&
         janelaI == e.janelaI && janelaF == e.janelaF);
    }
};

class AvaliadorEntidade : public Avaliador
{
    string entidadeConsiderar;
    public:
        AvaliadorEntidade(string entidadeConsiderar = "O");
        virtual ~AvaliadorEntidade();
        virtual vector<float> calcularDesempenho( Corpus &corpus, int atributo_padrao,
                                                  int atributo_teste );
        virtual vector<float> calcularDesempenho2( Corpus &corpus, int atributo_padrao, int atributo_teste, int atributo_considerar ){return vector<float>();}

};

#endif // AVALIADOR_ENTIDADE_H
