#include "parserdata.h"

#include <iostream>

ParserData::ParserData(const char *dataStr, int length) : data(dataStr), dataLength(length), pos(0) { }

bool ParserData::isEof() const {
    return pos >= dataLength;
}

void ParserData::seek(int amount) {
    pos += amount;
}

int ParserData::getPos() const {
    return pos;
}

const char *ParserData::getTail() const {
    return data + pos;
}
