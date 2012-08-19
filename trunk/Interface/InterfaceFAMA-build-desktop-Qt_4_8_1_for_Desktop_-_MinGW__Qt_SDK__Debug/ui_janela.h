/********************************************************************************
** Form generated from reading UI file 'janela.ui'
**
** Created: Sun 19. Aug 17:41:36 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JANELA_H
#define UI_JANELA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>
#include "botao.h"

QT_BEGIN_NAMESPACE

class Ui_Janela
{
public:
    QGridLayout *gridLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab_preProcess;
    QGridLayout *gridLayout_5;
    Botao *pushButton_abrir;
    QComboBox *comboBox_corpus;
    QGroupBox *groupBox_relatorioGeral;
    QGridLayout *gridLayout;
    QLabel *label_relatorio;
    QLineEdit *lineEdit_relatorio;
    QLabel *label_instancias;
    QLineEdit *lineEdit_instancias;
    QLabel *label_atributos;
    QLineEdit *lineEdit_atributos;
    QGroupBox *groupBox_atributoSelecionado;
    QGridLayout *gridLayout_4;
    QLabel *label_nome;
    QLineEdit *lineEdit_nome;
    QLabel *label_tipo;
    QLineEdit *lineEdit_tipo;
    QLabel *label_distintos;
    QLineEdit *lineEdit_distintos;
    QLabel *label_unicos;
    QLineEdit *lineEdit_unicos;
    QTableWidget *tableWidget_estatistica;
    QGroupBox *groupBox_atributos;
    QGridLayout *gridLayout_3;
    QTableWidget *tableWidget_atributos;
    QSpacerItem *verticalSpacer_3;
    QWidget *tab_2;

    void setupUi(QWidget *Janela)
    {
        if (Janela->objectName().isEmpty())
            Janela->setObjectName(QString::fromUtf8("Janela"));
        Janela->resize(625, 379);
        gridLayout_2 = new QGridLayout(Janela);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        tabWidget = new QTabWidget(Janela);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QFont font;
        font.setPointSize(9);
        tabWidget->setFont(font);
        tab_preProcess = new QWidget();
        tab_preProcess->setObjectName(QString::fromUtf8("tab_preProcess"));
        gridLayout_5 = new QGridLayout(tab_preProcess);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        pushButton_abrir = new Botao(tab_preProcess);
        pushButton_abrir->setObjectName(QString::fromUtf8("pushButton_abrir"));
        pushButton_abrir->setEnabled(false);
        pushButton_abrir->setMaximumSize(QSize(101, 21));
        QFont font1;
        font1.setItalic(false);
        font1.setUnderline(false);
        font1.setStrikeOut(false);
        pushButton_abrir->setFont(font1);
        pushButton_abrir->setCursor(QCursor(Qt::ArrowCursor));
        pushButton_abrir->setLayoutDirection(Qt::LeftToRight);
        pushButton_abrir->setAutoFillBackground(false);
        pushButton_abrir->setAutoDefault(true);
        pushButton_abrir->setDefault(false);
        pushButton_abrir->setFlat(false);

        gridLayout_5->addWidget(pushButton_abrir, 0, 0, 1, 1);

        comboBox_corpus = new QComboBox(tab_preProcess);
        comboBox_corpus->setObjectName(QString::fromUtf8("comboBox_corpus"));
        comboBox_corpus->setInsertPolicy(QComboBox::InsertAlphabetically);

        gridLayout_5->addWidget(comboBox_corpus, 0, 1, 1, 1);

        groupBox_relatorioGeral = new QGroupBox(tab_preProcess);
        groupBox_relatorioGeral->setObjectName(QString::fromUtf8("groupBox_relatorioGeral"));
        groupBox_relatorioGeral->setMaximumSize(QSize(16777215, 71));
        groupBox_relatorioGeral->setFont(font);
        groupBox_relatorioGeral->setFlat(false);
        groupBox_relatorioGeral->setCheckable(false);
        gridLayout = new QGridLayout(groupBox_relatorioGeral);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_relatorio = new QLabel(groupBox_relatorioGeral);
        label_relatorio->setObjectName(QString::fromUtf8("label_relatorio"));
        QFont font2;
        font2.setPointSize(10);
        label_relatorio->setFont(font2);

        gridLayout->addWidget(label_relatorio, 0, 0, 1, 1);

        lineEdit_relatorio = new QLineEdit(groupBox_relatorioGeral);
        lineEdit_relatorio->setObjectName(QString::fromUtf8("lineEdit_relatorio"));
        lineEdit_relatorio->setEnabled(false);
        QFont font3;
        font3.setBold(false);
        font3.setWeight(50);
        font3.setStrikeOut(false);
        font3.setKerning(true);
        font3.setStyleStrategy(QFont::PreferDefault);
        lineEdit_relatorio->setFont(font3);
        lineEdit_relatorio->setCursor(QCursor(Qt::ArrowCursor));
        lineEdit_relatorio->setFrame(false);

        gridLayout->addWidget(lineEdit_relatorio, 0, 1, 1, 1);

        label_instancias = new QLabel(groupBox_relatorioGeral);
        label_instancias->setObjectName(QString::fromUtf8("label_instancias"));
        label_instancias->setFont(font);

        gridLayout->addWidget(label_instancias, 1, 0, 1, 1);

        lineEdit_instancias = new QLineEdit(groupBox_relatorioGeral);
        lineEdit_instancias->setObjectName(QString::fromUtf8("lineEdit_instancias"));
        lineEdit_instancias->setEnabled(false);
        lineEdit_instancias->setCursor(QCursor(Qt::ArrowCursor));
        lineEdit_instancias->setFrame(false);

        gridLayout->addWidget(lineEdit_instancias, 1, 1, 1, 1);

        label_atributos = new QLabel(groupBox_relatorioGeral);
        label_atributos->setObjectName(QString::fromUtf8("label_atributos"));
        label_atributos->setFont(font);

        gridLayout->addWidget(label_atributos, 1, 2, 1, 1);

        lineEdit_atributos = new QLineEdit(groupBox_relatorioGeral);
        lineEdit_atributos->setObjectName(QString::fromUtf8("lineEdit_atributos"));
        lineEdit_atributos->setEnabled(false);
        lineEdit_atributos->setCursor(QCursor(Qt::ArrowCursor));
        lineEdit_atributos->setFrame(false);

        gridLayout->addWidget(lineEdit_atributos, 1, 3, 1, 1);


        gridLayout_5->addWidget(groupBox_relatorioGeral, 1, 0, 1, 2);

        groupBox_atributoSelecionado = new QGroupBox(tab_preProcess);
        groupBox_atributoSelecionado->setObjectName(QString::fromUtf8("groupBox_atributoSelecionado"));
        groupBox_atributoSelecionado->setFont(font);
        groupBox_atributoSelecionado->setFlat(false);
        groupBox_atributoSelecionado->setCheckable(false);
        gridLayout_4 = new QGridLayout(groupBox_atributoSelecionado);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_nome = new QLabel(groupBox_atributoSelecionado);
        label_nome->setObjectName(QString::fromUtf8("label_nome"));
        label_nome->setMaximumSize(QSize(16777215, 16));
        label_nome->setFont(font2);

        gridLayout_4->addWidget(label_nome, 0, 0, 1, 1);

        lineEdit_nome = new QLineEdit(groupBox_atributoSelecionado);
        lineEdit_nome->setObjectName(QString::fromUtf8("lineEdit_nome"));
        lineEdit_nome->setEnabled(false);
        lineEdit_nome->setMaximumSize(QSize(16777215, 16));
        lineEdit_nome->setFont(font3);
        lineEdit_nome->setCursor(QCursor(Qt::ArrowCursor));
        lineEdit_nome->setFrame(false);

        gridLayout_4->addWidget(lineEdit_nome, 0, 1, 1, 1);

        label_tipo = new QLabel(groupBox_atributoSelecionado);
        label_tipo->setObjectName(QString::fromUtf8("label_tipo"));
        label_tipo->setMaximumSize(QSize(16777215, 16));
        label_tipo->setFont(font);

        gridLayout_4->addWidget(label_tipo, 0, 2, 1, 1);

        lineEdit_tipo = new QLineEdit(groupBox_atributoSelecionado);
        lineEdit_tipo->setObjectName(QString::fromUtf8("lineEdit_tipo"));
        lineEdit_tipo->setEnabled(false);
        lineEdit_tipo->setMaximumSize(QSize(16777215, 16));
        lineEdit_tipo->setFont(font3);
        lineEdit_tipo->setCursor(QCursor(Qt::ArrowCursor));
        lineEdit_tipo->setFrame(false);

        gridLayout_4->addWidget(lineEdit_tipo, 0, 3, 1, 1);

        label_distintos = new QLabel(groupBox_atributoSelecionado);
        label_distintos->setObjectName(QString::fromUtf8("label_distintos"));
        label_distintos->setMaximumSize(QSize(16777215, 16));
        label_distintos->setFont(font);

        gridLayout_4->addWidget(label_distintos, 1, 0, 1, 1);

        lineEdit_distintos = new QLineEdit(groupBox_atributoSelecionado);
        lineEdit_distintos->setObjectName(QString::fromUtf8("lineEdit_distintos"));
        lineEdit_distintos->setEnabled(false);
        lineEdit_distintos->setMaximumSize(QSize(16777215, 16));
        lineEdit_distintos->setCursor(QCursor(Qt::ArrowCursor));
        lineEdit_distintos->setFrame(false);

        gridLayout_4->addWidget(lineEdit_distintos, 1, 1, 1, 1);

        label_unicos = new QLabel(groupBox_atributoSelecionado);
        label_unicos->setObjectName(QString::fromUtf8("label_unicos"));
        label_unicos->setMaximumSize(QSize(16777215, 16));
        label_unicos->setFont(font);

        gridLayout_4->addWidget(label_unicos, 1, 2, 1, 1);

        lineEdit_unicos = new QLineEdit(groupBox_atributoSelecionado);
        lineEdit_unicos->setObjectName(QString::fromUtf8("lineEdit_unicos"));
        lineEdit_unicos->setEnabled(false);
        lineEdit_unicos->setMaximumSize(QSize(16777215, 16));
        lineEdit_unicos->setCursor(QCursor(Qt::ArrowCursor));
        lineEdit_unicos->setFrame(false);

        gridLayout_4->addWidget(lineEdit_unicos, 1, 3, 1, 1);

        tableWidget_estatistica = new QTableWidget(groupBox_atributoSelecionado);
        tableWidget_estatistica->setObjectName(QString::fromUtf8("tableWidget_estatistica"));
        tableWidget_estatistica->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget_estatistica->setTabKeyNavigation(false);
        tableWidget_estatistica->setAlternatingRowColors(true);
        tableWidget_estatistica->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget_estatistica->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget_estatistica->setShowGrid(false);
        tableWidget_estatistica->setSortingEnabled(true);
        tableWidget_estatistica->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidget_estatistica->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        tableWidget_estatistica->horizontalHeader()->setStretchLastSection(true);
        tableWidget_estatistica->verticalHeader()->setVisible(false);

        gridLayout_4->addWidget(tableWidget_estatistica, 2, 0, 1, 4);


        gridLayout_5->addWidget(groupBox_atributoSelecionado, 1, 2, 2, 1);

        groupBox_atributos = new QGroupBox(tab_preProcess);
        groupBox_atributos->setObjectName(QString::fromUtf8("groupBox_atributos"));
        groupBox_atributos->setFont(font);
        gridLayout_3 = new QGridLayout(groupBox_atributos);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        tableWidget_atributos = new QTableWidget(groupBox_atributos);
        if (tableWidget_atributos->columnCount() < 2)
            tableWidget_atributos->setColumnCount(2);
        tableWidget_atributos->setObjectName(QString::fromUtf8("tableWidget_atributos"));
        tableWidget_atributos->setLayoutDirection(Qt::LeftToRight);
        tableWidget_atributos->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget_atributos->setTabKeyNavigation(false);
        tableWidget_atributos->setAlternatingRowColors(true);
        tableWidget_atributos->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget_atributos->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget_atributos->setShowGrid(false);
        tableWidget_atributos->setSortingEnabled(true);
        tableWidget_atributos->setColumnCount(2);
        tableWidget_atributos->horizontalHeader()->setStretchLastSection(true);
        tableWidget_atributos->verticalHeader()->setVisible(false);

        gridLayout_3->addWidget(tableWidget_atributos, 0, 0, 1, 1);


        gridLayout_5->addWidget(groupBox_atributos, 2, 0, 2, 2);

        verticalSpacer_3 = new QSpacerItem(20, 108, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

        gridLayout_5->addItem(verticalSpacer_3, 3, 2, 1, 1);

        tabWidget->addTab(tab_preProcess, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());

        gridLayout_2->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(Janela);
        QObject::connect(pushButton_abrir, SIGNAL(clicked()), Janela, SLOT(abrirArquivo()));
        QObject::connect(comboBox_corpus, SIGNAL(activated(int)), pushButton_abrir, SLOT(habilitarBotao(int)));
        QObject::connect(comboBox_corpus, SIGNAL(activated(int)), Janela, SLOT(habilitarBotao(int)));
        QObject::connect(tableWidget_atributos, SIGNAL(cellClicked(int,int)), Janela, SLOT(atributoSelecionado(int,int)));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Janela);
    } // setupUi

    void retranslateUi(QWidget *Janela)
    {
        Janela->setWindowTitle(QApplication::translate("Janela", "FAMA", 0, QApplication::UnicodeUTF8));
        pushButton_abrir->setText(QApplication::translate("Janela", "Abrir arquivo...", 0, QApplication::UnicodeUTF8));
        comboBox_corpus->clear();
        comboBox_corpus->insertItems(0, QStringList()
         << QApplication::translate("Janela", "Escolha o Corpus", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Janela", "CorpusMatriz", 0, QApplication::UnicodeUTF8)
        );
        groupBox_relatorioGeral->setTitle(QApplication::translate("Janela", "Relat\303\263rio geral", 0, QApplication::UnicodeUTF8));
        label_relatorio->setText(QApplication::translate("Janela", "  Relat\303\263rio:", 0, QApplication::UnicodeUTF8));
        lineEdit_relatorio->setText(QApplication::translate("Janela", "Nenhum", 0, QApplication::UnicodeUTF8));
        label_instancias->setText(QApplication::translate("Janela", "  Inst\303\242ncias:", 0, QApplication::UnicodeUTF8));
        lineEdit_instancias->setText(QApplication::translate("Janela", "Nenhum", 0, QApplication::UnicodeUTF8));
        label_atributos->setText(QApplication::translate("Janela", "Atributos:", 0, QApplication::UnicodeUTF8));
        lineEdit_atributos->setText(QApplication::translate("Janela", "Nenhum", 0, QApplication::UnicodeUTF8));
        groupBox_atributoSelecionado->setTitle(QApplication::translate("Janela", "Atributo selecionado", 0, QApplication::UnicodeUTF8));
        label_nome->setText(QApplication::translate("Janela", "     Nome:", 0, QApplication::UnicodeUTF8));
        lineEdit_nome->setText(QApplication::translate("Janela", "Nenhum", 0, QApplication::UnicodeUTF8));
        label_tipo->setText(QApplication::translate("Janela", "Tipo:", 0, QApplication::UnicodeUTF8));
        lineEdit_tipo->setText(QApplication::translate("Janela", "Nenhum", 0, QApplication::UnicodeUTF8));
        label_distintos->setText(QApplication::translate("Janela", "  Distintos:", 0, QApplication::UnicodeUTF8));
        lineEdit_distintos->setText(QApplication::translate("Janela", "Nenhum", 0, QApplication::UnicodeUTF8));
        label_unicos->setText(QApplication::translate("Janela", "\303\232nicos:", 0, QApplication::UnicodeUTF8));
        lineEdit_unicos->setText(QApplication::translate("Janela", "Nenhum", 0, QApplication::UnicodeUTF8));
        groupBox_atributos->setTitle(QApplication::translate("Janela", "Atributos", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_preProcess), QApplication::translate("Janela", "Pr\303\251-processamento", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Janela", "Tab 2", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Janela: public Ui_Janela {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JANELA_H
