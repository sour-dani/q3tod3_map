#include <cstring>
#include <iostream>
#include <string>
#include <filesystem>
// #include "q3tod3_map.h" // broken for some reason
#include "q3tod3_map.cpp"

int main(int argc, char* argv[]) {
    std::string usage = "Usage: q3tod3_map input.map [output.map]";
    std::string infile = "";
    std::string outfile = "";

    std::cout << "q3tod3_map " << APP_VERSION << " ";
#ifdef __WIN64__
    std::cout << "(x86_64-pc-windows-msvc)";
#elif __linux__
    std::cout << "(x86_64-unknown-linux-gnu)";
#endif
    std::cout << std::endl;
    std::cout << "Copyright (C) 2025 motorsep - License GPLv3" << std::endl;
    std::cout << "Modified by Sour Dani" << std::endl;
    std::cout << std::endl;

    if (argc > 2) outfile = argv[2];
    if (argc == 2) {
        if (strcmp(argv[1], "help") == 0 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
            std::cout << usage << std::endl;
            return 1;
        } else {
            std::string map_file = std::filesystem::path(argv[1]).generic_string();
            outfile += "converted_" + map_file;
        }
    }
    else if (argc < 2 || argc > 3) {
        std::cout << usage << std::endl;
        return 1;
    }

    infile = argv[1];
    std::cout<< "Converting: " << infile << std::endl;
    try {
        convert_map(infile, outfile);
        std::cout << "Generated map: " + outfile << std::endl;
    }
    catch (const std::string msg) {
        std::cout << msg;
        return 1;
    }
    return 0;
}
