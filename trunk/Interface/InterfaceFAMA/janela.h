#ifndef JANELA_H
#define JANELA_H

#include <QWidget>
#include <QFileDialog>
#include <QTableWidgetItem>
#include <QStandardItem>
#include <QSpinBox>
#include <sstream>
#include <cstdlib>
#include "param.h"
#include "modeloparam.h"
#include "../../corpus/corpusmatriz.h"

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
    Corpus *corpus;
    int indexCorpus;
    QString s;
    Param popUp;

public slots:
    void abrirArquivo();
    void habilitarBotao( int index );
    void atributoSelecionado( int row, int column );
    void definirParametros();
};

#endif // JANELA_H
