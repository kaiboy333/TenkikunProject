#include "Info.h"
#include "ProjectFileManager.h"

Info::Info() : SceneInfo()
{
	guid = ProjectFileManager::CreateGUID();	//guidを作成、セット

	ProjectFileManager::guidAndInfo.insert(std::make_pair(guid, this));	//guidとInfoのマップに追加
}

//void Info::SetGUID(std::string guid)
//{
//	this->guid = guid;
//}

std::string Info::GetGUID()
{
	return guid;
}
