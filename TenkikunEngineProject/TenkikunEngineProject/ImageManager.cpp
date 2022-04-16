#include "ImageManager.h"

int* ImageManager::LoadImage(std::string path)
{
	//�����A���ɉ摜���ǂݍ��܂�Ă����Ȃ�
	if (ghs.count(path.c_str())) {
		return ghs[path.c_str()];	//�����Ԃ�
	}

	//�摜��V�����ǂݍ���
	int gh;		//GraphicHandle
	//�摜���ǂݍ��߂Ȃ�������
	if ((gh = LoadGraph(path.c_str()) == -1)) {
		std::cout << "�摜�t�@�C�����ǂݍ��߂Ȃ���" << std::endl;
		return nullptr;
	}
	ghs[path] = &gh;	//�ǂݍ��߂���ghs�ɒǉ�
	//�����Ԃ�
	return &gh;
}
