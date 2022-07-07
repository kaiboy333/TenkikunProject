#include "ProjectFileManager.h"
#include "DxLib.h"
#include <fstream>
#include <iostream>
#include "Debug.h"
#include <rpcdce.h>
#include "MyString.h"
#include "Image.h"
#include <string>

ProjectFileManager::ProjectFileManager()
{
	//アセットのパスを作成
	assetFilePath = std::filesystem::current_path().string() + "\\Asset";
	//アセットの親の絶対パスにバックスラッシュ追加
	assetParentPathName = assetFilePath.parent_path().string() + "\\";
	//アセットフォルダが存在しないなら
	if (!std::filesystem::exists(assetFilePath)) {
		//フォルダを作成
		std::filesystem::create_directory(assetFilePath);
	}
	currentPath = assetFilePath;	//初期はアセットパス
}

void ProjectFileManager::Update()
{
	//ドラッグファイルリストのリセット
	dragFilePathes.clear();
	//ドラッグされているファイルがあるなら
	if (GetDragFileNum != 0) {
		for (int i = 0; i < GetDragFileNum(); i++) {
			TCHAR currentPath[100] = {};
			//読み込めたら
			if (GetDragFilePath(currentPath) != -1) {
				//ドラッグされたファイルのパスを作成
				std::filesystem::path path = std::filesystem::path(std::string(currentPath));
				//リストに追加
				dragFilePathes.push_back(path);
			}
		}
	}
}

ProjectFileManager::FileType ProjectFileManager::GetFileType(std::filesystem::path path) {
	//パスの拡張子を取得
	std::string extensionName = path.extension().string();

	//初期化
	FileType targetFileType = FileType::None;

	//パスがディレクトリだったら
	if (std::filesystem::is_directory(path)) {
		targetFileType = FileType::Folder;
	}
	else {
		//画像だったら
		if (extensionName == ".png" || extensionName == ".jpg") {
			targetFileType = FileType::Image;
		}
		//スクリプトだったら(cpp)
		else if (extensionName == ".cpp") {
			targetFileType = FileType::Script_cpp;
		}
		//スクリプトだったら(hpp)
		else if (extensionName == ".hpp") {
			targetFileType = FileType::Script_hpp;
		}
		//スクリプトだったら(h)
		else if (extensionName == ".h") {
			targetFileType = FileType::Script_h;
		}
		//雲ファイルなら
		else if (extensionName == ".kumo") {
			targetFileType = FileType::Kumo;
		}
	}

	//タイプを返す
	return targetFileType;
}

void ProjectFileManager::CreateAndLoadKumoFile(std::filesystem::path path)
{
	//ファイルタイプが何もナシか雲ファイルなら
	if (GetFileType(path) == FileType::None || GetFileType(path) == FileType::Kumo)
		//終わり
		return;

	//雲ファイルパスを作成
	std::filesystem::path kumoPath = std::filesystem::path(path.string() + ".kumo");

	//ファイルが存在しないなら
	if (!std::filesystem::exists(kumoPath)) {
		//ファイルに記述する
		WriteToKumoFile(kumoPath);
	}

	//雲ファイルからInfoクラスを作成
	WriteToInfo(kumoPath);
}

void ProjectFileManager::WriteToInfo(std::filesystem::path kumoPath)
{
	//ファイルを開く
	std::ifstream ifs(kumoPath.c_str());
	//開けたら
	if (ifs) {
		std::string strBuf;

		//行たちを読み込み
		std::vector<std::string> lines = MyString::GetLines(kumoPath);

		//GUIDを取得
		std::string guidStr = MyString::Split(lines[0], ':')[1];

		//追加で読み込んでInfoを作成
		Info* info = nullptr;
		//雲拡張子を抜いたパスを取得
		std::filesystem::path originPath(kumoPath.string().substr(0, kumoPath.string().length() - kumoPath.extension().string().length()));
		//元ファイルの種類によって様々なクラスを作成
		switch (GetFileType(originPath)) {
			case FileType::Image:
				info = new Image(originPath.string());
				break;
		}

		//作成できたなら
		if (info) {
			//マップに登録
			idInfos.insert(std::make_pair(guidStr, info));
		}
	}
}

void ProjectFileManager::WriteToKumoFile(std::filesystem::path kumoPath)
{
	//ファイルを作成、開く
	std::ofstream ofs(kumoPath.c_str());
	//開けたら
	if (ofs) {
		ofs << "guid : " + CreateGUID() << std::endl;	//guidを書き込む
		switch (GetFileType(kumoPath)) {
			case FileType::Image:
				break;
		}
	}
	else {
		Debug::Log(kumoPath.string() + "は開けませんでした。\n");
	}
}

std::string ProjectFileManager::CreateGUID()
{
	GUID guid;

	std::string guidStr;

	// GUIDの生成
	if (S_OK == CoCreateGuid(&guid)) {
		// GUIDを文字列へ変換
		stringstream stream;
		stream << std::hex << std::uppercase
			<< std::setw(8) << std::setfill('0') << guid.Data1
			<< "-" << std::setw(4) << std::setfill('0') << guid.Data2
			<< "-" << std::setw(4) << std::setfill('0') << guid.Data3
			<< "-";
		for (int i = 0; i < sizeof(guid.Data4); ++i)
		{
			if (i == 2)
				stream << "-";
			stream << std::hex << std::setw(2) << std::setfill('0') << (int)guid.Data4[i];
		}
		guidStr = stream.str();
	}
	
	return guidStr;
}

std::filesystem::path ProjectFileManager::assetFilePath;

std::filesystem::path ProjectFileManager::currentPath;

std::string ProjectFileManager::assetParentPathName = "";

std::vector<std::filesystem::path> ProjectFileManager::dragFilePathes;

std::unordered_map<std::string, Info*> ProjectFileManager::idInfos;
