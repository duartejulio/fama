/********************************************************************************
** Form generated from reading UI file 'janela.ui'
**
** Created: Thu 16. Aug 00:19:56 2012
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
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Janela
{
public:
    QGridLayout *gridLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab_preProcess;
    QPushButton *pushButton_abrir;
    QGroupBox *groupBox_relatorioGeral;
    QGridLayout *gridLayout;
    QLabel *label_relatorio;
    QLineEdit *lineEdit_relatorio;
    QLabel *label_instancias;
    QLabel *label_atributos;
    QLineEdit *lineEdit_atributos;
    QLineEdit *lineEdit_instancias;
    QGroupBox *groupBox_atributos;
    QLineEdit *lineEdit_todosAtributos;
    QLineEdit *lineEdit_5;
    QWidget *tab_2;

    void setupUi(QWidget *Janela)
    {
        if (Janela->objectName().isEmpty())
            Janela->setObjectName(QString::fromUtf8("Janela"));
        Janela->resize(498, 379);
        gridLayout_2 = new QGridLayout(Janela);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        tabWidget = new QTabWidget(Janela);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab_preProcess = new QWidget();
        tab_preProcess->setObjectName(QString::fromUtf8("tab_preProcess"));
        pushButton_abrir = new QPushButton(tab_preProcess);
        pushButton_abrir->setObjectName(QString::fromUtf8("pushButton_abrir"));
        pushButton_abrir->setGeometry(QRect(10, 10, 101, 21));
        pushButton_abrir->setMaximumSize(QSize(101, 21));
        QFont font;
        font.setItalic(false);
        font.setUnderline(false);
        font.setStrikeOut(false);
        pushButton_abrir->setFont(font);
        pushButton_abrir->setCursor(QCursor(Qt::ArrowCursor));
        pushButton_abrir->setLayoutDirection(Qt::LeftToRight);
        pushButton_abrir->setAutoFillBackground(false);
        pushButton_abrir->setAutoDefault(true);
        pushButton_abrir->setDefault(false);
        pushButton_abrir->setFlat(false);
        groupBox_relatorioGeral = new QGroupBox(tab_preProcess);
        groupBox_relatorioGeral->setObjectName(QString::fromUtf8("groupBox_relatorioGeral"));
        groupBox_relatorioGeral->setGeometry(QRect(10, 40, 241, 71));
        groupBox_relatorioGeral->setFlat(false);
        groupBox_relatorioGeral->setCheckable(false);
        gridLayout = new QGridLayout(groupBox_relatorioGeral);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_relatorio = new QLabel(groupBox_relatorioGeral);
        label_relatorio->setObjectName(QString::fromUtf8("label_relatorio"));

        gridLayout->addWidget(label_relatorio, 0, 0, 1, 1);

        lineEdit_relatorio = new QLineEdit(groupBox_relatorioGeral);
        lineEdit_relatorio->setObjectName(QString::fromUtf8("lineEdit_relatorio"));
        lineEdit_relatorio->setEnabled(false);
        QFont font1;
        font1.setKerning(true);
        font1.setStyleStrategy(QFont::PreferDefault);
        lineEdit_relatorio->setFont(font1);
        lineEdit_relatorio->setCursor(QCursor(Qt::ArrowCursor));
        lineEdit_relatorio->setFrame(false);

        gridLayout->addWidget(lineEdit_relatorio, 0, 1, 1, 1);

        label_instancias = new QLabel(groupBox_relatorioGeral);
        label_instancias->setObjectName(QString::fromUtf8("label_instancias"));

        gridLayout->addWidget(label_instancias, 1, 0, 1, 1);

        label_atributos = new QLabel(groupBox_relatorioGeral);
        label_atributos->setObjectName(QString::fromUtf8("label_atributos"));

        gridLayout->addWidget(label_atributos, 1, 2, 1, 1);

        lineEdit_atributos = new QLineEdit(groupBox_relatorioGeral);
        lineEdit_atributos->setObjectName(QString::fromUtf8("lineEdit_atributos"));
        lineEdit_atributos->setEnabled(false);
        lineEdit_atributos->setCursor(QCursor(Qt::ArrowCursor));
        lineEdit_atributos->setFrame(false);

        gridLayout->addWidget(lineEdit_atributos, 1, 3, 1, 1);

        lineEdit_instancias = new QLineEdit(groupBox_relatorioGeral);
        lineEdit_instancias->setObjectName(QString::fromUtf8("lineEdit_instancias"));
        lineEdit_instancias->setEnabled(false);
        lineEdit_instancias->setCursor(QCursor(Qt::ArrowCursor));
        lineEdit_instancias->setFrame(false);

        gridLayout->addWidget(lineEdit_instancias, 1, 1, 1, 1);

        groupBox_atributos = new QGroupBox(tab_preProcess);
        groupBox_atributos->setObjectName(QString::fromUtf8("groupBox_atributos"));
        groupBox_atributos->setGeometry(QRect(10, 120, 241, 141));
        lineEdit_todosAtributos = new QLineEdit(groupBox_atributos);
        lineEdit_todosAtributos->setObjectName(QString::fromUtf8("lineEdit_todosAtributos"));
        lineEdit_todosAtributos->setGeometry(QRect(20, 30, 191, 91));
        lineEdit_todosAtributos->setReadOnly(true);
        lineEdit_5 = new QLineEdit(tab_preProcess);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(260, 10, 211, 321));
        tabWidget->addTab(tab_preProcess, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());

        gridLayout_2->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(Janela);
        QObject::connect(pushButton_abrir, SIGNAL(clicked()), Janela, SLOT(abrirArquivo()));

        QMetaObject::connectSlotsByName(Janela);
    } // setupUi

    void retranslateUi(QWidget *Janela)
    {
        Janela->setWindowTitle(QApplication::translate("Janela", "Janela", 0, QApplication::UnicodeUTF8));
        pushButton_abrir->setText(QApplication::translate("Janela", "Abrir arquivo...", 0, QApplication::UnicodeUTF8));
        groupBox_relatorioGeral->setTitle(QApplication::translate("Janela", "Relat\303\263rio geral", 0, QApplication::UnicodeUTF8));
        label_relatorio->setText(QApplication::translate("Janela", "  Relat\303\263rio:", 0, QApplication::UnicodeUTF8));
        lineEdit_relatorio->setText(QApplication::translate("Janela", "Nenhum", 0, QApplication::UnicodeUTF8));
        label_instancias->setText(QApplication::translate("Janela", "Inst\303\242ncias:", 0, QApplication::UnicodeUTF8));
        label_atributos->setText(QApplication::translate("Janela", "Atributos:", 0, QApplication::UnicodeUTF8));
        lineEdit_atributos->setText(QApplication::translate("Janela", "Nenhum", 0, QApplication::UnicodeUTF8));
        lineEdit_instancias->setText(QApplication::translate("Janela", "Nenhum", 0, QApplication::UnicodeUTF8));
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
