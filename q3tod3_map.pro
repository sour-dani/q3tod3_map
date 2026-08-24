CONFIG += c++17

TEMPLATE = subdirs
SUBDIRS = gui cli shared
gui.subdir = src/gui
cli.subdir = src/cli
shared.subdir = src/shared
src/cli.depends = shared
src/gui.depends = shared

TRANSLATIONS += \
    locales/q3tod3_map_en_US.ts
CONFIG += lrelease
CONFIG += embed_translations
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += src/shared
