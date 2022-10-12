#include "MyString.h"
#include <iostream>
#include <fstream>

std::vector<std::string> MyString::Split(std::string str, std::string splitStr)
{
    std::vector<std::string> strs;
    //std::stringstream ss = std::stringstream(str);
    //std::string buf;

    //while (std::getline(ss, buf, splitChar)) {
    //    strs.push_back(buf);
    //}

    auto splitStrLen = splitStr.length();

    auto list = std::vector<std::string>();

    if (splitStrLen == 0) {
        list.push_back(str);
    }
    else {
        auto offset = std::string::size_type(0);
        while (1) {
            auto pos = str.find(splitStr, offset);
            if (pos == std::string::npos) {
                list.push_back(str.substr(offset));
                break;
            }
            list.push_back(str.substr(offset, pos - offset));
            offset = pos + splitStrLen;
        }
    }

    return list;
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
