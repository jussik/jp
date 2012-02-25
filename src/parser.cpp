#include "parser.h"

#include <v8.h>
#include <iostream>

using namespace v8;

Parser::Parser(const char *_script, int _scriptLength) : script(_script), scriptLength(_scriptLength) { }

Handle<Object> Parser::createReadResult(const char *str, int pos) {
    HandleScope scope;

    Handle<Object> obj = Object::New();
    obj->Set(String::New("%val"), String::New(str));
    obj->Set(String::New("%pos"), Number::New(pos));

    return scope.Close(obj);
}

ParserData *Parser::getDataInstance(const Local<Object> holder) {
    Local<External> wrap = Local<External>::Cast(holder->GetInternalField(0));
    return static_cast<ParserData*>(wrap->Value());
}

Handle<Value> Parser::jpEof(const Arguments &args) {
    HandleScope scope;
    ParserData *data = getDataInstance(args.Holder());

    Handle<Boolean> out = Boolean::New(data->isEof());

    return scope.Close(out);
}

Handle<Value> Parser::jpLog(const Arguments &args) {
    ParserData *data = getDataInstance(args.Holder());

    std::cout << "Log:" << data->getPos();
    if(args.Length()) {
        String::Utf8Value arg(args[0]);
        std::cout << ":" << *arg;
    }
    std::cout << std::endl;

    return Null();
}

Handle<Value> Parser::jpRead(const Arguments &args) {
    HandleScope scope;
    ParserData *data = getDataInstance(args.Holder());

    if(data->isEof()) {
        return ThrowException(String::New("Attempted to read past end of file"));
    } if(!args.Length()) {
        // No arguments, just read 1 char
        char str[2];
        int pos = data->getPos();
        str[0] = data->getTail()[0];
        data->seek(1);
        str[1] = '\0';
        return scope.Close(createReadResult(str, pos));
    } else if(args[0]->IsRegExp()) {
        // Create regex callback
        const char *src = "(function(rx, str){return str.match(rx)})";
        Handle<String> source = String::New(src);
        Handle<Script> js = Script::Compile(source);
        Handle<Value> funcVal = js->Run();
        Handle<Function> func = Handle<Function>::Cast(funcVal);

        // Run regex callback
        Handle<Value> rxList[2];
        rxList[0] = Handle<RegExp>::Cast(args[0]);
        rxList[1] = String::New(data->getTail());
        Local<Object> result = Local<Object>::Cast(func->CallAsFunction(args.This(), 2, rxList));

        // Handle the result
        if(result->IsNull()) {
            return ThrowException(String::New("Regular expression did not match"));
        } else {
            // Make sure index == 0 so we're not skipping any characters
            Local<Integer> index = Local<Integer>::Cast(result->Get(String::New("index")));
            if(index->Value() > 0)
                return ThrowException(String::New("Regular expression did not match"));

            // Our result is the first index of the array
            Local<Array> arr = Local<Array>::Cast(result);
            String::Utf8Value resultStr(arr->Get(0));

            int pos = data->getPos();
            data->seek(resultStr.length());
            //std::cout << "READ:" << pos << "-" << data->getPos() << " " << *resultStr << std::endl;
            return scope.Close(createReadResult(*resultStr, pos));
        }
    }

    return ThrowException(String::New("Unsupported argument type for read"));
}

ParserData Parser::Run(const char *_data, int dataLength) {
    // Init data
    ParserData data(_data, dataLength);

    // Init scope
    HandleScope scope;

    // Start context
    Handle<Context> context = Context::New();
    Context::Scope context_scope(context);

    // Make jp object
    Handle<ObjectTemplate> jp = ObjectTemplate::New();
    jp->SetInternalFieldCount(1);
    jp->Set(String::New("doc"), ObjectTemplate::New(), ReadOnly);
    jp->Set(String::New("log"), FunctionTemplate::New(&Parser::jpLog), ReadOnly);
    jp->Set(String::New("eof"), FunctionTemplate::New(&Parser::jpEof), ReadOnly);
    jp->Set(String::New("read"), FunctionTemplate::New(&Parser::jpRead), ReadOnly);

    Local<Object> jpInstance = jp->NewInstance();
    jpInstance->SetInternalField(0, External::New(&data));
    context->Global()->Set(String::New("jp"), jpInstance, ReadOnly);

    // Run script
    Handle<String> source = String::New(script);
    Handle<Script> js = Script::Compile(source);
    js->Run();

    return data;
}
