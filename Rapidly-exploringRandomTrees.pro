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
    src/classes/generators/treegenerator.cpp \
    src/classes/endmethods/endmethod.cpp \
    src/classes/generators/randomtreegenerator.cpp \
    src/classes/generators/rrtgenerator.cpp \
    src/app/centralwidget.cpp \
    src/classes/config.cpp \
    src/app/heightmappanel/heightmapfilepanel.cpp \
    src/app/heightmappanel/heightmapframe.cpp \
    src/app/heightmappanel/heightmapsubpanel.cpp \
    src/app/heightmappanel/heightmapviewpanel.cpp \
    src/app/configpanel/configpanel.cpp \
    src/app/configpanel/endmethodwidget.cpp \
    src/app/configpanel/generatorwidget.cpp \
    src/app/configpanel/metricwidget.cpp \
    src/app/configpanel/additionalinfoswidget.cpp

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
    src/classes/generators/treegenerator.h \
    src/classes/endmethods/endmethod.h \
    src/classes/generators/randomtreegenerator.h \
    src/classes/generators/rrtgenerator.h \
    src/app/centralwidget.h \
    src/classes/config.h \
    src/app/heightmappanel/heightmapfilepanel.h \
    src/app/heightmappanel/heightmapframe.h \
    src/app/heightmappanel/heightmapsubpanel.h \
    src/app/heightmappanel/heightmapviewpanel.h \
    src/app/configpanel/configpanel.h \
    src/app/configpanel/endmethodwidget.h \
    src/app/configpanel/generatorwidget.h \
    src/app/configpanel/metricwidget.h \
    src/app/configpanel/additionalinfoswidget.h

FORMS    += mainwindow.ui
