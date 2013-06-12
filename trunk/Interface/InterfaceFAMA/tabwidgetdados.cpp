#include "tabwidgetdados.h"

TabWidgetDados::TabWidgetDados(QWidget *parent) :
    QTableWidget(parent)
{
    //criação dos itens que estarão no menu do botão direito na tabela de resultados da validação
    exportarValidacao = new QAction( "Validação", this );
    exportarTreinamento = new QAction( "Treinamento", this );
    //apagarExperimento = new QAction( "Apagar Experimento", this );

    //alocação de eventos
    connect( exportarValidacao, SIGNAL( triggered() ), this, SLOT( exportarDadosValidacao() ) );
    connect( exportarTreinamento, SIGNAL( triggered() ), this, SLOT( exportarDadosTreinamento() ) );
    //connect( apagarExperimento, SIGNAL( triggered() ), this, SLOT( apagarExperimentoAtual() ) );
}

void TabWidgetDados::definirDados( Treinador *tr, QString nomeTr, int numVal, Avaliador *av, QString nomeAv, QString atrbTr, double infoExtra )
{
    vetTreinador.push_back( tr );
    nomeTreinador.push_back( nomeTr );
    numValidacao.push_back( numVal );
    vetAvaliador.push_back( av );
    nomeAvaliador.push_back( nomeAv );
    atributoTreino.push_back( atrbTr );
    informacaoExtra.push_back( infoExtra );
}

bool TabWidgetDados::pertenceTreinador( Treinador *tr )
{
    int i, tam_treinador = vetTreinador.size();

    for( i = 0; i < tam_treinador; ++i )
        if( vetTreinador[i] == tr ) return true;

    return false;
}

bool TabWidgetDados::pertenceAvaliador( Avaliador *av )
{
    int i, tam_avaliador = vetAvaliador.size();

    for( i = 0; i < tam_avaliador; ++i )
        if( vetAvaliador[i] == av ) return true;

    return false;
}

void TabWidgetDados::clear( Treinador *tr, Treinador *tr2, Avaliador *av )
{
    int i, tamMax = vetTreinador.size();

    for( i = 0; i < tamMax; ++i )
        if( vetTreinador[i] != tr && vetTreinador[i] != tr2 ) delete vetTreinador[i];
    for( i = 0; i < tamMax; ++i )
        if( vetAvaliador[i] != av ) delete vetAvaliador[i];

    vetTreinador.clear();
    vetAvaliador.clear();
    nomeTreinador.clear();
    nomeAvaliador.clear();
    atributoTreino.clear();
    numValidacao.clear();
    informacaoExtra.clear();
}

Treinador* TabWidgetDados::restaurarTreinador( int indiceExperimento )
{
    return vetTreinador[indiceExperimento];
}

Avaliador* TabWidgetDados::restaurarAvaliador( int indiceExperimento )
{
    return vetAvaliador[indiceExperimento];
}

int TabWidgetDados::restaurarValidador( int indiceExperimento )
{
    return numValidacao[indiceExperimento];
}

double TabWidgetDados::restaurarExtra( int indiceExperimento )
{
    return informacaoExtra[indiceExperimento];
}

QString TabWidgetDados::restaurarNomeTr( int indiceExperimento )
{
    return nomeTreinador[indiceExperimento];
}

QString TabWidgetDados::restaurarNomeAv( int indiceExperimento )
{
    return nomeAvaliador[indiceExperimento];
}

QString TabWidgetDados::restaurarAtrbTr( int indiceExperimento )
{
    return atributoTreino[indiceExperimento];
}

void TabWidgetDados::contextMenuEvent( QContextMenuEvent * event )
{
    //não aparece menu quando não ha validação
    if( vetTreinador.empty() ) return;

    QMenu menu( this ), *subMenuExportar;

    subMenuExportar = menu.addMenu( "Exportar Dados" );
    subMenuExportar->addAction( exportarValidacao );
    subMenuExportar->addAction( exportarTreinamento );
    //menu.addSeparator();
    //menu.addAction( apagarExperimento );
    menu.exec( event->globalPos() );
}

void TabWidgetDados::exportarDadosValidacao()
{
    sendImportarDados( currentRow() );
}

void TabWidgetDados::exportarDadosTreinamento()
{
    sendImportarDadosAba3( currentRow() );
}

/*void TabWidgetDados::apagarExperimentoAtual()
{
    sendLimparExperimento( currentRow() );
}*/
