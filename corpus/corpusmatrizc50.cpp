#include "corpusmatrizc50.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include "../C50/c50.h"

void aparar2(string &str){
    string::size_type pos = str.find_last_not_of(' ');
    if (pos != string::npos){
        str.erase(pos + 1);
        pos = str.find_first_not_of(' ');
        if(pos != string::npos)
            str.erase(0, pos);
        
    }
    else
        str.erase(str.begin(), str.end());
}

void CorpusC50::ajustarSeparador( char separador )
{
    this->separador = separador;
}

vector<string> CorpusC50::pegarClasses(){
    return classes;
}
vector< vector<string> > CorpusC50::pegarAttValores(){
    return attValName;
}
//fun��o criada para ler o arquivo do C5.0
bool CorpusC50::carregarArquivo(C50 &objc50, string arquivo ){

    ifstream arqin((arquivo+".data").c_str()); // Abre arquivo para leitura em modo texto
   
    if( !arqin.is_open() ) //verifica se arquivo conseguiu ser aberto
    {
        cout << "Erro:carregarArquivo!\nFalha na abertura do arquivo!" << endl;
        return false;
    }
    string str,classNome;
    char ch;

    //verifica se atributos foram passados
    if (!atributos.size())
    {
         string at;
        vector<string> attnames;
        bool line=false;
        ifstream arqat( (arquivo+".names.txt").c_str()); // Abre arquivo para leitura em modo texto
        if( !arqat.is_open() ) //verifica se arquivo conseguiu ser aberto
        {
            cout<<"Erro";
        }
       else
        {
             at = "";
             //a primeira linha cont�m a o atributo classe.
             //varre linha a linha por atributos

            if(!arqat.eof())
            arqat >> at;
             for(string::iterator it= at.begin(); it!=at.end();){
                 if(*it=='.'){
                     at.erase(it);
                     it = at.end();
                 }
                 else
                     it++;
             }
             classNome = at;
            while(!arqat.eof())
            {
                arqat >> at;
                if(line){
                            string attnamesaux="";
                            for(string::iterator it = at.begin(); it!=at.end(); it++){
                                if(*it==','||*it=='.'){
                                    if(*it=='.')
                                    line=false;
                                    else {line = true;}
                                    
                                    attnames.push_back(attnamesaux);
                                    attnamesaux.clear();
                                }
                                else{
                                attnamesaux += *it;
                                }
                            }
                            if(!line){
                            attValName.push_back(attnames);
                            attnames.clear();
                            }

                }else{
                    int position = at.find(":");
                    if(position == at.size()-1)
                    {
                        at.erase(at.size()-1);
                        atributos.push_back(at);
                        line=true;
                    }
                    else{

                        for( string::iterator it = at.begin(); it != at.end(); ){
                            if( *it == ':' )
                            {
                                
                                string attnamesaux="";
                                for(string::iterator aux = it+1; aux!=at.end(); aux++){
                                    if(*aux==','||*aux=='.'){
                                        if(*aux=='.')
                                            line=false;
                                            else line = true;
                                        attnames.push_back(attnamesaux);
                                        attnamesaux.clear();
                                }
                                    else{

                                    attnamesaux += *aux;
                                }
                            }

                           if(!line){
                            attValName.push_back(attnames);
                            attnames.clear();
                            }
                               
                            at.erase( it,at.end() );
                            atributos.push_back(at);
                            it = at.end();

                    }

                    else ++it;
                }
                }
                }

            }
            arqat.close();


        }

        //realoca membros em fun��o de novos atributos do corpus
        qtd_atributos = atributos.size();
        for( register int i = 0; i < qtd_atributos; ++i )
            posAtributos[atributos[i]] = i;

        //verifica se os atributos foram carregados
        if( !qtd_atributos )
        {
            cout << "Aviso:carregarArquivo!\nN�o foi poss�vel carregar atributos!" << endl;
            return false;
        }
        else
            cout << qtd_atributos << " atributos carregados com sucesso." << endl;
    }

    qtd_sentencas = 1;
    frases.resize(1);
    frases[0].resize(1);
    frases[0][0].resize( qtd_atributos );

    int row = 0, column = 0, contador = -1,count = 0;

    // l� um caracter inicial do arquivo
    /*if(!arqin.eof()){
        string b;
        arqin>>b;
        cout<<b<<endl;
    }*/
     //arqin.get( ch );
    string buffer;
    while( !arqin.eof() ) // Enquanto n�o for fim de arquivo e a leitura n�o contiver erros
    {
        arqin>>buffer;
        std::string::iterator itaux = buffer.begin();
        if ( *itaux != '[' && *itaux != '#' )
        {
            if( *itaux != '\n' ) //considera frases com distancia maior que 1 espa�o
            {
                for( register int i = 0; i < qtd_atributos; ++i )
                {
                    // l� a palavra que ser� colocada no vector s�mbolos
                    while( ( *itaux != separador || i == qtd_atributos - 1 ) && *itaux != '\n' && itaux!=buffer.end() ) //torna programa mais
                    {                                                              //robusto em rela��o a erros '_' no corpus
                        if(ch!='.')
                        str.push_back( *itaux );
                        itaux++;
                    }
                    if (apararValores)
                        aparar2(str);
                    if ( dicionario.find( str ) == dicionario.end() )
                    {
                        dicionario[ str ] = ++contador; // nessa linha primeiro cria-se um elemento(ou seja, aumenta o size),
                                                                   // depois realiza-se a atribui��o
                        simbolos.push_back( str );
                        //if( i == 1 ) cout << str << endl;
                    }
                    ++count;
                    frases[ row ][ column ][ i ] = dicionario[ str ];
                    str.clear();    // limpa str para armazenar a pr�xima string
                    //arqin.get( ch );
                    if(itaux!=buffer.end())
                        itaux++;
                    else{
                        if(i!=qtd_atributos-1)
                        arqin>>buffer;
                    }
                }
            }

            if( arqin.eof() ) //arquivo terminando sem linha em branco
            {
                qtd_sentencas = frases.size(); //atualiza qtd de sentencas
                qtd_simbolos = simbolos.size(); //atualiza qtd de simbolos
                break;
            }

            if( *itaux == '\n' ) //verifica se ha mudan�a de frase
            {
                if( arqin.get( ch ) && !arqin.eof() && ch != '\n') //caso em que ha nova frase
                {
                    frases.resize( ++row + 1 ); //desloca para a proxima linha na matriz ( proxima frase no texto )
                    frases[row].resize(1);
                    frases[row][0].resize( qtd_atributos );
                    column = 0;
                }
                if( arqin.eof() )
                {
                    qtd_sentencas = frases.size(); //atualiza qtd de sentencas
                    qtd_simbolos = simbolos.size(); //atualiza qtd de simbolos
                    break;
                }
            }
            else
            {
                if (dividirExemplos){
                    frases.resize( ++row + 1 ); //desloca para a proxima linha na matriz ( proxima frase no texto )
                    frases[row].resize(1);
                    frases[row][0].resize( qtd_atributos );
                    column = 0;
                }
                else{
                    frases[row].resize( ++column + 1 ); //desloca p/ o proximo elemento da matriz na mesma linha
                    frases[row][column].resize( qtd_atributos );
                }
            }
        }
        else
        {
            arqin.ignore( INF, '\n' );
            //arqin.get( ch );
        }
    }

    if( arqin.bad() && !arqin.eof() )    //caso de erro na leitura do arquivo
    {
        cout << "Erro:carregarArquivo!\nErro na leitura do arquivo!" << endl;
        arqin.close();
        return false;
    }

    arqin.close();
     
     objc50.MaxAtt = atributos.size();
     
     objc50.ClassAtt = objc50.MaxAtt;
    
     for(int i=0; i<objc50.MaxAtt;i++){
        int tam = attValName[i].size();
        if(objc50.MaxDiscrVal < tam)
        objc50.MaxDiscrVal = tam;
    }
    
    
      int i;        
        std::vector<string>::iterator it;
     objc50.AttName = new String[objc50.MaxAtt+1];
       objc50.AttName[0]= NULL;
    for(i=1, it= atributos.begin(); i<=objc50.MaxAtt; i++, it++){
        int tamAux = (*it).length();
        objc50.AttName[i]=(String ) calloc(tamAux, sizeof(String *));
        for(int j=0; j<tamAux;j++)
           objc50.AttName[i][j] = (*it)[j];
    }
       
        

     
     objc50.AttValName = (String **) calloc(objc50.MaxAtt+1, sizeof(String **));
     objc50.MaxAttVal = new DiscrValue[objc50.MaxAtt+1];
     
     objc50.MaxAttVal[0] = 0;
     objc50.AttValName[0] = NULL;
   
     for( i=1; i<=objc50.MaxAtt;i++){
           if(attValName[i-1][0]!="continuous"){
         int aux = attValName[i-1].size();
         
         objc50.MaxAttVal[i] = aux+1;
         objc50.AttValName[i] =(String *) calloc(objc50.MaxAttVal[i]+2, sizeof(String *));
         objc50.AttValName[i][0] = NULL;
         objc50.AttValName[i][1]= "N/A";
         for(int j=2; j<=aux+1; j++){
             
             int tamAux = attValName[i-1][j-2].length();
             objc50.AttValName[i][j]=(String ) calloc(tamAux, sizeof(String ));
             for(int k=0; k<tamAux; k++){
                 objc50.AttValName[i][j][k] = attValName[i-1][j-2][k];
             }
         }
    }
           else{
         objc50.MaxAttVal[i]=0;
     }
     }
     int index = atributos.size()-1;
    int aux = attValName[index].size();
    for( i=0; i<aux; i++){
        classes.push_back(attValName[4][i]) ;
    }
     
    objc50.MaxClass = classes.size();
        objc50.ClassName = new String[objc50.MaxClass+1];
        objc50.ClassName[0] = "?";
    for(i=1, it= classes.begin(); i<=objc50.MaxClass;i++, it++)
    {  
        objc50.ClassName[i] = (String ) calloc((*it).length(), sizeof(String ));
        for(int j=0; j<(*it).length();j++){
       objc50.ClassName[i][j] = (*it)[j] ;

        }
    }
    cout << "Arquivo <" << arquivo << "> carregado com sucesso!" << endl;
    
    objc50.alocar();
  adicionarCasos(objc50);
    return true;
}


