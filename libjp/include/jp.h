#ifndef LIBJP_H
#define LIBJP_H

#if defined _WIN32 || defined __CYGWIN__
#ifdef LIBJP_LIBRARY
  #ifdef __GNUC__
    #define LIBJP_EXPORT __attribute__ ((dllexport))
  #else
    #define LIBJP_EXPORT __declspec(dllexport)
  #endif
#else
  #ifdef __GNUC__
    #define LIBJP_EXPORT __attribute__ ((dllimport))
  #else
    #define LIBJP_EXPORT __declspec(dllimport)
  #endif
#endif
#define DLL_LOCAL
#else
#if __GNUC__ >= 4
  #define LIBJP_EXPORT __attribute__ ((visibility ("default")))
  #define LIBJP_LOCAL  __attribute__ ((visibility ("hidden")))
#else
  #define LIBJP_EXPORT
  #define LIBJP_LOCAL
#endif
#endif

#include <string>
#include <v8.h>

namespace jp {
    class File {
    private:
        bool success;
        std::string data;
        std::string filename;
    public:
        LIBJP_EXPORT File(const char *filename);
        LIBJP_EXPORT bool IsSuccessful() const;
        LIBJP_EXPORT const char *GetData() const;
        LIBJP_EXPORT unsigned long Length() const;
        LIBJP_EXPORT const char *GetFilename() const;
    };

    class ParserData {
    private:
        const File &file;
        unsigned int pos;
    public:
        LIBJP_EXPORT ParserData(const File *file);
        LIBJP_EXPORT bool IsEof() const;
        LIBJP_EXPORT void Seek(int amount);
        LIBJP_EXPORT unsigned int GetPos() const;
        LIBJP_EXPORT const char *GetTail() const;
        LIBJP_EXPORT const File *GetFile() const;
    };

    class Parser {
    private:
        const File &script;
        LIBJP_LOCAL static v8::Handle<v8::Object> createReadResult(const char *str, int pos);
        LIBJP_LOCAL static ParserData *getDataInstance(const v8::Local<v8::Object> holder);
        LIBJP_LOCAL static v8::Handle<v8::Value> jpEof(const v8::Arguments &args);
        LIBJP_LOCAL static v8::Handle<v8::Value> jpLog(const v8::Arguments &args);
        LIBJP_LOCAL static v8::Handle<v8::Value> jpRead(const v8::Arguments &args);
    public:
        LIBJP_EXPORT Parser(const File *script);
        LIBJP_EXPORT const ParserData Run(const File *data) const;
    };
}

#endif // LIBJP_H
