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
    ../src/mqeditor.cpp \
    ../src/config.cpp

HEADERS  += mainwindow.h \
    ../src/mqeditor.h \
    ../src/config.h

FORMS    += mainwindow.ui

INCLUDEPATH += ../srcs  ../maiquel-toolkit-cpp/src


LIBS  =  -L../maiquel-toolkit-cpp/lib       -lmtksupport  -lyaml
