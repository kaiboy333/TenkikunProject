#include "SceneInfo.h"
#include "ProjectFileManager.h"

SceneInfo::SceneInfo()
{
	//�t�@�C��ID�𐶐�
	fileID = ProjectFileManager::CreateFileID();

	////�}�b�v�ɓo�^
	//ProjectFileManager::sceneInfos.insert(std::make_pair(fileID, this));
}