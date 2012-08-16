#ifndef JANELA_H
#define JANELA_H

#include <QWidget>
#include <QFileDialog>
#include <sstream>
#include "corpusmatriz.h"

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

public slots:
    void abrirArquivo();
};

#endif // JANELA_H
