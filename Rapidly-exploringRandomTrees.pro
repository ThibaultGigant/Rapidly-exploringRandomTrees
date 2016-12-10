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
    src/classes/environnement.cpp \
    src/classes/heightmap.cpp \
    src/app/heightmapframe.cpp \
    src/app/heightmapsuppanel.cpp \
    src/app/heightmapsubpanel.cpp

HEADERS  += \
    src/classes/vertex.h \
    src/app/mainwindow.h \
    src/classes/quadrant.h \
    src/classes/environnement.h \
    src/classes/heightmap.h \
    src/app/heightmapframe.h \
    src/app/heightmapsuppanel.h \
    src/app/heightmapsubpanel.h

FORMS    += mainwindow.ui
