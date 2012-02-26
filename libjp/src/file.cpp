#include "../include/jp.h"
#include <fstream>

using namespace jp;

File::File(const char *name)
{
    filename = std::string(name);
    success = false;

    std::ifstream file(name);

    if(!file.is_open()) {
        return;
    }

    try {
        file.seekg(0, std::ios::end);
        data.reserve(file.tellg());
        file.seekg(0, std::ios::beg);

        data.assign((std::istreambuf_iterator<char>(file)),
                    std::istreambuf_iterator<char>());

        file.close();
    } catch (...) {
        if(file.is_open())
            file.close();
        return;
    }

    success = true;
}

bool File::IsSuccessful() const {
    return success;
}

unsigned long File::Length() const {
    return data.length();
}

const char *File::GetData() const {
    return data.c_str();
}

const char *File::GetFilename() const {
    return filename.c_str();
}
