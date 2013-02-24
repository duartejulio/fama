#-------------------------------------------------
#
# Project created by QtCreator 2013-02-24T12:48:59
#
#-------------------------------------------------

QT       += core gui

TARGET = InterfaceFAMA
TEMPLATE = app


SOURCES += main.cpp\
        janela.cpp \
    param.cpp \
    modeloparam.cpp \
    ../../corpusInterface/corpusmatriz.cpp \
    ../../corpusInterface/corpus.cpp

HEADERS  += janela.h \
    param.h \
    modeloparam.h \
    ../../corpusInterface/corpusmatriz.h \
    ../../corpusInterface/corpus.h

FORMS    += janela.ui \
    param.ui
