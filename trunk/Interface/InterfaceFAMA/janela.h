#ifndef JANELA_H
#define JANELA_H

#include <QWidget>
#include <QFileDialog>
#include <QTableWidgetItem>
#include <sstream>
#include "paramcorpus.h"
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

public slots:
    void abrirArquivo();
    void habilitarBotao( int index );
    void atributoSelecionado( int row, int column );
    void close()
    {
        QWidget::close();
    }
};

#endif // JANELA_H
