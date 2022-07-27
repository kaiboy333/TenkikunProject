#include "Info.h"
#include "ProjectFileManager.h"

Info::Info(std::filesystem::path path, bool canWrite) : SceneInfo()
{
	////guid��Info�̃}�b�v�ɒǉ�
	//ProjectFileManager::guidAndInfo.insert(std::make_pair(guid, this));

	//�p�X���Z�b�g
	this->path = path;
	//���O��ݒ�
	this->name = ProjectFileManager::GetNameWithoutExtensionName(path.filename());
	//�t�@�C�������݂��Ă��Ȃ��A�V�����J���Ă����Ȃ�
	if (!std::filesystem::exists(path) && canWrite) {
		//�t�@�C�����쐬
		std::ofstream ofs(path.c_str());
	}
	//�_�t�@�C�����쐬�Aguid���Z�b�g
	this->guid = ProjectFileManager::WriteToKumoFile(path.string() + ".kumo");

	//guid�ƃp�X�̃y�A���}�b�v�ɓo�^
	ProjectFileManager::guidAndPath.insert(std::make_pair(this->guid, path));
	//path��Info�̃}�b�v�ɒǉ�
	ProjectFileManager::pathAndInfo.insert(std::make_pair(path, this));
}