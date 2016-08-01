#-------------------------------------------------
#
# Project created by QtCreator 2016-06-09T16:17:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = kbt_v1
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    algorithm.cpp \
    renderarea.cpp \
    inputwidget.cpp \
    tools.cpp \
    simulation.cpp \
    node.cpp \
    algbroadcastinterpolate.cpp \
    algbroadcastdirect.cpp \
    algvoronoi.cpp \
    graphwindow.cpp \
    qcustomplot.cpp \
    graphcomponent.cpp \
    responsiblenodes.cpp

HEADERS  += mainwindow.h \
    vector2f.h \
    tools.h \
    voronoicell.h \
    node.h \
    algorithm.h \
    input.h \
    renderarea.h \
    inputwidget.h \
    simulation.h \
    constants.h \
    algmodel.h \
    alg.h \
    algbroadcastinterpolate.h \
    algbroadcastdirect.h \
    algvoronoi.h \
    graphwindow.h \
    qcustomplot.h \
    graphcomponent.h \
    responsiblenodes.h

FORMS    += mainwindow.ui
