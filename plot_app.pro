#-------------------------------------------------
#
# Project created by QtCreator 2014-02-10T14:33:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport
TARGET = plot_app
TEMPLATE = app

QMAKE_LFLAGS += /INCREMENTAL:NO

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0#?????mozna usunac??

SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h

FORMS    += mainwindow.ui
