#include "classificadorknn.h"
#include <math.h>

//adaptado de http://en.pudn.com/downloads102/sourcecode/chinese/detail417707_en.html

int ClassificadorKNN::AddtoTSet(struct svector v)
{
    if(curTSize>=MAXSZ) {
        ostringstream erro;
        erro << "Conjunto de Dados Inválido";
        throw erro.str();
    }
    trSet[curTSize] = v;
    curTSize++;
    return 1;
}

double ClassificadorKNN::Distance(svector v1, svector v2)
{
    double d = 0.0;
    double tem = 0.0;
    for(int i = 0;i < NATTRS;i++)
        tem += (v1.attributes[i]-v2.attributes[i])*(v1.attributes[i]-v2.attributes[i]);
    d = sqrt(tem);
    return d;
}

int ClassificadorKNN::max(item knn[]){
    int maxNo = 0;
    if(K > 1)
        for(int i = 1;i < K;i++)
            if(knn[i].distance>knn[maxNo].distance)
                maxNo = i;
    return maxNo;
}

double ClassificadorKNN::Classify(svector v){
    double dd = 0;
    int maxn = 0;
    int freq[K];
    double mfreqC = 0, wmfreqC = 0, total = 0;//the class label appears most frequently
    int i;
    for(i = 0;i < K;i++)
        knn[i].distance = MAXVALUE;
    for(i = 0;i < curTSize;i++)
    {
        dd = Distance(trSet[i],v);
        maxn = max(knn);//for every new state of the training set should update maxn
            if(dd < knn[maxn].distance) {
                knn[maxn].distance = dd;
                knn[maxn].classlabel = trSet[i].classlabel;
            }
    }
    for(i = 0;i < K;i++)//freq[i] represents knn[i].classlabel appears how many times
        freq[i] = 1;
    for(i = 0;i < K;i++)
        for(int j = 0;j < K;j++)
            if((i!=j)&&(knn[i].classlabel == knn[j].classlabel))
                freq[i]+=1;
    int mfreq = 1;
    mfreqC = knn[0].classlabel;
    for(i = 0;i < K;i++){
        if (usarPesos){
            if (knn[i].distance){
                wmfreqC += knn[i].distance*knn[i].classlabel;
                total += knn[i].distance;
            }
            else{
                return knn[i].classlabel;
            }
        }

        if(freq[i] > mfreq)  {
            mfreq = freq[i];//mfreq represents the most frepuences
            mfreqC = knn[i].classlabel; //mfreqNo is the item no. with the most frequent
                                         //classlabel
        }
    }

    if (usarPesos)
        return round(wmfreqC/total);
    else
        return mfreqC;
}

bool ClassificadorKNN::inicializarDados( int qtdExemplos ){
    MAXSZ = qtdExemplos;

    if (trSet)
        delete []trSet;

    trSet = new svector[MAXSZ];

    return true;
}

bool ClassificadorKNN::executarClassificacao( Corpus &corpus, int atributo ){

    float val;
    double classlabel;
    struct svector trExmp;
    unsigned int nAtributos, nConjExemplos, nExemplos, a, i, c, e;

    //determina números de conjuntos de exemplos e atributos
    nConjExemplos = corpus.pegarQtdConjExemplos();
    nAtributos = atributos.size();

    //varre atributos
    for (c=0; c < nConjExemplos; c++){
        nExemplos = corpus.pegarQtdExemplos(c);
        for (e=0; e < nExemplos; e++){
            for (a=0; a<nAtributos;a++){
                i = corpus.pegarPosAtributo(atributos[a]);
                (std::istringstream)(corpus(c, e, i)) >> val >> std::dec;//converte para float
                trExmp.attributes[a] = val;
            }
            classlabel = Classify(trExmp);
            //cout << classlabel << endl;
            //for(i = 0;i < K;i++)
            //    cout<<knn[i].distance<<"\t"<<knn[i].classlabel<<endl;

            corpus(c,e,atributo,classes[(int)classlabel]);
        }
    }

/*
    struct vector testv={{142,188,11,1159,0.5513196},17};
    classlabel = Classify(testv);
    cout<<"The classlable of the testv is:    ";
    cout<<classlabel<<endl;
    for(i = 0;i < K;i++)
        cout<<knn[i].distance<<"\t"<<knn[i].classlabel<<endl;
    //cout<<max(knn);
*/
    return true;
}
