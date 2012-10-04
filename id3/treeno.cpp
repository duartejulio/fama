#include "dtree.h"
#include <cmath>

TreeNo::TreeNo () {
        nomeNo="";
}

TreeNo::TreeNo(string nome) {
        nomeNo=nome;
        cout << "\nCriar no: " << nomeNo;
}

void TreeNo::adicionarNo(string nome) {
        nomeNo=nome;
        cout << "\nCriar no: " << nomeNo;
}

void TreeNo::pegarValoresNo (Corpus &corpus, int atributo, int iRespostaNo) {
        map <string, int>::iterator it;
        map <string, TreeNo*>::iterator ite;

        vector<string> atributosNo;
        int nExemplos, nConjExemplos, c, e, qualidade, iValor, freq;
        string melhorAttrNo, nomeAtributoAlvo;
        Corpus *subcorpusNo;

        nomeAtributoAlvo = corpus.pegarAtributo(iRespostaNo);

        nConjExemplos = corpus.pegarQtdConjExemplos();
        //determina quais são os valores possíveis para o atributo
        mapaValoresNo.clear();
        cout << "\n ========== PEGAR VALORES =============" << endl;
//            cout << "\n Atributo: " << atributos[atributo] << endl;

        for (c=0; c < nConjExemplos; c++){
            nExemplos = corpus.pegarQtdExemplos(c);
            for (e=0; e < nExemplos; e++){
                mapaValoresNo   [corpus.pegarSimbolo(corpus.pegarValor(c, e, atributo))] = 0;
                mapaValoresEndNo[corpus.pegarSimbolo(corpus.pegarValor(c, e, atributo))];
            }
        }

        for (it = mapaValoresNo.begin(); it!=mapaValoresNo.end(); it++){
            iValor = corpus.pegarIndice(it->first);
            //calcula a frequencia de valores nesse atributo
            qualidade = 0;
            for (c=0; c < nConjExemplos; c++){
                nExemplos = corpus.pegarQtdExemplos(c);
                for (e=0; e < nExemplos; e++){
                    if (iValor == corpus.pegarValor(c, e, atributo))
                        qualidade++;
                }
            }
            it->second = qualidade;
            cout << "\n" <<  it->first << " / ";
            cout << it->second;
            cout << "\n-----------------------------------------------------------------------------\n";
        }

        nExemplos = 0;
        cout << "\n ++++++++++++++++++++++++++++++++++++" << endl;
        cout << "\n Atributo: " << corpus.pegarAtributo(atributo) << endl;
        cout << "\n ++++++++++++++++++++++++++++++++++++" << endl;
        for (it = mapaValoresNo.begin(); it!=mapaValoresNo.end(); it++)
             nExemplos += it->second;

        for (it = mapaValoresNo.begin(), ite = mapaValoresEndNo.begin(); it!=mapaValoresNo.end(); it++, ite++) {
            cout << "\n-----------------------------------------------------------------------------\n";
            cout << "\n Criar subcorpus com o valor: " << it->first;
            iValor = corpus.pegarIndice(it->first);
            freq = it->second;

            vector < vector <bool> > mascara;
            mascara.resize(corpus.pegarQtdConjExemplos());
            for (c=0; c<corpus.pegarQtdConjExemplos(); c++){
                mascara[c].resize(corpus.pegarQtdExemplos(c));
                for (e=0; e < corpus.pegarQtdExemplos(c); e++)
                    mascara[c][e] = (iValor ==  corpus.pegarValor(c, e, atributo));
            }
            subcorpusNo = corpus.gerarSubCorpus(mascara);

            subcorpusNo->removerAtributo(atributo);
//                 subcorpusNo.removerAtributo(subcorpusNo.pegarAtributo(atributo));

            iRespostaNo = subcorpusNo->pegarPosAtributo(nomeAtributoAlvo);

//                 iRespostaNo = subcorpusNo.pegarPosAtributo(atraux);
            cout << endl << "iRespostaNo: " << iRespostaNo << endl;

            melhorAttrNo=" ";
            atributosNo = subcorpusNo->pegarAtributos();
            melhorAttrNo = pegarValorMaiorFreq(*subcorpusNo, iRespostaNo);
            int freqResposta=pegarValorFreq(*subcorpusNo, iRespostaNo);

            if ((subcorpusNo->pegarQtdTotalExemplos()<=1) || ((subcorpusNo->pegarQtdAtributos()-1)<=0)) {
                ite->second = new TreeNo (melhorAttrNo);
                //cout << "\n End No: " << ite->second;
                //cout << endl << "Press any key to quit..." << endl;
                //getch();
                continue;
            }
            if (freqResposta==subcorpusNo->pegarQtdTotalExemplos()) {
                cout << "\n freqResposta: " << freqResposta;
                cout << "\n qtd exemplos: " << subcorpusNo->pegarQtdTotalExemplos();
                ite->second = new TreeNo (melhorAttrNo);
                //cout << "\n End No: " << ite->second;
                //cout << endl << "Press any key to quit..." << endl;
                //getch();
                continue;
            }
//                 melhorAttr=objNo.escolherAtributoNo(subcorpusNo, atributosNo, iRespostaNo);

            melhorAttrNo=escolherAtributoNo(*subcorpusNo, atributosNo, iRespostaNo);
            ite->second = new TreeNo (melhorAttrNo);
            //cout << "\n End No: " << ite->second;
            //cout << endl << "Press any key to quit..." << endl;
            //getch();

            (*ite->second).pegarValoresNo(*subcorpusNo, subcorpusNo->pegarPosAtributo(melhorAttrNo), iRespostaNo);
            delete subcorpusNo;
        }

        return;
}


