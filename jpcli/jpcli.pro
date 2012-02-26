include(../common.pri)

TARGET = build/jpcli
TEMPLATE = app
CONFIG += console
CONFIG -= qt

LIBS += -L../libjp/build -ljp
INCLUDEPATH += ../libjp/include

SOURCES += src/main.cpp

