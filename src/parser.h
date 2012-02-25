#ifndef PARSER_H
#define PARSER_H

#include "parserdata.h"

#include <v8.h>

class Parser
{
private:
    const char *script;
    const int scriptLength;

    static v8::Handle<v8::Object> createReadResult(const char *str, int pos);
    static ParserData *getDataInstance(const v8::Local<v8::Object> holder);
    static v8::Handle<v8::Value> jpEof(const v8::Arguments &args);
    static v8::Handle<v8::Value> jpLog(const v8::Arguments &args);
    static v8::Handle<v8::Value> jpRead(const v8::Arguments &args);
public:
    Parser(const char *script, int scriptLength);
    ParserData Run(const char *data, int dataLength);
};

#endif // PARSER_H
