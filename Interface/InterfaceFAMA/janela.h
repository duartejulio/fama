#ifndef JANELA_H
#define JANELA_H


#include <QFileDialog>
#include "param.h"
#include "../../corpusInterface/corpusmatriz.h"

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
    QString s;
    Param popUp;
    void logicaDeAbertura();

public slots:
    void abrirArquivo();
    void habilitarBotao( int index );
    void atributoSelecionado( int row, int column );
    void definirParametros();
};

#endif // JANELA_H
