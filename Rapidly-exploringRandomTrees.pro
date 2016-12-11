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
    src/classes/environment/vertex.cpp \
    src/app/main.cpp \
    src/app/mainwindow.cpp \
    src/classes/environment/quadrant.cpp \
    src/classes/metrics/euclidiandistance.cpp \
    src/classes/environment/environment.cpp \
    src/classes/metrics/manhattandistance.cpp \
    src/classes/metrics/metric.cpp \
    src/classes/session.cpp \
    src/classes/heightmap.cpp \
    src/app/heightmapframe.cpp \
    src/app/heightmapsuppanel.cpp \
    src/app/heightmapsubpanel.cpp \
    src/classes/generators/treegenerator.cpp \
    src/classes/endmethods/endmethod.cpp \
    src/classes/endmethods/verticesnumber.cpp \
    src/classes/endmethods/timelimit.cpp

HEADERS  += \
    src/classes/environment/vertex.h \
    src/app/mainwindow.h \
    src/classes/environment/quadrant.h \
    src/classes/metrics/euclidiandistance.h \
    src/classes/environment/environment.h \
    src/classes/metrics/metric.h \
    src/classes/metrics/manhattandistance.h \
    src/classes/session.h \
    src/classes/heightmap.h \
    src/app/heightmapframe.h \
    src/app/heightmapsuppanel.h \
    src/app/heightmapsubpanel.h \
    src/classes/generators/treegenerator.h \
    src/classes/endmethods/endmethod.h \
    src/classes/endmethods/verticesnumber.h \
    src/classes/endmethods/timelimit.h

FORMS    += mainwindow.ui
