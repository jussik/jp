TEMPLATE = app
CONFIG += console
CONFIG -= qt

LIBS += -lv8

SOURCES += src/main.cpp \
    src/parser.cpp \
    src/parserdata.cpp \
    src/file.cpp

OTHER_FILES += \
    js/simpleParser.js \
    data/kv.txt \
    README.md

HEADERS += \
    src/parser.h \
    src/parserdata.h \
    src/file.h

