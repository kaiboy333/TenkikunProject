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

    //�J������
    if (ifs) {
        std::string str;
        //�s���ǂݍ��߂Ȃ��Ȃ�܂�
        while (!ifs.eof()) {
            //�s���擾
            std::getline(ifs, str);
            //���X�g�ɒǉ�
            strs.push_back(str);
        }
    }

    return strs;
}
