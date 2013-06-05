#include "dados.h"
#include "ui_dados.h"

Dados::Dados(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Dados)
{
    ui->setupUi(this);

    treinador = NULL;
    avaliador = NULL;
}

Dados::~Dados()
{
    delete ui;
}

void Dados::definirDados( Treinador *tr, QString nomeTr, int numVal, double infoExtra, Avaliador *av, QString nomeAv, QString atrbTr )
{
    treinador = tr;
    ui->lineEdit_treinador->setText( nomeTr );
    ui->comboBox_validacao->setCurrentIndex( numVal );
    if( infoExtra == -1 ) ui->doubleSpinBox_extra->setValue( 0 );
    else ui->doubleSpinBox_extra->setValue( infoExtra );
    avaliador = av;
    ui->lineEdit_avaliador->setText( nomeAv );
    ui->lineEdit_atributo->setText( atrbTr );
}

Treinador* Dados::restaurarTreinador()
{
    return treinador;
}

Avaliador* Dados::restaurarAvaliador()
{
    return avaliador;
}

int Dados::restaurarValidador()
{
    return ui->comboBox_validacao->currentIndex();
}

double Dados::restaurarExtra()
{
    return ui->doubleSpinBox_extra->value();
}

QString Dados::restaurarNomeTr()
{
    return ui->lineEdit_treinador->text();
}

QString Dados::restaurarNomeAv()
{
    return ui->lineEdit_avaliador->text();
}

QString Dados::restaurarAtrbTr()
{
    return ui->lineEdit_atributo->text();
}
