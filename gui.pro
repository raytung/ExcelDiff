#-------------------------------------------------
#
# Project created by QtCreator 2014-01-28T23:50:31
#
#-------------------------------------------------

CONFIG   += qt

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = gui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        BasicExcel.cpp\
        ExcelDiff.cpp\
        ExcelFormat.cpp

HEADERS  += mainwindow.h\
            BasicExcel.hpp\
            ExcelDiff.hpp\
            ExcelFormat.h

FORMS += mainwindow.ui

