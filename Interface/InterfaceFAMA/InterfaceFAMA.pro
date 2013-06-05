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
    param.cpp \
    modeloparam.cpp \
    ../../classificador/classificadortbl.cpp \
    ../../classificador/classificadorhmm.cpp \
    ../../classificador/classificador_maisprovavel.cpp \
    ../../classificador/classificador.cpp \
    ../../treinador/treinador.cpp \
    ../../treinador/tbl.cpp \
    ../../treinador/maisprovavel.cpp \
    ../../treinador/hmm.cpp \
    ../../outros/regra.cpp \
    ../../corpus/corpusmatrizui.cpp \
    ../../treinador/maisprovavelui.cpp \
    ../../validador/validadortreino.cpp \
    ../../validador/validadorteste.cpp \
    ../../validador/validadorkdobras.cpp \
    ../../validador/validadordivisao.cpp \
    ../../validador/validador.cpp \
    ../../avaliador/avaliador_acuracia.cpp \
    ../../avaliador/Avaliador.cpp \
    ../../treinador/hmmui.cpp \
    ../../treinador/tblui.cpp \
    dados.cpp

HEADERS  += janela.h \
    ../../corpus/corpusmatriz.h \
    ../../corpus/corpus.h \
    param.h \
    modeloparam.h \
    ../../classificador/classificadortbl.h \
    ../../classificador/classificadorhmm.h \
    ../../classificador/classificador_maisprovavel.h \
    ../../classificador/classificador.h \
    ../../treinador/treinador.h \
    ../../treinador/tbl.h \
    ../../treinador/maisprovavel.h \
    ../../treinador/hmm.h \
    ../../outros/regra.h \
    ../../corpus/corpusmatrizui.h \
    ../../treinador/maisprovavelui.h \
    ../../validador/validadortreino.h \
    ../../validador/validadorteste.h \
    ../../validador/validadorkdobras.h \
    ../../validador/validadordivisao.h \
    ../../validador/validador.h \
    ../../avaliador/avaliador_acuracia.h \
    ../../avaliador/Avaliador.h \
    ../../treinador/hmmui.h \
    ../../treinador/tblui.h \
    dados.h

FORMS    += janela.ui \
    param.ui \
    dados.ui
