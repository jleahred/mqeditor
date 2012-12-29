#-------------------------------------------------
#
# Project created by QtCreator 2012-12-22T17:03:07
#
#-------------------------------------------------

QT       += core gui

QMAKE_CXXFLAGS += -std=gnu++0x

TARGET = untitled6
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../src/mqeditor.cpp

HEADERS  += mainwindow.h \
    ../src/mqeditor.h

FORMS    += mainwindow.ui

INCLUDEPATH += ../srcs  ../maiquel-tolkit-cpp/src


LIBS  =  -L../maiquel-tolkit-cpp/lib       -lmtksupport  -lyaml
