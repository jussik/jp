#ifndef PARSERDATA_H
#define PARSERDATA_H

#include <vector>

class ParserData
{
private:
    const char *data;
    int dataLength;
    int pos;
public:
    ParserData(const char* data, int length);
    bool isEof() const;
    void seek(int amount);
    int getPos() const;
    const char *getTail() const;
};

#endif // PARSERDATA_H
