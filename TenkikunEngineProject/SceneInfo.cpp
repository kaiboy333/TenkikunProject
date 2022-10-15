#include "SceneInfo.h"
#include "ProjectFileManager.h"

SceneInfo::SceneInfo()
{
	//ファイルIDを生成
	fileID = ProjectFileManager::CreateFileID();

	////マップに登録
	//ProjectFileManager::sceneInfos.insert(std::make_pair(fileID, this));
}