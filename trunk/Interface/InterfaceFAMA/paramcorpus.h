#ifndef PARAMCORPUS_H
#define PARAMCORPUS_H

#include <QDialog>
#include <vector>

namespace Ui {
class ParamCorpus;
}

class ParamCorpus : public QDialog
{
    Q_OBJECT
    
public:
    explicit ParamCorpus(QWidget *parent = 0);
    ~ParamCorpus();
    char separador;
    bool dividirExemplos;
    std::vector< std::string > atributos;
private:
    Ui::ParamCorpus *ui;

public slots:
    void escolherAtributos(bool state);
    void redimensionarTabela( int i );
    void accept();
};

#endif // PARAMCORPUS_H
