#include "botao.h"

Botao::Botao(QWidget *parent) :
    QPushButton(parent)
{
}

void Botao::habilitarBotao( int index )
{
    if( index )
        setEnabled( true );
}
