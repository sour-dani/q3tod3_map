QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    about.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    about.h \
    mainwindow.h

FORMS += \
    about.ui \
    mainwindow.ui

include(../../q3tod3_map.pri)
