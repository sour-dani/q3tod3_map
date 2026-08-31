#include <cstring>
#include <iostream>
#include <string>
#include <filesystem>
#include "q3tod3_map.h"

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

    if (argc < 2 || argc > 3) {
        std::cout << usage << std::endl;
        return 1;
    } else {
        infile = argv[1];
    }
    if (argc == 2) {
        if (infile == "help" || infile == "-h" || infile == "--help") {
            std::cout << usage << std::endl;
            return 1;
        } else {
            std::string map_file = std::filesystem::path(infile).filename().generic_string();
            outfile = std::filesystem::path(infile).remove_filename().generic_string();
            outfile += "converted_" + map_file;
        }
    }
    else if (argc == 3) outfile = argv[2];

    std::cout<< "Converting: " << infile << std::endl;
    try {
        convert_map(infile, outfile);
        std::cout << "Generated map: " + outfile << std::endl;
    }
    catch (std::pair<std::string, std::string>& error) {
        std::cout << "|!|ERROR|!| " << error.first << " " << error.second;
        return 1;
    } catch(std::exception& e) {
        std::cerr << "|!|ERROR|!| Unexpected exception caught: " << e.what() << std::endl;
    }

    return 0;
}