bool CorpusC50::gravarArquivo( string arquivo )
{
    ofstream arqout( arquivo.c_str() ); //Abre arquivo para escrita em modo texto
    if( !arqout.is_open() ) //verifica se arquivo conseguiu ser aberto
    {
        cout << "Erro:gravarArquivo!\nFalha na abertura do arquivo!" << endl;
        return false;
    }

    int column, k;

    arqout << "[atributos=";
    for( k = 0; k < qtd_atributos - 1; ++k )
        arqout << atributos[k] << ",";
    arqout << atributos[k] << "] [separador=" << separador << "]" << endl;
    
    for( register int i = 0; i < qtd_sentencas; ++i )
    {
        column = frases[i].size();        
        for( register int j = 0; j < column; ++j )
        {
            for( k = 0; k < qtd_atributos - 1; ++k )
                arqout << simbolos[ frases[i][j][k] ] << separador;
            arqout << simbolos[ frases[i][j][k] ]<<" ." << endl;
        }
        arqout << endl;
    }

    arqout.close();

    cout << "Arquivo <" << arquivo << "> gravado com sucesso!" << endl;

    return true;
}

Corpus* CorpusC50::clone()
{
    return new CorpusC50( *this );
}


CorpusC50::CorpusC50(vector<string> atributos, char separador,
                           bool dividirExemplos, bool apararValores)
    :Corpus( atributos )
{
    //ctor
    this->separador = separador;
    this->dividirExemplos = dividirExemplos;
    this->apararValores = apararValores;
}
bool CorpusC50::carregarArquivo( string arquivo )
{
    ifstream arqin( arquivo.c_str() ); // Abre arquivo para leitura em modo texto
    if( !arqin.is_open() ) //verifica se arquivo conseguiu ser aberto
    {
        cout << "Erro:carregarArquivo!\nFalha na abertura do arquivo!" << endl;
        return false;
    }
    string str;
    char ch;

    //verifica se atributos foram passados
    if (!atributos.size())
    {
        string at;
        ifstream arqat( (arquivo + ".names.txt").c_str() ); // Abre arquivo para leitura em modo texto
        if( !arqat.is_open() ) //verifica se arquivo conseguiu ser aberto
        {
            at = "";
            arqin.get( ch );
            if( ch == '[' )
            {
                char s[1000];
                arqin.get( s, 1000, '\n' );
                string str(s);
                int i = 0;
                //apaga espa�os em branco da string
                for( string::iterator it = str.begin(); it != str.end(); )
                    if( *it == ' ' ) it = str.erase( it );
                    else ++it;

                while( str[i] != '=' )
                    at += str[i++];
                if( at == "features" || at == "atributos")
                {
                    while( str[i] != ']' )
                    {
                        at = "";
                        while( str[++i] != ',' && str[i] != ']' )
                            at += str[i];
                        atributos.push_back( at );
                    }
                    if( str[++i] == '[' )
                    {
                        at = "";
                        while( str[++i] != '=' && str[i] != ']' )
                            at += str[i];
                        cout << "*" << at << "*";
                        if( at == "separator" || at == "separador")
                            separador = str[++i];
                    }
                    arqin.seekg( 0, ios::beg );
                }
                else
                {
                    cout << "Aviso:carregarArquivo!\nN�o foi poss�vel carregar atributos!" << endl;
                    return false;
                }
            }
            else
            {
                cout << "Aviso:carregarArquivo!\nN�o foi poss�vel carregar atributos!" << endl;
                return false;
            }
        }
        else
        {
            //varre linha a linha por atributos
            while(arqat.good())
            {
                arqat >> at;
                if (arqat.eof())
                    break;
                atributos.push_back(at);
            }
            arqat.close();
        }

        //realoca membros em fun��o de novos atributos do corpus
        qtd_atributos = atributos.size();
        for( register int i = 0; i < qtd_atributos; ++i )
            posAtributos[atributos[i]] = i;

        //verifica se os atributos foram carregados
        if( !qtd_atributos )
        {
            cout << "Aviso:carregarArquivo!\nN�o foi poss�vel carregar atributos!" << endl;
            return false;
        }
        else
            cout << qtd_atributos << " atributos carregados com sucesso." << endl;
    }

    qtd_sentencas = 1;
    frases.resize(1);
    frases[0].resize(1);
    frases[0][0].resize( qtd_atributos );

    int row = 0, column = 0, contador = -1,count = 0;

    // l� um caracter inicial do arquivo
    arqin.get( ch );

    while( arqin.good() ) // Enquanto n�o for fim de arquivo e a leitura n�o contiver erros
    {
        if ( ch != '[' && ch != '#' )
        {
            if( ch != '\n' ) //considera frases com distancia maior que 1 espa�o
            {
                for( register int i = 0; i < qtd_atributos; ++i )
                {
                    // l� a palavra que ser� colocada no vector s�mbolos
                    while( ( ch != separador || i == qtd_atributos - 1 ) && ch != '\n' && !arqin.eof() ) //torna programa mais
                    {                                                              //robusto em rela��o a erros '_' no corpus
                        str.push_back( ch );
                        arqin.get( ch );
                    }

                    if (apararValores)
                        aparar2(str);

                    if ( dicionario.find( str ) == dicionario.end() )
                    {
                        dicionario[ str ] = ++contador; // nessa linha primeiro cria-se um elemento(ou seja, aumenta o size),
                                                                   // depois realiza-se a atribui��o
                        simbolos.push_back( str );
                        //if( i == 1 ) cout << str << endl;
                    }
                    ++count;
                    frases[ row ][ column ][ i ] = dicionario[ str ];
                    str.clear();    // limpa str para armazenar a pr�xima string
                    arqin.get( ch );
                }
            }

            if( arqin.eof() ) //arquivo terminando sem linha em branco
            {
                qtd_sentencas = frases.size(); //atualiza qtd de sentencas
                qtd_simbolos = simbolos.size(); //atualiza qtd de simbolos
                break;
            }

            if( ch == '\n' ) //verifica se ha mudan�a de frase
            {
                if( arqin.get( ch ) && !arqin.eof() && ch != '\n') //caso em que ha nova frase
                {
                    frases.resize( ++row + 1 ); //desloca para a proxima linha na matriz ( proxima frase no texto )
                    frases[row].resize(1);
                    frases[row][0].resize( qtd_atributos );
                    column = 0;
                }
                if( arqin.eof() )
                {
                    qtd_sentencas = frases.size(); //atualiza qtd de sentencas
                    qtd_simbolos = simbolos.size(); //atualiza qtd de simbolos
                    break;
                }
            }
            else
            {
                if (dividirExemplos){
                    frases.resize( ++row + 1 ); //desloca para a proxima linha na matriz ( proxima frase no texto )
                    frases[row].resize(1);
                    frases[row][0].resize( qtd_atributos );
                    column = 0;
                }
                else{
                    frases[row].resize( ++column + 1 ); //desloca p/ o proximo elemento da matriz na mesma linha
                    frases[row][column].resize( qtd_atributos );
                }
            }
        }
        else
        {
            arqin.ignore( INF, '\n' );
            arqin.get( ch );
        }
    }

    if( arqin.bad() && !arqin.eof() )    //caso de erro na leitura do arquivo
    {
        cout << "Erro:carregarArquivo!\nErro na leitura do arquivo!" << endl;
        arqin.close();
        return false;
    }

    arqin.close();
    cout << "Arquivo <" << arquivo << "> carregado com sucesso!" << endl;
    return true;
}

