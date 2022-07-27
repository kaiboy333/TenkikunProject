#include "Info.h"
#include "ProjectFileManager.h"

Info::Info(std::filesystem::path path, bool canWrite) : SceneInfo()
{
	////guidとInfoのマップに追加
	//ProjectFileManager::guidAndInfo.insert(std::make_pair(guid, this));

	//パスをセット
	this->path = path;
	//名前を設定
	this->name = ProjectFileManager::GetNameWithoutExtensionName(path.filename());
	//ファイルが存在していなく、新しく開いていいなら
	if (!std::filesystem::exists(path) && canWrite) {
		//ファイルを作成
		std::ofstream ofs(path.c_str());
	}
	//雲ファイルを作成、guidをセット
	this->guid = ProjectFileManager::WriteToKumoFile(path.string() + ".kumo");

	//guidとパスのペアをマップに登録
	ProjectFileManager::guidAndPath.insert(std::make_pair(this->guid, path));
	//pathとInfoのマップに追加
	ProjectFileManager::pathAndInfo.insert(std::make_pair(path, this));
}