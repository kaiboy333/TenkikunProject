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
		//シーンファイルなら
		else if (extensionName == ".scene") {
			targetFileType = FileType::Scene;
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
			//Infoにguidをセット
			info->SetGUID(guidStr);
			//マップに登録
			idInfos.insert(std::make_pair(guidStr, info));
		}
	}
}

void ProjectFileManager::WriteToKumoFile(std::filesystem::path kumoPath)
{
	//雲ファイルなら
	if (GetFileType(kumoPath) == FileType::Kumo) {
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
}

void ProjectFileManager::WriteToSceneFile(Scene* scene)
{
	//シーンファイルを開く
	std::ofstream ofs(scene->scenePath);
	//開けたら
	if (ofs) {
		//クラスとファイルIDのマップを作成
		std::unordered_map<SceneInfo*, int> fileIDs;

		for (GameObject* gameobject : scene->gameobjects) {
			//クラス名書き込む
			ofs << typeid(gameobject).name() << std::endl;
			//ファイルIDを生成
			int fileID = CreateFileID();
			//マップに追加
			fileIDs.insert(std::make_pair(gameobject, fileID));

			//ファイルIDを書き込む
			ofs << "fileID : " << fileID << std::endl;
			//名前を書き込む
			ofs << gameobject->GetName() << std::endl;
			//コンポーネントを書き込む
			ofs << "components :" << std::endl;
			for (Component* component : gameobject->components) {
				//コンポーネントのファイルIDが生成されていないなら
				if (!fileIDs.contains(component)) {
					//IDを作成
					fileID++;
					//マップに追加
					fileIDs.insert(std::make_pair(component, fileID));
				}
				//そのIDを書き込む
				ofs << " component : {fileID : " << fileIDs[component] << "}" << std::endl;
			}

			for (Component* component : gameobject->components) {
				//クラス名書き込む
				ofs << typeid(component).name() << std::endl;
				//ファイルIDを書き込む
				ofs << "fileID : " << fileIDs[component] << std::endl;
				//ゲームオブジェクトを書き込む
				ofs << "gameobject : {fileID : " << fileIDs[gameobject] << "}" << std::endl;

				//タイプ取得
				const std::type_info& type = typeid(*component);
				//Transformだったら
				if (type == typeid(Transform)) {
					Transform* transform = static_cast<Transform*>(component);
					//localPositionを書き込む
					Vector3 localPos = transform->localPosition;
					ofs << "localPosition : {x : " << localPos.x << ", y : " << localPos.y << ", z : " << localPos.z << "}";
					//localRotationを書き込む
					Vector3 localRote = transform->localRotation;
					ofs << "localRotation : {x : " << localRote.x << ", y : " << localRote.y << ", z : " << localRote.z << "}";
					//localScaleを書き込む
					Vector3 localScale = transform->localScale;
					ofs << "localScale : {x : " << localScale.x << ", y : " << localScale.y << ", z : " << localScale.z << "}";
				}
				//Cameraなら
				else if (type == typeid(Camera)) {

				}
				//ImageRendererなら
				else if (type == typeid(ImageRenderer)) {
					ImageRenderer* imageRenderer = static_cast<ImageRenderer*>(component);
					//isFlipXを書き込む
					ofs << "isFlipX : " << (int)imageRenderer->isFlipX << std::endl;
					//isFlipYを書き込む
					ofs << "isFlipY : " << (int)imageRenderer->isFlipY << std::endl;
					//imageを書き込む(guid)
					ofs << "image : {guid : " << imageRenderer->image->GetGUID() << "}" << std::endl;
				}
			}
		}
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

int ProjectFileManager::CreateFileID()
{
	//ランダムに生成
	return distr(eng);
}

std::filesystem::path ProjectFileManager::assetFilePath;

std::filesystem::path ProjectFileManager::currentPath;

std::string ProjectFileManager::assetParentPathName = "";

std::vector<std::filesystem::path> ProjectFileManager::dragFilePathes;

std::unordered_map<std::string, Info*> ProjectFileManager::idInfos;

//ランダム生成期の初期化
std::random_device ProjectFileManager::rd;
std::default_random_engine ProjectFileManager::eng = std::default_random_engine(rd);
std::uniform_int_distribution<int> ProjectFileManager::distr = std::uniform_int_distribution<int>(ProjectFileManager::MIN, ProjectFileManager::MAX);