// retorna o valor que aparece com mais frequencia
string TreeNo::pegarValorMaiorFreq (Corpus &corpus, int atributo) {
        map <string, int> mapaValoresMaior;
        map <string, int>::iterator it;
        int nConjExemplos, nExemplos, c, e, qualidade, iValor;
        int maiorFreq = 0;
        string valorMaior;

        nConjExemplos = corpus.pegarQtdConjExemplos();

        for (c = 0; c < nConjExemplos; c++){
            nExemplos = corpus.pegarQtdExemplos(c);
            for (e=0; e < nExemplos; e++)
                mapaValoresMaior[corpus.pegarSimbolo(corpus.pegarValor(c, e, atributo))] = 0;
        }

        //da pra melhorar tambem
        for (it = mapaValoresMaior.begin(); it!=mapaValoresMaior.end(); it++){
            iValor = corpus.pegarIndice(it->first);
            //calcula a frequencia de valores nesse atributo
            qualidade = 0;
            for (c = 0; c < nConjExemplos; c++){
                nExemplos = corpus.pegarQtdExemplos(c);
                for (e=0; e < nExemplos; e++){
                    if (iValor == corpus.pegarValor(c, e, atributo))
                        qualidade++;
                }
            }
            it->second = qualidade;
            //cout << iValor << " / ";
           // cout << "\n" <<  it->first << " / ";
           // cout << it->second;
           // cout << "\n-----------------------------------------------------------------------------\n";
        }
         for (it = mapaValoresMaior.begin(); it!=mapaValoresMaior.end(); it++)
             if (it->second > maiorFreq) {
                maiorFreq = it->second;
                valorMaior = it->first;
             }
         return valorMaior;
}

// retorna a maior frequencia
int TreeNo::pegarValorFreq (Corpus &corpus, int atributo) {
        map <string, int> mapaValoresMaior;
        map <string, int>::iterator it;
        int nExemplos, nConjExemplos, c, e, qualidade, iValor;
        int maiorFreq = 0;
        string valorMaior;

        nConjExemplos = corpus.pegarQtdConjExemplos();

        for (c = 0; c < nConjExemplos; c++){
            nExemplos = corpus.pegarQtdExemplos(c);
            for (e=0; e < nExemplos; e++)
                mapaValoresMaior[corpus.pegarSimbolo(corpus.pegarValor(c, e, atributo))] = 0;
        }

        for (it = mapaValoresMaior.begin(); it!=mapaValoresMaior.end(); it++){
            iValor = corpus.pegarIndice(it->first);
            //calcula a frequencia de valores nesse atributo
            qualidade = 0;
            for (c = 0; c < nConjExemplos; c++){
                nExemplos = corpus.pegarQtdExemplos(c);
                for (e=0; e < nExemplos; e++){
                    if (iValor == corpus.pegarValor(c, e, atributo))
                        qualidade++;
                }
            }
            it->second = qualidade;
            //cout << iValor << " / ";
            cout << "\n" <<  it->first << " / ";
            cout << it->second;
            cout << "\n-----------------------------------------------------------------------------\n";
        }
         for (it = mapaValoresMaior.begin(); it!=mapaValoresMaior.end(); it++)
             if (it->second > maiorFreq) {
                maiorFreq = it->second;
                valorMaior = it->first;
             }
         cout << "\nMaior freq: " << maiorFreq << endl;

         return maiorFreq;
}

