CONFIG += c++17
TEMPLATE = subdirs
SUBDIRS = core gui cli
core.subdir = src/core
gui.subdir = src/gui
cli.subdir = src/cli

cli.depends = core
gui.depends = core

CONFIG += lrelease
CONFIG += embed_translations
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
include(q3tod3_map.pri)
