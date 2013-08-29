#include "treinadorC50.h"

TreinadorC50::TreinadorC50( vector<string> atributos, vector<string> classes, vector< vector<string> > attValName,C50 objC50, float cf )
{
    this->atributos = atributos;
    this->classes = classes;
    this-> attValName = attValName;
    this->objC50 =  objC50;
    this->cf = cf;
}

TreinadorC50::~TreinadorC50()
{
    //dtor
}

Classificador *TreinadorC50::executarTreinamento( Corpus &corpus, int atributo )
{
    objC50.setCF(cf);
    objC50.InitialiseTreeData();
    objC50.ConstructClassifiers();
	return new ClassificadorC50( atributos, classes, attValName, objC50.Pruned[0], objC50 );
}