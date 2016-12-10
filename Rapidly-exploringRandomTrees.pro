#-------------------------------------------------
#
# Project created by QtCreator 2016-12-10T10:54:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Rapidly-exploringRandomTreess
TEMPLATE = app


SOURCES +=\
    src/classes/vertex.cpp \
    src/app/main.cpp \
    src/app/mainwindow.cpp \
    src/classes/quadrant.cpp \
    src/classes/metrics/euclidiandistance.cpp \
    src/classes/environment.cpp \
    src/classes/metrics/manhattandistance.cpp \
    src/classes/metrics/metric.cpp \
    src/classes/session.cpp

HEADERS  += \
    src/classes/vertex.h \
    src/app/mainwindow.h \
    src/classes/quadrant.h \
    src/classes/metrics/euclidiandistance.h \
    src/classes/environment.h \
    src/classes/metrics/metric.h \
    src/classes/metrics/manhattandistance.h \
    src/classes/session.h

FORMS    += mainwindow.ui
