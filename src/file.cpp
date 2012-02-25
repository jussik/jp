#include "file.h"

#include <fstream>

File::File(const char *name)
{
    filename = std::string(name);
    success = false;
    length = 0;

    std::ifstream file(name);

    if(!file.is_open()) {
        return;
    }

    int fileLength = 0;
    bool isAllocated = false;

    try {
        file.seekg(0, std::ios::end);
        fileLength = file.tellg();
        file.seekg(0, std::ios::beg);

        // Appending a null to the buffer, just in case
        data = new char[fileLength + 1];
        isAllocated = true;
        data[fileLength] = '\0';

        file.read(data, fileLength);

        file.close();
    } catch (...) {
        if(isAllocated)
            delete data;
        if(file.is_open())
            file.close();
        return;
    }

    length = fileLength;
    success = true;
}

File::~File() {
    if(success)
        delete [] data;
}

bool File::isSuccessful() const {
    return success;
}

int File::getLength() const {
    return length;
}

const char *File::getData() const {
    return data;
}

const std::string File::getFilename() const {
    return filename;
}
