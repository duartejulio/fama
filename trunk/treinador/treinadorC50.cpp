#include "treinadorC50.h"
#include "../corpus/corpusmatrizc50.h"

#include <map>
typedef map<string, int>::const_iterator MapIterator;

TreinadorC50::TreinadorC50( float cf )
{
    this->cf = cf;
}

TreinadorC50::~TreinadorC50()
{
    //dtor
}

Classificador *TreinadorC50::executarTreinamento( Corpus &corpus, int atributo )
{
    int i, j, k;
    map <string, int> vals;

    atributos = corpus.pegarAtributos();


    this->attValName = ((CorpusC50*)&corpus)->pegarAttValores();
/*
    cout << "AttName\n";
    for (int i=0;i<attValName.size();i++){
        for (int j=0;j<attValName[i].size();j++)
            cout << "[" << attValName[i][j] << "]";
        cout << endl;
    }
    cout << "**********\n";
*/
    objC50.MaxAtt = atributos.size();

     objC50.ClassAtt = objC50.MaxAtt;

     for(i=0; i<objC50.MaxAtt;i++){
        int tam = attValName[i].size();
        if(objC50.MaxDiscrVal < tam)
        objC50.MaxDiscrVal = tam;
    }



     std::vector<string>::iterator it;
     objC50.AttName = new String[objC50.MaxAtt+1];
     objC50.AttName[0]= NULL;
     for(i=1, it= atributos.begin(); i<=objC50.MaxAtt; i++, it++){
        int tamAux = (*it).length();
        objC50.AttName[i]=(String ) calloc(tamAux, sizeof(String *));
        for(int j=0; j<tamAux;j++)
           objC50.AttName[i][j] = (*it)[j];
     }




     objC50.AttValName = (String **) calloc(objC50.MaxAtt+1, sizeof(String **));
     objC50.MaxAttVal = new DiscrValue[objC50.MaxAtt+1];

     objC50.MaxAttVal[0] = 0;
     objC50.AttValName[0] = NULL;

     for( i=1; i<=objC50.MaxAtt;i++){
           if(attValName[i-1][0]!="continuous"){
         int aux = attValName[i-1].size();

         objC50.MaxAttVal[i] = aux+1;
         objC50.AttValName[i] =(String *) calloc(objC50.MaxAttVal[i]+2, sizeof(String *));
         objC50.AttValName[i][0] = NULL;
         objC50.AttValName[i][1]= "N/A";
         for(int j=2; j<=aux+1; j++){

             int tamAux = attValName[i-1][j-2].length();
             //cout<<"attValName "<<attValName[i-1][j-2]<<endl;
             objC50.AttValName[i][j]=(String ) calloc(tamAux, sizeof(String ));
             for(int k=0; k<tamAux; k++){
                 objC50.AttValName[i][j][k] = attValName[i-1][j-2][k];
             }
         }
    }
           else{
         objC50.MaxAttVal[i]=0;
     }
     }
     int index = atributos.size()-1;
    int aux = attValName[index].size();
    for( i=0; i<aux; i++){
        classes.push_back(attValName[objC50.ClassAtt - 1][i]) ;
    }

    objC50.MaxClass = classes.size();
        objC50.ClassName = new String[objC50.MaxClass+1];
        objC50.ClassName[0] = "?";
    for(i=1, it= classes.begin(); i<=objC50.MaxClass;i++, it++)
    {
        objC50.ClassName[i] = (String ) calloc((*it).length(), sizeof(String ));
        for(int j=0; j<(*it).length();j++){
       objC50.ClassName[i][j] = (*it)[j] ;

        }
    }

    objC50.alocar();
    //objC50.imprimir();
    adicionarCasos(objC50, corpus);

    objC50.setCF(cf);
    objC50.InitialiseTreeData();
    objC50.ConstructClassifiers();
	return new ClassificadorC50( atributos, classes, attValName, objC50.Pruned[0], objC50 );
}

void TreinadorC50::adicionarCasos(C50 &objc50, Corpus &corpus)
{

    objc50.MaxCase = corpus.pegarQtdSentencas()-1;
    int linha,totlinhas,numatributos,qtdConjExemplos,c;
    numatributos= corpus.pegarQtdAtributos();
    objc50.Case = new DataRec[objc50.MaxCase+1];

    qtdConjExemplos = corpus.pegarQtdConjExemplos();
    long int index = 0;
    for (c=0; c<qtdConjExemplos; c++){
        totlinhas = corpus.pegarQtdExemplos(c);
        for(int linha = 0; linha< totlinhas; linha++, index++){

            objc50.Case[index]= (DataRec) calloc(objc50.MaxCase+1, sizeof(DataRec));
            int  vatual= corpus.pegarValor(c,linha,numatributos-1);

            string valor;
            valor = corpus.pegarSimbolo(vatual);
           /* for(int i=0; i< valor_atual.size()-1;i++){
                valor.push_back(valor_atual[i]);

            }*/



                (objc50.Case[index][0])._cont_val = 0;
                for(int i=0; i<classes.size();i++){
                    if(!valor.compare(classes[i])){
                        (objc50.Case[index][0])._discr_val = i+1;
                       i = objc50.MaxAttVal[objc50.ClassAtt];

                    }else{
                    if(i== classes.size()-1)
                            (objc50.Case[index][0])._discr_val = i+1;
                    }
                }


                for( int j=1; j<numatributos; j++)
                {
                        int  vatual= corpus.pegarValor(c,linha,j-1);

                        string valor_atual;
            valor_atual = corpus.pegarSimbolo(vatual);
                        if(!objc50.MaxAttVal[j]){

                              float numero;
            std::stringstream out2(valor_atual);
            out2 >> numero;
                             (objc50.Case[index][j])._cont_val = numero;
                        }
                        else{

                        (objc50.Case[index][j])._cont_val = 0;

                for(int k=0; k<objc50.MaxAttVal[j];k++){
                    if(!valor_atual.compare(objc50.AttValName[j][k+2])){
                   (objc50.Case[index][j])._discr_val = k+2;
                   k= objc50.MaxAttVal[j];
                    }else{
                        if(k== objc50.MaxAttVal[j]-1)
                            (objc50.Case[index][j])._discr_val = k+2;
                    }
                }
                }

                }

            }
    }

}
