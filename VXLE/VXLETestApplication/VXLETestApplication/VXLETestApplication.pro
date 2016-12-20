QT += qml quick

CONFIG += c++11

SOURCES += main.cpp \
    vxlemenucontroller.cpp \
    vxlemenuitem.cpp \
    vxletestapplicationsettings.cpp \
    vxlesrtmloader.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML2_IMPORT_PATH  =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    vxlemenucontroller.h \
    vxlemenuitem.h \
    vxletestapplicationsettings.h \
    vxlesrtmloader.h