// escolhe atributo de melhor ganho
string TreeNo::escolherAtributoNo (Corpus &subcorpus, vector<string> atr, int atributoAlvo) {
         vector<string>::iterator it;
         double melhorGanho = 0.0, nganho = 0.0;
         string melhorAtributo;
         int iatributo;
         for (it = atr.begin(); it != atr.end(); it++) {
              if (*it != atr[atributoAlvo]) {
                  iatributo=subcorpus.pegarPosAtributo(*it);
                  cout << "\nAtr: " << *it << endl;
                  cout << "\nPosAtr :" << iatributo << endl;
                  nganho = ganho(subcorpus, iatributo, atributoAlvo);
                  if (nganho >= melhorGanho) {
                     melhorGanho = nganho;
                     melhorAtributo = *it;
                  }
              }
         }
         cout << "\n melhor ganho: " << melhorGanho << endl;
         cout << "\n melhor atributo: " << melhorAtributo;

         return melhorAtributo;
}

// calcula a entropia de um atributo
double TreeNo::entropia (Corpus &corpus, int atributo) {
        map <string, int> mapaValoresFreq;
        map <string, int>::iterator it;
        int nConjExemplos, c, nExemplos=0, e, qualidade, iValor, freq;
        double valor_entropia = 0.0;
        float prob = 0.0;

        //determina quais são os valores possíveis para o atributo
    //            cout << "\n ========== PEGAR VALORES PARA ENTROPIA =============" << endl;
        nConjExemplos = corpus.pegarQtdConjExemplos();

        for (c = 0; c < nConjExemplos; c++){
            nExemplos = corpus.pegarQtdExemplos(c);
            for (e=0; e < nExemplos; e++)
                mapaValoresFreq[corpus.pegarSimbolo(corpus.pegarValor(c, e, atributo))] = 0;
        }

        for (it = mapaValoresFreq.begin(); it!=mapaValoresFreq.end(); it++){
            iValor = corpus.pegarIndice(it->first);
            //calcula a frequencia de valores nesse atributo
            qualidade = 0;
            for (c = 0; c < nConjExemplos; c++){
                nExemplos = corpus.pegarQtdExemplos(c);
                for (e=0; e < nExemplos; e++){
                    if (iValor == corpus.pegarValor(c, e, atributo))
                        qualidade++;
                }
            }
            it->second = qualidade;
            //cout << iValor << " / ";
    //                cout << "\n" <<  it->first << " / ";
    //                cout << it->second;
    //                cout << "\n-----------------------------------------------------------------------------\n";
        }

    //             cout << "\n ========== ENTROPIA =============" << endl;
         nExemplos=0;
         for (it = mapaValoresFreq.begin(); it!=mapaValoresFreq.end(); it++)
             nExemplos += it->second;

         for (it = mapaValoresFreq.begin(); it!=mapaValoresFreq.end(); it++){
             freq = it->second;
             prob = (float) freq/nExemplos;
             valor_entropia += ((-prob) * log2(prob));
        }

        return valor_entropia;
}

