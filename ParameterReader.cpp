#include "ParameterReader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

std::list<InputParam> ParameterReader::read(std::string fileName)
{
    auto pList = std::list<InputParam>();

    std::string path = fs::current_path().string() + "\\..\\SlimeSim\\" + fileName;
    std::cout << "read params: " << path << std::endl;

    std::ifstream file;
    file.open(path);

    if (file.is_open()) {
        std::string str;
        while (std::getline(file, str))
        {
            std::cout << "LINE: [" << str << "]" << std::endl;
        }
        std::cout << "while is done" << std::endl;
    } else {
        std::cout << "file not open" << std::endl;
    }

    file.close();

    return pList;
}
