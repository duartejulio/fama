#-------------------------------------------------
#
# Project created by QtCreator 2012-08-17T20:36:15
#
#-------------------------------------------------

QT       += core gui

TARGET = InterfaceFAMA
TEMPLATE = app


SOURCES += main.cpp\
        janela.cpp \
    ../../corpus/corpusmatriz.cpp \
    ../../corpus/corpus.cpp \
    botao.cpp \
    paramcorpus.cpp

HEADERS  += janela.h \
    ../../corpus/corpusmatriz.h \
    ../../corpus/corpus.h \
    botao.h \
    paramcorpus.h

FORMS    += janela.ui \
    paramcorpus.ui
