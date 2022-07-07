#include "MyString.h"
#include <iostream>
#include <fstream>

std::vector<std::string> MyString::Split(std::string str, char splitChar)
{
    std::vector<std::string> strs;
    std::stringstream ss = std::stringstream(str);
    std::string buf;

    while (std::getline(ss, buf, splitChar)) {
        strs.push_back(buf);
    }

    return strs;
}

std::vector<std::string> MyString::GetLines(std::filesystem::path path)
{
    std::vector<std::string> strs;

    std::ifstream ifs(path.c_str());

    //開けたら
    if (ifs) {
        std::string str;
        //行が読み込めなくなるまで
        while (!ifs.eof()) {
            //行を取得
            std::getline(ifs, str);
            //リストに追加
            strs.push_back(str);
        }
    }

    return strs;
}
