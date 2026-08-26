CONFIG += c++17
TEMPLATE = subdirs
SUBDIRS = shared gui cli
shared.subdir = src/shared
gui.subdir = src/gui
cli.subdir = src/cli

cli.depends = shared
gui.depends = shared

CONFIG += lrelease
CONFIG += embed_translations
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
