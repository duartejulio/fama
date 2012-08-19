#include "paramcorpus.h"
#include "ui_paramcorpus.h"

ParamCorpus::ParamCorpus(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParamCorpus)
{
    ui->setupUi(this);
    ui->tableWidget_atributos->setHorizontalHeaderLabels( QStringList() << "Atributos" );

    separador = '_';
    dividirExemplos = false;
    atributos = std::vector< std::string >();
}

ParamCorpus::~ParamCorpus()
{
    delete ui;
}

void ParamCorpus::escolherAtributos( bool state )
{
    if( state )
    {
        ui->tableWidget_atributos->clearContents();
        ui->tableWidget_atributos->setEnabled( false );
        ui->spinBox_numAtributos->setValue( 1 );
        ui->spinBox_numAtributos->setEnabled( false );
        atributos.clear();
    }
    else
    {
        ui->tableWidget_atributos->setEnabled( true );
        ui->spinBox_numAtributos->setEnabled( true );
        ui->tableWidget_atributos->setRowCount( 1 );
    }
}

void ParamCorpus::redimensionarTabela( int i )
{
    ui->tableWidget_atributos->setRowCount( i );
}

void ParamCorpus::accept()
{
    if( ui->comboBox_exemplos->currentIndex() ) dividirExemplos = true;
    else dividirExemplos = false;
    separador = ui->comboBox_separador->currentText().toStdString()[0];

    int max = ui->tableWidget_atributos->rowCount();
    for( int i = 0; i < max; ++i )
        atributos.push_back( ui->tableWidget_atributos->item(i,0)->text().toStdString() );

    QDialog::accept();
}
