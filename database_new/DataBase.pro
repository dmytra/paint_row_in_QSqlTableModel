#-------------------------------------------------
#
# Project created by QtCreator 2015-08-10T16:08:24
#
#-------------------------------------------------

QT       += core
QT       += gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DataBase
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    database.cpp \
    tablemodel.cpp

HEADERS  += mainwindow.h \
    database.h \
    tablemodel.h

FORMS    += mainwindow.ui
