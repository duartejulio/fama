#ifndef DADOS_H
#define DADOS_H

#include <QWidget>
#include "../../treinador/treinador.h"
#include "../../avaliador/avaliador.h"

namespace Ui {
class Dados;
}

class Dados : public QWidget
{
    Q_OBJECT
    
public:
    explicit Dados(QWidget *parent = 0);
    ~Dados();
    void definirDados( Treinador *tr, QString nomeTr, int numVal, double infoExtra, Avaliador *av, QString nomeAv, QString atrbTr );
    Treinador* restaurarTreinador();
    Avaliador* restaurarAvaliador();
    int restaurarValidador();
    double restaurarExtra();
    QString restaurarNomeTr();
    QString restaurarNomeAv();
    QString restaurarAtrbTr();
    
private:
    Ui::Dados *ui;
    Treinador *treinador;
    Avaliador *avaliador;
};

#endif // DADOS_H
