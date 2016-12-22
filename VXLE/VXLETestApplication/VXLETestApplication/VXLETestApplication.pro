QT += qml quick

CONFIG += c++11

SOURCES += main.cpp \
    vxlemenucontroller.cpp \
    vxlemenuitem.cpp \
    vxletestapplicationsettings.cpp \
    vxlesrtmloader.cpp \
    vxlemaprenderer.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML2_IMPORT_PATH  =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    vxlemenucontroller.h \
    vxlemenuitem.h \
    vxletestapplicationsettings.h \
    vxlesrtmloader.h \
    vxlemaprenderer.h

release: DESTDIR = ./build-release
debug:   DESTDIR = ./build-debug

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui
