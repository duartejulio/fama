#ifndef PARAM_H
#define PARAM_H

#include <QDialog>
#include <QSpinBox>
#include <sstream>
#include "modeloparam.h"

namespace Ui {
class Param;
}

class Param : public QDialog
{
    Q_OBJECT
    
public:
    explicit Param(QWidget *parent = 0);
    ~Param();
    void ajustarModelo( QAbstractItemModel &m );
    int iniciarDialog();
    std::string pegarString( int row );
    QWidget *pegarWidget( int row );

    std::vector< std::pair< std::string, QWidget* > > parametros;
private:
    Ui::Param *ui;
    QTableView* pegarView();

    friend class ModeloParam;

public slots:
    void accept();
    void escolherAtributos( bool state );
    void redimensionarAtributos( int tam );
};

#endif // PARAM_H
