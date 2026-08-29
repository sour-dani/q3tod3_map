QT       += core gui widgets
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
TARGET = q3tod3_map_gui

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
