#include <iostream>
#include <jp.h>

int main() {
    jp::File src("js/simpleParser.js");
    if(!src.IsSuccessful()) {
        std::cerr << "Error opening script " << src.GetFilename() << std::endl;
        return 1;
    }

    jp::File data("data/kv.txt");
    if(!data.IsSuccessful()) {
        std::cerr << "Error opening data " << data.GetFilename() << std::endl;
        return 1;
    }

    jp::Parser script(&src);
    const jp::ParserData pd = script.Run(&data);

    std::cout << "DONE " << pd.GetPos() << std::endl;

    return 0;
}

