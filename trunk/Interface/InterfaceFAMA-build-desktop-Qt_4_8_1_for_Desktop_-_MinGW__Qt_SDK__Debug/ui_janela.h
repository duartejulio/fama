/********************************************************************************
** Form generated from reading UI file 'janela.ui'
**
** Created: Sun 24. Feb 12:56:57 2013
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
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Janela
{
public:
    QTabWidget *tabWidget;
    QWidget *tab_preProcess;
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
    QToolButton *toolButton_construtor;
    QPushButton *pushButton_abrir;
    QWidget *tab_2;

    void setupUi(QWidget *Janela)
    {
        if (Janela->objectName().isEmpty())
            Janela->setObjectName(QString::fromUtf8("Janela"));
        Janela->resize(625, 379);
        tabWidget = new QTabWidget(Janela);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(9, 9, 607, 361));
        QFont font;
        font.setPointSize(9);
        tabWidget->setFont(font);
        tab_preProcess = new QWidget();
        tab_preProcess->setObjectName(QString::fromUtf8("tab_preProcess"));
        comboBox_corpus = new QComboBox(tab_preProcess);
        comboBox_corpus->setObjectName(QString::fromUtf8("comboBox_corpus"));
        comboBox_corpus->setGeometry(QRect(107, 9, 171, 20));
        comboBox_corpus->setInsertPolicy(QComboBox::InsertAlphabetically);
        groupBox_relatorioGeral = new QGroupBox(tab_preProcess);
        groupBox_relatorioGeral->setObjectName(QString::fromUtf8("groupBox_relatorioGeral"));
        groupBox_relatorioGeral->setGeometry(QRect(9, 36, 296, 71));
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
        QFont font1;
        font1.setPointSize(10);
        label_relatorio->setFont(font1);

        gridLayout->addWidget(label_relatorio, 0, 0, 1, 1);

        lineEdit_relatorio = new QLineEdit(groupBox_relatorioGeral);
        lineEdit_relatorio->setObjectName(QString::fromUtf8("lineEdit_relatorio"));
        lineEdit_relatorio->setEnabled(false);
        QFont font2;
        font2.setBold(false);
        font2.setWeight(50);
        font2.setStrikeOut(false);
        font2.setKerning(true);
        font2.setStyleStrategy(QFont::PreferDefault);
        lineEdit_relatorio->setFont(font2);
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

        groupBox_atributoSelecionado = new QGroupBox(tab_preProcess);
        groupBox_atributoSelecionado->setObjectName(QString::fromUtf8("groupBox_atributoSelecionado"));
        groupBox_atributoSelecionado->setGeometry(QRect(311, 36, 283, 265));
        groupBox_atributoSelecionado->setFont(font);
        groupBox_atributoSelecionado->setFlat(false);
        groupBox_atributoSelecionado->setCheckable(false);
        label_nome = new QLabel(groupBox_atributoSelecionado);
        label_nome->setObjectName(QString::fromUtf8("label_nome"));
        label_nome->setGeometry(QRect(11, 25, 58, 16));
        label_nome->setMaximumSize(QSize(16777215, 16));
        label_nome->setFont(font1);
        lineEdit_nome = new QLineEdit(groupBox_atributoSelecionado);
        lineEdit_nome->setObjectName(QString::fromUtf8("lineEdit_nome"));
        lineEdit_nome->setEnabled(false);
        lineEdit_nome->setGeometry(QRect(75, 25, 73, 16));
        lineEdit_nome->setMaximumSize(QSize(16777215, 16));
        lineEdit_nome->setFont(font2);
        lineEdit_nome->setCursor(QCursor(Qt::ArrowCursor));
        lineEdit_nome->setFrame(false);
        label_tipo = new QLabel(groupBox_atributoSelecionado);
        label_tipo->setObjectName(QString::fromUtf8("label_tipo"));
        label_tipo->setGeometry(QRect(154, 25, 28, 16));
        label_tipo->setMaximumSize(QSize(16777215, 16));
        label_tipo->setFont(font);
        lineEdit_tipo = new QLineEdit(groupBox_atributoSelecionado);
        lineEdit_tipo->setObjectName(QString::fromUtf8("lineEdit_tipo"));
        lineEdit_tipo->setEnabled(false);
        lineEdit_tipo->setGeometry(QRect(199, 25, 73, 16));
        lineEdit_tipo->setMaximumSize(QSize(16777215, 16));
        lineEdit_tipo->setFont(font2);
        lineEdit_tipo->setCursor(QCursor(Qt::ArrowCursor));
        lineEdit_tipo->setFrame(false);
        label_distintos = new QLabel(groupBox_atributoSelecionado);
        label_distintos->setObjectName(QString::fromUtf8("label_distintos"));
        label_distintos->setGeometry(QRect(11, 47, 58, 16));
        label_distintos->setMaximumSize(QSize(16777215, 16));
        label_distintos->setFont(font);
        lineEdit_distintos = new QLineEdit(groupBox_atributoSelecionado);
        lineEdit_distintos->setObjectName(QString::fromUtf8("lineEdit_distintos"));
        lineEdit_distintos->setEnabled(false);
        lineEdit_distintos->setGeometry(QRect(75, 47, 73, 16));
        lineEdit_distintos->setMaximumSize(QSize(16777215, 16));
        lineEdit_distintos->setCursor(QCursor(Qt::ArrowCursor));
        lineEdit_distintos->setFrame(false);
        label_unicos = new QLabel(groupBox_atributoSelecionado);
        label_unicos->setObjectName(QString::fromUtf8("label_unicos"));
        label_unicos->setGeometry(QRect(154, 47, 39, 16));
        label_unicos->setMaximumSize(QSize(16777215, 16));
        label_unicos->setFont(font);
        lineEdit_unicos = new QLineEdit(groupBox_atributoSelecionado);
        lineEdit_unicos->setObjectName(QString::fromUtf8("lineEdit_unicos"));
        lineEdit_unicos->setEnabled(false);
        lineEdit_unicos->setGeometry(QRect(199, 47, 73, 16));
        lineEdit_unicos->setMaximumSize(QSize(16777215, 16));
        lineEdit_unicos->setCursor(QCursor(Qt::ArrowCursor));
        lineEdit_unicos->setFrame(false);
        tableWidget_estatistica = new QTableWidget(groupBox_atributoSelecionado);
        tableWidget_estatistica->setObjectName(QString::fromUtf8("tableWidget_estatistica"));
        tableWidget_estatistica->setGeometry(QRect(11, 69, 261, 185));
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
        groupBox_atributos = new QGroupBox(tab_preProcess);
        groupBox_atributos->setObjectName(QString::fromUtf8("groupBox_atributos"));
        groupBox_atributos->setGeometry(QRect(9, 113, 296, 215));
        groupBox_atributos->setFont(font);
        gridLayout_3 = new QGridLayout(groupBox_atributos);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        tableWidget_atributos = new QTableWidget(groupBox_atributos);
        if (tableWidget_atributos->columnCount() < 2)
            tableWidget_atributos->setColumnCount(2);
        tableWidget_atributos->setObjectName(QString::fromUtf8("tableWidget_atributos"));
        QFont font3;
        font3.setPointSize(8);
        tableWidget_atributos->setFont(font3);
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
        tableWidget_atributos->verticalHeader()->setDefaultSectionSize(17);

        gridLayout_3->addWidget(tableWidget_atributos, 0, 0, 1, 1);

        toolButton_construtor = new QToolButton(tab_preProcess);
        toolButton_construtor->setObjectName(QString::fromUtf8("toolButton_construtor"));
        toolButton_construtor->setEnabled(false);
        toolButton_construtor->setGeometry(QRect(280, 10, 25, 19));
        pushButton_abrir = new QPushButton(tab_preProcess);
        pushButton_abrir->setObjectName(QString::fromUtf8("pushButton_abrir"));
        pushButton_abrir->setEnabled(false);
        pushButton_abrir->setGeometry(QRect(10, 10, 92, 21));
        pushButton_abrir->setMaximumSize(QSize(101, 21));
        QFont font4;
        font4.setItalic(false);
        font4.setUnderline(false);
        font4.setStrikeOut(false);
        pushButton_abrir->setFont(font4);
        pushButton_abrir->setCursor(QCursor(Qt::ArrowCursor));
        pushButton_abrir->setLayoutDirection(Qt::LeftToRight);
        pushButton_abrir->setAutoFillBackground(false);
        pushButton_abrir->setAutoDefault(true);
        pushButton_abrir->setDefault(false);
        pushButton_abrir->setFlat(false);
        tabWidget->addTab(tab_preProcess, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());

        retranslateUi(Janela);
        QObject::connect(tableWidget_atributos, SIGNAL(cellClicked(int,int)), Janela, SLOT(atributoSelecionado(int,int)));
        QObject::connect(comboBox_corpus, SIGNAL(activated(int)), Janela, SLOT(habilitarBotao(int)));
        QObject::connect(toolButton_construtor, SIGNAL(clicked()), Janela, SLOT(definirParametros()));
        QObject::connect(pushButton_abrir, SIGNAL(clicked()), Janela, SLOT(abrirArquivo()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Janela);
    } // setupUi

    void retranslateUi(QWidget *Janela)
    {
        Janela->setWindowTitle(QApplication::translate("Janela", "FAMA", 0, QApplication::UnicodeUTF8));
        comboBox_corpus->clear();
        comboBox_corpus->insertItems(0, QStringList()
         << QApplication::translate("Janela", "Escolha o Corpus", 0, QApplication::UnicodeUTF8)
        );
        groupBox_relatorioGeral->setTitle(QApplication::translate("Janela", "Corpus", 0, QApplication::UnicodeUTF8));
        label_relatorio->setText(QApplication::translate("Janela", "       Nome:", 0, QApplication::UnicodeUTF8));
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
        toolButton_construtor->setText(QApplication::translate("Janela", "...", 0, QApplication::UnicodeUTF8));
        pushButton_abrir->setText(QApplication::translate("Janela", "Abrir arquivo...", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_preProcess), QApplication::translate("Janela", "Pr\303\251-processamento", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Janela", "Tab 2", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Janela: public Ui_Janela {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JANELA_H