void CorpusC50::adicionarCasos(C50 &objc50)
{
   
    objc50.MaxCase = pegarQtdSentencas()-1;
    int linha,totlinhas,numatributos,qtdConjExemplos,c;
    numatributos= pegarQtdAtributos();
    objc50.Case = new DataRec[objc50.MaxCase+1];

    qtdConjExemplos = pegarQtdConjExemplos();
    for (c=0; c<qtdConjExemplos; c++){
        totlinhas = pegarQtdExemplos(c);
        for(int linha = 0; linha< totlinhas; linha++){
            
            objc50.Case[c+linha]= (DataRec) calloc(objc50.MaxCase+1, sizeof(DataRec));
            int  vatual= pegarValor(c,linha,numatributos-1);
           
            string valor;
            valor = pegarSimbolo(vatual);
           /* for(int i=0; i< valor_atual.size()-1;i++){
                valor.push_back(valor_atual[i]);
               
            }*/
           
            
               
                (objc50.Case[c+linha][0])._cont_val = 0;
                for(int i=0; i<classes.size();i++){
                    if(!valor.compare(classes[i])){
                        (objc50.Case[c+linha][0])._discr_val = i+1;
                       i = objc50.MaxAttVal[objc50.ClassAtt];
                      
                    }else{
                    if(i== classes.size()-1)
                            (objc50.Case[c+linha][0])._discr_val = i+1;
                    }
                }
            
           
                for( int j=1; j<numatributos; j++)
                {
                        int  vatual= pegarValor(c,linha,j-1);
                        
                        string valor_atual;
            valor_atual = pegarSimbolo(vatual);
                        if(!objc50.MaxAttVal[j]){
                            
                              float numero;
            std::stringstream out2(valor_atual);
            out2 >> numero;
                             (objc50.Case[c+linha][j])._cont_val = numero;
                        }
                        else{
                        (objc50.Case[c+linha][j])._cont_val = 0;
                for(int k=0; k<objc50.MaxAttVal[j];k++){
                    if(!valor_atual.compare(objc50.AttValName[j][k+2])){
                   (objc50.Case[c+linha][j])._discr_val = k+2;
                   k= objc50.MaxAttVal[objc50.ClassAtt];
                    }else{
                        if(k== objc50.MaxAttVal[objc50.ClassAtt]-1)
                            (objc50.Case[c+linha][j])._discr_val = k+2;
                    }
                }
                }
                }

            }
    }
      
}