// calcula o ganho da informacao
double TreeNo::ganho (Corpus &corpus, int atributo, int atributoAlvo) {
        map <string, int> mapaValores;
        map <string, int>::iterator it;
        Corpus *subcorpusganho;
        //subcorpusganho.ajustarSeparador(',');
        int nConjExemplos, c, nExemplos, i, e, qualidade, iValor, freq, column;
        double valor_entropia = 0.0, subentropia = 0.0, valor_ganho = 0.0;
        float prob = 0.0;

        nConjExemplos = corpus.pegarQtdConjExemplos();

        //determina quais são os valores possíveis para o atributo
        mapaValores.clear();
        i = corpus.pegarPosAtributo(corpus.pegarAtributo(atributo));
        cout << "\n ========== PEGAR VALORES =============" << endl;
        cout << "\n Atributo: " << corpus.pegarAtributo(atributo) << endl;

        for (c = 0; c < nConjExemplos; c++){
            nExemplos = corpus.pegarQtdExemplos(c);
            for (e=0; e < nExemplos; e++)
                mapaValores[corpus.pegarSimbolo(corpus.pegarValor(c, e, i))] = 0;
        }

        for (it = mapaValores.begin(); it!=mapaValores.end(); it++){
            iValor = corpus.pegarIndice(it->first);
            //calcula a frequencia de valores nesse atributo
            qualidade = 0;
            for (c = 0; c < nConjExemplos; c++){
                nExemplos = corpus.pegarQtdExemplos(c);
                for (e=0; e < nExemplos; e++){
                    if (iValor == corpus.pegarValor(c, e, i))
                        qualidade++;
                }
            }
            it->second = qualidade;
//               cout << iValor << " / ";
            cout << "\n" <<  it->first << " / ";
            cout << it->second;
            cout << "\n-----------------------------------------------------------------------------\n";
        }

        for( register int s = 0 ; s < corpus.pegarQtdConjExemplos(); s++ ) {
             for( register int j = 0; j < corpus.pegarQtdExemplos(s); j++ ) {
                    column=corpus.pegarQtdAtributos();
                    cout << "\n";
                    for (register int cont=0; cont < column; cont++) {
                            cout << corpus.pegarSimbolo(corpus.pegarValor(s, j, cont)) << ", ";
                    }
             }

         }

         nExemplos = 0;
         cout << "\n ++++++++++++++++++++++++++++++++++++" << endl;
         cout << "\n Atributo: " << corpus.pegarAtributo(atributo) << endl;
         cout << "\n ++++++++++++++++++++++++++++++++++++" << endl;

         cout << "\n AtributoAlvo: " << corpus.pegarAtributo(atributoAlvo) << endl;

         for (it = mapaValores.begin(); it!=mapaValores.end(); it++)
             nExemplos += it->second;

         for (it = mapaValores.begin(); it!=mapaValores.end(); it++) {
//                 cout << "\n-----------------------------------------------------------------------------\n";
//                 cout << "\n Criar subcorpus com o valor: " << it->first;
            iValor = corpus.pegarIndice(it->first);
            freq = it->second;
            prob = (float) freq/nExemplos;

            vector < vector <bool> > mascara;
            mascara.resize(corpus.pegarQtdConjExemplos());
            for (c=0; c<corpus.pegarQtdConjExemplos(); c++){
                mascara[c].resize(corpus.pegarQtdExemplos(c));
                for (e=0; e < corpus.pegarQtdExemplos(c); e++)
                    mascara[c][e] = (iValor ==  corpus.pegarValor(c, e, atributo));
            }
            subcorpusganho = corpus.gerarSubCorpus(mascara);
            subentropia += (prob * entropia(*subcorpusganho, atributoAlvo));
            delete subcorpusganho;
         }
         valor_entropia = entropia(corpus, atributoAlvo);
         valor_ganho = valor_entropia - subentropia;
         cout << "\n Valor da entropia total: " << valor_entropia << endl;
         cout << "\n Valor do ganho " << endl;
         cout << "\n (Valor da entropia total - Valor subentropia acumulada): " << valor_ganho << endl;
//             cout << "\n";
         cout << "\n=============================================================================\n";

         return valor_ganho;
}


// imprimir arvore de decisao
void TreeNo::imprimirNo() {
     map <string, TreeNo*>::iterator ite;
     for (ite = mapaValoresEndNo.begin(); ite!=mapaValoresEndNo.end(); ite++){
         cout << "\n\n\t\t" <<  ite->first;
         cout << "\n\t\t   |------>  " << (*ite->second).nomeNo;
         (*ite->second).imprimirNo();
        // cout << "\n-----------------------------------------------------------------------------\n";
     }
}



