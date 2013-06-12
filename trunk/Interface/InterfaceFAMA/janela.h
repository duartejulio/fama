#ifndef JANELA_H
#define JANELA_H


#include <QFileDialog>
#include <QMessageBox>
#include "param.h"
#include "../../corpus/corpusmatrizui.h"
#include "../../treinador/maisprovavelui.h"
#include "../../treinador/hmmui.h"
#include "../../treinador/tblui.h"
#include "../../validador/validadorteste.h"
#include "../../validador/validadortreino.h"
#include "../../validador/validadorkdobras.h"
#include "../../validador/validadordivisao.h"
#include "../../avaliador/avaliador_acuracia.h"


namespace Ui {
class Janela;
}

class Janela : public QWidget
{
    Q_OBJECT

public:
    explicit Janela(QWidget *parent = 0);
    ~Janela();

private:
    Ui::Janela *ui;
    Corpus *corpus, *corpusTeste;
    Treinador *treinador, *treinadorAba3;
    Classificador *classificador;
    Avaliador *avaliador;
    QString s;
    Param popUp;
    int numExperimento;
    void logicaDeAbertura();
    bool importado; //variavel auxiliar que descreve quando um dado é importado
    vector< int > vetExperimentos;

public slots:
    void abrirArquivo();
    void abrirArquivoTeste();
    void habilitarBotao( int index );
    void atributoSelecionado( int row, int column );
    void definirParametros();
    void escolherMetodo( int index );
    void escolherTreinador( int index );
    void escolherClassificador( int index );
    void escolherAvaliador( int index );
    void definirParametrosTreinador();
    void definirParametrosTreinadorAba3();
    void executarValidacao();
    void guardarConhecimento();
    void carregarConhecimento();
    void treinar();
    void classificar();
    void gravarCorpus();
    void importarDados( int index );
    void importarDadosAba3( int index );
    void limparValidacao();
    //void limparExperimento(int index);
};

#endif // JANELA_H
