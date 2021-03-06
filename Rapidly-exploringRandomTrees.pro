#-------------------------------------------------
#
# Project created by QtCreator 2016-12-10T10:54:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Rapidly-exploringRandomTrees
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
    src/app/configpanel/additionalinfoswidget/additionalinfoswidget.cpp \
    src/app/configpanel/endmethodwidget/endmethodwidget.cpp \
    src/app/configpanel/generatorwidget/generatorwidget.cpp \
    src/app/configpanel/metricwidget/metricwidget.cpp \
    src/app/configpanel/endmethodwidget/nbverticeslimitwidget.cpp \
    src/app/configpanel/endmethodwidget/timelimitwidget.cpp \
    src/app/configpanel/additionalinfoswidget/nbrunsframe.cpp \
    src/app/configpanel/additionalinfoswidget/sleeptimeframe.cpp \
    src/app/configpanel/runbuttonswidget/runbuttonswidget.cpp \
    src/app/configpanel/additionalinfoswidget/deltatframe.cpp \
    src/classes/threadgenerator.cpp \
    src/app/configpanel/listwidget/listwidget.cpp \
    src/app/heightmappanel/dragwidget.cpp \
    src/classes/generators/prmgenerator.cpp

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
    src/app/configpanel/additionalinfoswidget/additionalinfoswidget.h \
    src/app/configpanel/endmethodwidget/endmethodwidget.h \
    src/app/configpanel/generatorwidget/generatorwidget.h \
    src/app/configpanel/metricwidget/metricwidget.h \
    src/app/configpanel/endmethodwidget/nbverticeslimitwidget.h \
    src/app/configpanel/endmethodwidget/timelimitwidget.h \
    src/app/configpanel/additionalinfoswidget/nbrunsframe.h \
    src/app/configpanel/additionalinfoswidget/sleeptimeframe.h \
    src/app/configpanel/runbuttonswidget/runbuttonswidget.h \
    src/app/configpanel/additionalinfoswidget/deltatframe.h \
    src/classes/threadgenerator.h \
    src/app/configpanel/listwidget/listwidget.h \
    src/app/heightmappanel/dragwidget.h \
    src/classes/generators/prmgenerator.h

FORMS    += mainwindow.ui

DISTFILES += \
    ressources
