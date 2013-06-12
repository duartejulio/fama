#ifndef TABWIDGETDADOS_H
#define TABWIDGETDADOS_H

#include <QTableWidget>
#include <QAction>
#include <QMenu>
#include <QContextMenuEvent>
#include "../../treinador/treinador.h"
#include "../../avaliador/avaliador.h"

class TabWidgetDados : public QTableWidget
{
    Q_OBJECT
public:
    explicit TabWidgetDados(QWidget *parent = 0);
    void definirDados( Treinador *tr, QString nomeTr, int numVal, Avaliador *av, QString nomeAv, QString atrbTr, double infoExtra = .0 );
    bool pertenceTreinador( Treinador *tr );
    bool pertenceAvaliador( Avaliador *av );
    void clear( Treinador *tr, Treinador *tr2, Avaliador *av );
    Treinador* restaurarTreinador( int indiceExperimento );
    Avaliador* restaurarAvaliador( int indiceExperimento );
    int restaurarValidador( int indiceExperimento );
    double restaurarExtra( int indiceExperimento );
    QString restaurarNomeTr( int indiceExperimento );
    QString restaurarNomeAv( int indiceExperimento );
    QString restaurarAtrbTr( int indiceExperimento );
    void contextMenuEvent( QContextMenuEvent * event );

signals:
    void sendImportarDados( int index );
    void sendImportarDadosAba3( int index );
    //void sendLimparExperimento( int index );
    
public slots:
    void exportarDadosValidacao();
    void exportarDadosTreinamento();
    //void apagarExperimentoAtual();

private:
    vector< Treinador* > vetTreinador;
    vector< Avaliador* > vetAvaliador;
    vector< QString > nomeTreinador, nomeAvaliador, atributoTreino;
    vector< int > numValidacao;
    vector< double > informacaoExtra;
    QAction *exportarValidacao, *exportarTreinamento, *apagarExperimento;
    
};

#endif // TABWIDGETDADOS_H
