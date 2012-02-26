#include "../include/jp.h"
#include <iostream>

using namespace jp;

ParserData::ParserData(const File *_file) : file(*_file), pos(0) { }

bool ParserData::IsEof() const {
    return pos >= file.Length();
}

void ParserData::Seek(int amount) {
    pos += amount;
}

unsigned int ParserData::GetPos() const {
    return pos;
}

const char *ParserData::GetTail() const {
    return file.GetData() + pos;
}

const File *ParserData::GetFile() const {
    return &file;
}
