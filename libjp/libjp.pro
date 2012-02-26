include(../common.pri)

TARGET = build/jp
TEMPLATE = lib
CONFIG -= qt
VERSION = 0.1.0

LIBS += -lv8

DEFINES += LIBJP_LIBRARY

SOURCES += \
    src/parser.cpp \
    src/parserdata.cpp \
    src/file.cpp

HEADERS += \
    include/jp.h

