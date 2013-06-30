#ifndef PARAM_H
#define PARAM_H

#include <QDialog>
#include <QSpinBox>
#include <QFileDialog>
#include <sstream>
#include "modeloparam.h"
#include "../../treinador/maisprovavelui.h"
#include "../../treinador/hmmui.h"
#include "../../treinador/tblui.h"

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
    //slots presentes devido a exigencias da pop-up de parâmetros
    void accept();
    void escolherAtributos( bool state );
    void redimensionarAtributos( int tam );
    void abrirMoldeDeRegras();
    void carregarConhecimentoBLS();
};

#endif // PARAM_H
