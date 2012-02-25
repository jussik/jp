#ifndef FILE_H
#define FILE_H

#include <string>

class File
{
private:
    bool success;
    char *data;
    int length;
    std::string filename;
public:
    File(const char *filename);
    ~File();
    bool isSuccessful() const;
    const char *getData() const;
    int getLength() const;
    const std::string getFilename() const;
};

#endif // FILE_H
