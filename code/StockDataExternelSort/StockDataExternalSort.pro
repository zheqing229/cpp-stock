QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    indexstock.cpp \
    indexstockarray.cpp \
    main.cpp \
    stock.cpp \
    stockarray.cpp \
    stockchina.cpp \
    stockchinaarray.cpp \
    stockus.cpp \
    stockusarray.cpp \
    util.cpp

HEADERS += \
    bigdata.h \
    datadef.h \
    heap.h \
    indexstock.h \
    indexstockarray.h \
    mergesort.h \
    stock.h \
    stockarray.h \
    stockchina.h \
    stockchinaarray.h \
    stockus.h \
    stockusarray.h \
    util.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
