#include "classificadorc50.h"

ClassificadorC50::ClassificadorC50( vector<string> att, vector<string> classes, vector< vector<string> > attValName)
{
         this->atributos = att;
        this->classes = classes;
	this->classeNome = atributos[(atributos).size() - 1];
        this->attValName = attValName;
}

ClassificadorC50::ClassificadorC50( string arquivo )
{
    carregarConhecimento( arquivo );
}

bool ClassificadorC50::executarClassificacao( Corpus &corpusProva, int atributo, C50 &objc50 )
{
    //corpusProva.criarAtributo( "pos", "N" );
    int atributo_base,att,index,valoraux,c;
	string valor, valor_atual;
	atributo_base = corpusProva.pegarPosAtributo( classeNome );
	Tree arvoreaux,arvore;
        arvore = objc50.Pruned[0];	
	int qtdConjExemplos = corpusProva.pegarQtdConjExemplos();

for(c=0; c<qtdConjExemplos;c++)
{
    arvoreaux = arvore;
    att = arvore->Tested;
    while(arvoreaux->NodeType)
	{
		valoraux = corpusProva.pegarValor(c,0,att-1);
							valor = corpusProva.pegarSimbolo(valoraux);
							
		switch(arvoreaux->NodeType)
		{
			case BrDiscr: //caso com valores discretos
							for(int i=0; i<attValName[att-1].size(); i++){
								if(!valor.compare(attValName[att-1][i])){
									index=i+2;
									break;
								}
							}
							break;
			case BrThresh: //caso em que os valores s�o cont�nuos
							if(!valor.compare("N/A"))
							{
								index = 1;
							}
							else
							{
								float valor1;
								(std::istringstream)valor >> valor1>>std::dec;
								if(arvoreaux->Lower != arvore->Upper)
								{
									if(valor1 <= arvoreaux->Lower)
										index = 2;
									else
									{
										index = 3;
									}
								}
								else
								{
									if(valor1 <= arvoreaux->Cut)
										index=2;
									else
										index = 3;
								}
							}
							break;
			case BrSubset:	//caso em que há subconjuntos de valores discretos
							index = 2;
							int last;
							while(index<= arvoreaux->Forks)
							{
								int elementos = objc50.Elements(att, arvoreaux->Subset[index],&last);
								if(elementos ==1)
								{
									if(!valor.compare(attValName[att-1][last-2]))
									break;
								}
								else
								{
									for( int p = 2; !In(p,arvoreaux->Subset[index]);p++){
										if(!valor.compare(attValName[att-1][p-2]))
										break;
									}
								}
								index++;
							}
							break;
		}
		arvoreaux = arvoreaux->Branch[index];
	}

		string classeNovoNome = classes[arvoreaux->Leaf - 1];
		corpusProva.ajustarValor(c,0,atributo_base,corpusProva.pegarIndice(classeNovoNome.c_str()));
}
   return true;
}

bool ClassificadorC50::gravarConhecimento( string arquivo )
{
    ofstream arqout( arquivo.c_str() );
    if( !arqout.is_open() ) //verifica se arquivo conseguiu ser aberto
    {
        cout << "Erro:gravarConhecimento!\nFalha na abertura do arquivo!" << endl;
        return false;
    }
    arqout<<"Atributos"<<endl;
    for(int i=0;i< atributos.size(); i++){
        arqout<< atributos[i]<<endl;
    }
    arqout<<"Classe"<<endl;
        arqout << classeNome << endl;
        arqout<<"ValoresClasses"<<endl;
    for(int i=0;i< classes.size(); i++){
        arqout<< classes[i]<<endl;
    }
        arqout<<"ValoresAtributos"<<endl;
    for(vector< vector<string> >::iterator it = attValName.begin(); it!=attValName.end();it++){
        for(int i=0; i<(*it).size(); i++){
            arqout<<(*it)[i]<<endl;
        }
        arqout<<"FimAtributo"<<endl;
     }
    
        arqout.close();
    cout << "Arquivo <" << arquivo << "> gravado com sucesso!" << endl;
    return true;
}

bool ClassificadorC50::carregarConhecimento( string arquivo )
{
    ifstream arqin( arquivo.c_str() );
    if( !arqin.is_open() ) //verifica se arquivo conseguiu ser aberto
    {
        cout << "Erro:carregarConhecimento!\nFalha na abertura do arquivo!" << endl;
        return false;
    }
    string aux;
    arqin >> aux;
    while( aux.compare("Classe"))
    {
        atributos.push_back(aux);
        arqin>>aux;
    }
    arqin >> classeNome;
    arqin>>aux;
    while( aux.compare("ValoresAtributos"))
    {
        classes.push_back(aux);
        arqin>>aux;
    }
    vector<string> attaux;
    arqin>>aux;
    while(!arqin.eof())
    {
        while(aux.compare("FimAtributo"))
        {
            attaux.push_back(aux);
            arqin>>aux;
        }
        attValName.push_back(attaux);
        attaux.clear();
            arqin>>aux;
    }
    arqin.close();
    cout << "Arquivo <" << arquivo << "> carregado com sucesso!" << endl;
    return true;
}
