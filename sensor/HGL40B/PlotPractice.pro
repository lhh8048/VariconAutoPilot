#-------------------------------------------------
#
# Project created by QtCreator 2015-05-06T19:05:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = PlotPractice
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    jetsonGPIO.c \
    hgl40b.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    jetsonGPIO.h \
    hgl40b.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    Border 1920x1080.png \
    Border 1920x1080.png \
    Border 1920x1080.png

RESOURCES += \
    PlotPractice.qrc