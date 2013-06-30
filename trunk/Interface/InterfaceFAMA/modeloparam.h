#ifndef MODELOPARAM_H
#define MODELOPARAM_H

#include <QTableView>
#include <QComboBox>
#include "param.h"

class Param;

class ModeloParam : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ModeloParam(QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const ;
    void inserirDados( int row, int column, std::string v, const QModelIndex &parent = QModelIndex() );
    void inserirDados(int row, int column, Param &ct, QWidget *x, std::string aux = "", const QModelIndex &parent = QModelIndex() );
    bool isWidget(int row, int column);
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
    QComboBox* metodosTreinoDisponiveis();
signals:
    
public slots:

private:
    std::vector< std::vector< std::pair<bool, std::string > > > Dados;
    QComboBox *comboBox_metodosTreino;
    
};

#endif // MODELOPARAM_H
