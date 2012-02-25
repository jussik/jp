#include <iostream>

#include "file.h"
#include "parser.h"

int main() {
    File src("js/simpleParser.js");
    if(!src.isSuccessful()) {
        std::cerr << "Error opening script " << src.getFilename() << std::endl;
        return 1;
    }

    File data("data/kv.txt");
    if(!data.isSuccessful()) {
        std::cerr << "Error opening data " << data.getFilename() << std::endl;
        return 1;
    }

    Parser script(src.getData(), src.getLength());
    script.Run(data.getData(), data.getLength());

    return 0;
}

