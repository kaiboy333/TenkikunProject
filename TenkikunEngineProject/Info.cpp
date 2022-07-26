#include "Info.h"
#include "ProjectFileManager.h"

Info::Info() : SceneInfo()
{
	guid = ProjectFileManager::CreateGUID();	//guid���쐬�A�Z�b�g

	ProjectFileManager::guidAndInfo.insert(std::make_pair(guid, this));	//guid��Info�̃}�b�v�ɒǉ�
}

//void Info::SetGUID(std::string guid)
//{
//	this->guid = guid;
//}

std::string Info::GetGUID()
{
	return guid;
}
