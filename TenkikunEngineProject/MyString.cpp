#include "MyString.h"

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
