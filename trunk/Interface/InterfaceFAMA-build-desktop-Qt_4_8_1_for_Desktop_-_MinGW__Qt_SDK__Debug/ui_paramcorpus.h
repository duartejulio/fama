/********************************************************************************
** Form generated from reading UI file 'paramcorpus.ui'
**
** Created: Sun 19. Aug 16:21:04 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARAMCORPUS_H
#define UI_PARAMCORPUS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpinBox>
#include <QtGui/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_ParamCorpus
{
public:
    QGridLayout *gridLayout;
    QFormLayout *formLayout;
    QLabel *label_separador;
    QComboBox *comboBox_separador;
    QFormLayout *formLayout_2;
    QLabel *label_exemplos;
    QComboBox *comboBox_exemplos;
    QCheckBox *checkBox_atributos;
    QFormLayout *formLayout_3;
    QLabel *label_numAtributos;
    QSpinBox *spinBox_numAtributos;
    QTableWidget *tableWidget_atributos;
    QDialogButtonBox *buttonBox_ok;

    void setupUi(QDialog *ParamCorpus)
    {
        if (ParamCorpus->objectName().isEmpty())
            ParamCorpus->setObjectName(QString::fromUtf8("ParamCorpus"));
        ParamCorpus->resize(236, 324);
        QFont font;
        font.setPointSize(8);
        ParamCorpus->setFont(font);
        ParamCorpus->setSizeGripEnabled(true);
        ParamCorpus->setModal(false);
        gridLayout = new QGridLayout(ParamCorpus);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label_separador = new QLabel(ParamCorpus);
        label_separador->setObjectName(QString::fromUtf8("label_separador"));
        QFont font1;
        font1.setPointSize(9);
        label_separador->setFont(font1);

        formLayout->setWidget(0, QFormLayout::LabelRole, label_separador);

        comboBox_separador = new QComboBox(ParamCorpus);
        comboBox_separador->setObjectName(QString::fromUtf8("comboBox_separador"));
        comboBox_separador->setMaximumSize(QSize(41, 22));
        QFont font2;
        font2.setPointSize(13);
        comboBox_separador->setFont(font2);
        comboBox_separador->setEditable(false);

        formLayout->setWidget(0, QFormLayout::FieldRole, comboBox_separador);


        gridLayout->addLayout(formLayout, 0, 0, 1, 1);

        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        label_exemplos = new QLabel(ParamCorpus);
        label_exemplos->setObjectName(QString::fromUtf8("label_exemplos"));
        label_exemplos->setFont(font1);

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_exemplos);

        comboBox_exemplos = new QComboBox(ParamCorpus);
        comboBox_exemplos->setObjectName(QString::fromUtf8("comboBox_exemplos"));
        comboBox_exemplos->setMaximumSize(QSize(54, 20));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, comboBox_exemplos);


        gridLayout->addLayout(formLayout_2, 1, 0, 1, 1);

        checkBox_atributos = new QCheckBox(ParamCorpus);
        checkBox_atributos->setObjectName(QString::fromUtf8("checkBox_atributos"));
        checkBox_atributos->setFont(font1);
        checkBox_atributos->setChecked(true);

        gridLayout->addWidget(checkBox_atributos, 2, 0, 1, 1);

        formLayout_3 = new QFormLayout();
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        label_numAtributos = new QLabel(ParamCorpus);
        label_numAtributos->setObjectName(QString::fromUtf8("label_numAtributos"));
        label_numAtributos->setFont(font1);

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_numAtributos);

        spinBox_numAtributos = new QSpinBox(ParamCorpus);
        spinBox_numAtributos->setObjectName(QString::fromUtf8("spinBox_numAtributos"));
        spinBox_numAtributos->setEnabled(false);
        spinBox_numAtributos->setMaximumSize(QSize(46, 22));
        spinBox_numAtributos->setReadOnly(false);
        spinBox_numAtributos->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        spinBox_numAtributos->setMinimum(1);

        formLayout_3->setWidget(0, QFormLayout::FieldRole, spinBox_numAtributos);


        gridLayout->addLayout(formLayout_3, 3, 0, 1, 1);

        tableWidget_atributos = new QTableWidget(ParamCorpus);
        if (tableWidget_atributos->columnCount() < 1)
            tableWidget_atributos->setColumnCount(1);
        tableWidget_atributos->setObjectName(QString::fromUtf8("tableWidget_atributos"));
        tableWidget_atributos->setEnabled(false);
        tableWidget_atributos->setEditTriggers(QAbstractItemView::AllEditTriggers);
        tableWidget_atributos->setColumnCount(1);
        tableWidget_atributos->horizontalHeader()->setStretchLastSection(true);

        gridLayout->addWidget(tableWidget_atributos, 4, 0, 1, 1);

        buttonBox_ok = new QDialogButtonBox(ParamCorpus);
        buttonBox_ok->setObjectName(QString::fromUtf8("buttonBox_ok"));
        buttonBox_ok->setOrientation(Qt::Horizontal);
        buttonBox_ok->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox_ok, 5, 0, 1, 1);


        retranslateUi(ParamCorpus);
        QObject::connect(buttonBox_ok, SIGNAL(accepted()), ParamCorpus, SLOT(accept()));
        QObject::connect(buttonBox_ok, SIGNAL(rejected()), ParamCorpus, SLOT(reject()));
        QObject::connect(checkBox_atributos, SIGNAL(clicked(bool)), ParamCorpus, SLOT(escolherAtributos(bool)));
        QObject::connect(spinBox_numAtributos, SIGNAL(valueChanged(int)), ParamCorpus, SLOT(redimensionarTabela(int)));

        QMetaObject::connectSlotsByName(ParamCorpus);
    } // setupUi

    void retranslateUi(QDialog *ParamCorpus)
    {
        ParamCorpus->setWindowTitle(QApplication::translate("ParamCorpus", "Par\303\242metros do CorpusMatriz", 0, QApplication::UnicodeUTF8));
        label_separador->setText(QApplication::translate("ParamCorpus", "Separador:", 0, QApplication::UnicodeUTF8));
        comboBox_separador->clear();
        comboBox_separador->insertItems(0, QStringList()
         << QApplication::translate("ParamCorpus", "_", 0, QApplication::UnicodeUTF8)
         << QString()
        );
        label_exemplos->setText(QApplication::translate("ParamCorpus", "Dividir Exemplos:", 0, QApplication::UnicodeUTF8));
        comboBox_exemplos->clear();
        comboBox_exemplos->insertItems(0, QStringList()
         << QApplication::translate("ParamCorpus", "false", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ParamCorpus", "true", 0, QApplication::UnicodeUTF8)
        );
        checkBox_atributos->setText(QApplication::translate("ParamCorpus", "Atributos autom\303\241ticos", 0, QApplication::UnicodeUTF8));
        label_numAtributos->setText(QApplication::translate("ParamCorpus", "N\302\272 atributos:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ParamCorpus: public Ui_ParamCorpus {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAMCORPUS_H
