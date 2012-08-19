#ifndef BOTAO_H
#define BOTAO_H

#include <QWidget>
#include <QPushButton>

class Botao : public QPushButton
{
    Q_OBJECT
public:
    explicit Botao(QWidget *parent = 0);
    
signals:
    
public slots:
    void habilitarBotao(int index);
    
};

#endif // BOTAO_H