void CorpusC50::casos(C50 &objc50){
    
        FILE *dados;
    dados =fopen("C:\\Users\\Leticia Cremasco\\Documents\\IP\\fama\\testes\\hypothyroid.data.txt","r+");
    if(!dados)
 {
    printf( "Erro na abertura do arquivo");
    exit(0);
 }
    objc50.alocar();

    FILE *atributos;
    atributos = fopen("C:\\Users\\Leticia Cremasco\\Documents\\IP\\fama\\testes\\hypothyroid.names.txt","r+");
    if(!atributos)
 {
    printf( "Erro na abertura do arquivo");
    exit(0);
 }
    objc50.Of = stdout;
if(!objc50.Of)
 {
    printf( "Erro na abertura do arquivo");
    exit(0);
 }
    //FILE *teste("hypothyroid.test","r+");
objc50.GetNames(atributos);


    objc50.GetData(dados, true,false);
    int j,i;
    printf("%d\n",objc50.ClassAtt);
    for(i=0; i< objc50.MaxAtt; i++){
        printf("%s\n",objc50.AttName[i]);
    }
   
    for(i=0; i<objc50.MaxAtt;i++){
        printf("\n\n %d \n\n",objc50.MaxAttVal[i]);
        for(j=0; j<objc50.MaxAttVal[i];j++){
             printf("%s\n",objc50.AttValName[i][j]);
        }
        
    }
    for( j=0; j<=objc50.MaxCase; j++){
        for(i=0; i<objc50.MaxAtt; i++){
            printf("%d\n,%f\n",objc50.Case[j][i]._discr_val,objc50.Case[j][i]._cont_val);
            
        }
        printf("acabou uma linha\n");
    }
    for(i=0; i<=objc50.MaxClass;i++){
        cout<<"nome da classe "<<i<<objc50.ClassName[i]<<endl;
    }
    printf("MaxdiscrVal %d\n",objc50.MaxDiscrVal);
    for(int i=0; i< 5 ;i++){
    printf("SpecialCase %c", objc50.SpecialStatus[i]);}
    
    printf("MaxClass %d\n", objc50.MaxClass);
    fclose(dados);
}