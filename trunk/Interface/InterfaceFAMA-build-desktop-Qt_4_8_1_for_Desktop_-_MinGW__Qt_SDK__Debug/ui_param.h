/********************************************************************************
** Form generated from reading UI file 'param.ui'
**
** Created: Thu 6. Sep 08:38:05 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARAM_H
#define UI_PARAM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QTableView>

QT_BEGIN_NAMESPACE

class Ui_Param
{
public:
    QGridLayout *gridLayout;
    QTableView *tableView;
    QDialogButtonBox *buttonBox_ok;

    void setupUi(QDialog *Param)
    {
        if (Param->objectName().isEmpty())
            Param->setObjectName(QString::fromUtf8("Param"));
        Param->resize(230, 305);
        gridLayout = new QGridLayout(Param);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tableView = new QTableView(Param);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setEditTriggers(QAbstractItemView::AllEditTriggers);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        tableView->horizontalHeader()->setVisible(false);
        tableView->horizontalHeader()->setStretchLastSection(true);
        tableView->verticalHeader()->setVisible(false);

        gridLayout->addWidget(tableView, 0, 0, 1, 1);

        buttonBox_ok = new QDialogButtonBox(Param);
        buttonBox_ok->setObjectName(QString::fromUtf8("buttonBox_ok"));
        buttonBox_ok->setOrientation(Qt::Horizontal);
        buttonBox_ok->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox_ok, 1, 0, 1, 1);


        retranslateUi(Param);
        QObject::connect(buttonBox_ok, SIGNAL(accepted()), Param, SLOT(accept()));
        QObject::connect(buttonBox_ok, SIGNAL(rejected()), Param, SLOT(reject()));

        QMetaObject::connectSlotsByName(Param);
    } // setupUi

    void retranslateUi(QDialog *Param)
    {
        Param->setWindowTitle(QApplication::translate("Param", "Par\303\242metros", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Param: public Ui_Param {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAM_H
