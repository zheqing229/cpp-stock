QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    indexstock.cpp \
    indexstockarray.cpp \
    linearprogramming.cpp \
    linearregression.cpp \
    main.cpp \
    mainwindow.cpp \
    plotwindow.cpp \
    predictionplotwindow.cpp \
    qcustomplot.cpp \
    stockchina.cpp \
    stockchinaarray.cpp \
    util.cpp

HEADERS += \
    ../../QCustomPlot图形库说明及K线图示例/MyPlotWindow/qcustomplot.h \
    ../../QCustomPlot图形库说明及K线图示例/MyPlotWindow/qcustomplot.h \
    datadef.h \
    indexstock.h \
    indexstockarray.h \
    linearprogramming.h \
    linearregression.h \
    mainwindow.h \
    plotwindow.h \
    predictionplotwindow.h \
    qcustomplot.h \
    stockchina.h \
    stockchinaarray.h \
    util.h

FORMS += \
    mainwindow.ui \
    plotwindow.ui \
    predictionplotwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
