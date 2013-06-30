#include "tblui.h"
#include <QMessageBox>

TBLUI::TBLUI( Classificador* classInicial, string arqMoldeRegras, string atributoChute, int toleranciaScore )
    : TBL( classInicial, arqMoldeRegras, atributoChute, toleranciaScore )
{
}

Treinador* TBLUI::construirJanela( void *popUp, Corpus &corpus )
{
    Param *popUpPointer = ( Param * )popUp;
    ModeloParam model;
    int ok;

    model.inserirDados( 0, 0, "Classificador Inicial (BLS):" );
    model.inserirDados( 1, 0, "Arquivo de conhecimento:" );
    model.inserirDados( 1, 1, "C:\\" );
    model.inserirDados( 2, 0, "Carregar arquivo:" );
    model.inserirDados( 3, 0, "Arquivo de molde de regras:" );
    model.inserirDados( 3, 1, "C:\\" );
    model.inserirDados( 4, 0, "Escolher arquivo:" );
    model.inserirDados( 5, 0, "Nome do novo atributo criado no Class. Ini." );
    model.inserirDados( 5, 1, " " );
    model.inserirDados( 6, 0, "Score máximo de regra aceita" );

    popUpPointer->ajustarModelo( model );

    //inserção Widgets
    model.inserirDados( 0, 1, *popUpPointer, model.metodosTreinoDisponiveis() );

    QIcon icon;
    icon.addFile( QString::fromUtf8("../imagens/folder_open.png"), QSize(), QIcon::Normal, QIcon::Off );

    QPushButton *pButton = new QPushButton();
    pButton->setIcon( icon );
    model.inserirDados( 2, 1, *popUpPointer, pButton );

    QPushButton *pushButton = new QPushButton();
    pushButton->setIcon( icon );
    model.inserirDados( 4, 1, *popUpPointer, pushButton );

    QSpinBox *sBox = new QSpinBox();
    sBox->setValue( 2 );
    sBox->setMinimum( 1 );
    model.inserirDados( 6, 1, *popUpPointer, sBox );

    //inserção de Evento(slot deve estar no Widget ou na classe Param)
    QObject::connect( pushButton, SIGNAL( clicked() ), popUpPointer, SLOT( abrirMoldeDeRegras() ) );
    QObject::connect( pButton, SIGNAL( clicked() ), popUpPointer, SLOT( carregarConhecimentoBLS() ) );
    QMetaObject::connectSlotsByName( popUpPointer );

    ok = popUpPointer->iniciarDialog();

    //QMessageBox::about( popUpPointer, "Erro", "Tente com outro nome de atributo." );

    if( ok )
    {
        Classificador *classificador;

        switch( ( ( QComboBox* ) popUpPointer->pegarWidget( 0 ) )->currentIndex() )
        {
            case 0:
                classificador = new ClassificadorMaisProvavel( popUpPointer->pegarString( 1 ) );
                break;
            case 1:
                classificador = new ClassificadorHMM( popUpPointer->pegarString( 1 ) );
                break;
            case 2:
                //esse código só pode ser liberado após o conhecimento do BLS tbm ser gravado no TBL
                //classificador = new ClassificadorTBL( popUpPointer->pegarString( 1 ) );
                break;
        }

        Treinador *treinador = new TBL( classificador, popUpPointer->pegarString( 3 ), popUpPointer->pegarString( 5 ), sBox->value() );
        return treinador;
    }
    return this;
}
