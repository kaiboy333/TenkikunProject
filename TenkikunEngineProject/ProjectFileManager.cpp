#include "ProjectFileManager.h"
#include "DxLib.h"
#include <fstream>
#include <iostream>
#include "Debug.h"
#include <rpcdce.h>
#include "MyString.h"
#include "Image.h"
#include <string>
#include "Script.h"

ProjectFileManager::ProjectFileManager()
{
	//アセットのパスを作成
	assetFilePath = std::filesystem::current_path().string() + "\\Assets";
	//アセットの親の絶対パスにバックスラッシュ追加
	assetParentPathName = assetFilePath.parent_path().string() + "\\";
	//アセットフォルダが存在しないなら
	if (!std::filesystem::exists(assetFilePath)) {
		//フォルダを作成
		std::filesystem::create_directory(assetFilePath);
	}
	currentPath = assetFilePath;	//初期はアセットパス

	imageFilePath = std::filesystem::current_path().string() + "\\Images";	//Imagesフォルダパス設定

	//リソースフォルダパスを作成
	resourceFilePath = assetFilePath.string() + "\\Resources";
	//リソースフォルダが存在しないなら
	if (!std::filesystem::exists(resourceFilePath)) {
		//フォルダを作成
		std::filesystem::create_directory(resourceFilePath);
	}

	//リソースフォルダ内に入れたい画像をコピー&ペースト
	//四角の画像パスをコピー&ペースト
	std::filesystem::path copyPath = std::filesystem::path(imageFilePath.string() + "\\Square.png");
	std::filesystem::path pastePath = std::filesystem::path(resourceFilePath.string() + "\\" + copyPath.filename().string());
	if (!std::filesystem::exists(pastePath)) {
		filesystem::copy(copyPath, pastePath);
	}
	//天気くんの画像パスをコピー&ペースト
	copyPath = std::filesystem::path(imageFilePath.string() + "\\Tenkikun.png");
	pastePath = std::filesystem::path(resourceFilePath.string() + "\\" + copyPath.filename().string());
	if (!std::filesystem::exists(pastePath)) {
		filesystem::copy(copyPath, pastePath);
	}
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
		//アニメーションファイルなら
		else if (extensionName == ".anim") {
			targetFileType = FileType::Anim;
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
		std::string guidStr = MyString::Split(lines[0], ' ')[1];

		//追加で読み込んでInfoを作成
		Info* info = nullptr;
		//雲拡張子を抜いたパスを取得
		std::filesystem::path originPath(kumoPath.string().substr(0, kumoPath.string().length() - kumoPath.extension().string().length()));
		//元ファイルの種類によって様々なクラスを作成
		switch (GetFileType(originPath)) {
			case FileType::Image:
				info = new Image(originPath);	//Imageを生成
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
			std::string guid = CreateGUID();
			ofs << "guid: " << guid << std::endl;	//guidを書き込む
			switch (GetFileType(kumoPath)) {
			case FileType::Image:
				break;
			}
		}
		else {
			Debug::Log(kumoPath.string() + "は開けませんでした。");
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

		//シーン名を書き込む
		ofs << "sceneName: " << scene->GetName() << std::endl;

		for (GameObject* gameobject : scene->gameobjects) {
			//クラス名書き込む
			ofs << typeid(*gameobject).name() << std::endl;

			//ファイルIDを生成
			int fileID = GetValue<SceneInfo*, int>(fileIDs, gameobject, CreateFileID());

			//ファイルIDを書き込む
			ofs << "\tfileID: " << fileID << std::endl;

			//名前を書き込む
			ofs << "\tname: " << gameobject->GetName() << std::endl;

			//コンポーネントの数を書き込む
			ofs << "\tcomponents: " << gameobject->components.size() << std::endl;
			for (Component* component : gameobject->components) {
				//ファイルIDを取得
				fileID = GetValue<SceneInfo*, int>(fileIDs, component, CreateFileID());
				//IDを書き込む
				ofs << "\t\tcomponent: {fileID: " << fileID << " }" << std::endl;
			}

			for (Component* component : gameobject->components) {
				//クラス名書き込む
				ofs << typeid(*component).name() << std::endl;

				//ファイルIDを取得
				fileID = GetValue<SceneInfo*, int>(fileIDs, component, CreateFileID());

				//ファイルIDを書き込む
				ofs << "\tfileID: " << fileID << std::endl;

				//ゲームオブジェクトを書き込む
				ofs << "\tgameobject: {fileID: " << fileIDs[gameobject] << " }" << std::endl;

				//タイプ取得
				const std::type_info& type = typeid(*component);
				//Transformだったら
				if (type == typeid(Transform)) {
					Transform* transform = static_cast<Transform*>(component);
					//localPositionを書き込む
					Vector3 localPos = transform->localPosition;
					ofs << "\tlocalPosition: {x: " << localPos.x << " ,y: " << localPos.y << " ,z: " << localPos.z << " }" << std::endl;

					//localRotationを書き込む
					Vector3 localRote = transform->localRotation;
					ofs << "\tlocalRotation: {x: " << localRote.x << " ,y: " << localRote.y << " ,z: " << localRote.z << " }" << std::endl;

					//localScaleを書き込む
					Vector3 localScale = transform->localScale;
					ofs << "\tlocalScale: {x: " << localScale.x << " ,y: " << localScale.y << " ,z: " << localScale.z << " }" << std::endl;

					//子のTransformの数を書き込む
					ofs << "\tchildren: " << transform->children.size() << std::endl;
					//子のTransformを取得
					for (Transform* child : transform->children) {
						//子のTransformのIDを取得
						fileID = GetValue<SceneInfo*, int>(fileIDs, child, CreateFileID());
						//IDを書き込む
						ofs << "\t\tchild: fileID:{ " << fileID << " }" << std::endl;
					}

					//親のTransformのID取得
					if (transform->parent) {
						fileID = GetValue<SceneInfo*, int>(fileIDs, transform->parent, CreateFileID());
					}
					//transform->parentがnullなら
					else {
						//ファイルIDは0
						fileID = 0;
					}
					//IDを書き込む
					ofs << "\tparent: {fileID: " << fileID << " }" << std::endl;
				}
				//Cameraなら
				else if (type == typeid(Camera)) {

				}
				//ImageRendererなら
				else if (type == typeid(ImageRenderer)) {
					ImageRenderer* imageRenderer = static_cast<ImageRenderer*>(component);
					//isFlipXを書き込む
					ofs << "\tisFlipX: " << (int)imageRenderer->isFlipX << std::endl;

					//isFlipYを書き込む
					ofs << "\tisFlipY: " << (int)imageRenderer->isFlipY << std::endl;

					//imageを書き込む(guid)
					ofs << "\timage: {guid: " << imageRenderer->image->GetGUID() << " }" << std::endl;
				}
				////MonoBehaviourなら
				//else if (type == typeid(MonoBehaviour)) {
				//	MonoBehaviour* mono = static_cast<MonoBehaviour*>(component);
				//	//MonoBehaviourのfileIDを取得
				//	fileID = GetValue<SceneInfo*, int>(fileIDs, mono, CreateFileID());
				//	Type
				//	//ヘッダーとcppのIDを書き込む(fileID, guid)
				//	ofs << "mono: {fileID: " << fileID  << " ,guid: {header: " << mono->GetGUID() << " ,cpp: " << script->GetMonoBehaviour()->GetCPPGUID() << " }" << " }" << std::endl;
				//}
			}
		}
	}
}

void ProjectFileManager::LoadSceneFromFile(std::filesystem::path scenePath, Scene* scene)
{
	//行たちを読み込み
	std::vector<std::string> lines = MyString::GetLines(scenePath);
	int row = 0;
	//ファイルIDとクラスマップを作成
	std::unordered_map<int, SceneInfo*> sceneInfos;

	//シーン名取得
	scene->SetName(MyString::Split(lines[row++], ' ')[1], true);

	//読み込める限り
	while (lines.size() - 1 > row) {
		//クラス名を取得
		std::string className = lines[row++];
		SceneInfo* sceneInfo = nullptr;
		int fileID;

		//ファイルIDを取得
		fileID = std::stoi(MyString::Split(lines[row++], ' ')[1]);

		//GameObjectなら
		if (className == typeid(GameObject).name()) {
			//クラス生成
			GameObject* gameobject = static_cast<GameObject*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, scene->CreateEmpty()));
			//名前取得
			gameobject->SetName(MyString::Split(lines[row++], ' ')[1]);
			//コンポーネントの数取得
			int componentNum = std::stoi(MyString::Split(lines[row++], ' ')[1]);
			for (int i = 0; i < componentNum; i++, row++) {

			}
		}
		//Transformなら
		else if (className == typeid(Transform).name()) {
			//ゲームオブジェクトのファイルIDを取得
			fileID = std::stoi(MyString::Split(lines[row++], ' ')[2]);
			//ゲームオブジェクトを取得
			GameObject* gameobject = static_cast<GameObject*>(sceneInfos[fileID]);
			//Transformを取得
			Transform* transform = gameobject->transform;

			//localPositionをセット
			std::vector<std::string> words = MyString::Split(lines[row++], ' ');
			Vector3 localPos = Vector3(std::stof(words[2]), std::stof(words[4]), std::stof(words[6]));
			transform->localPosition = localPos;

			//localRotationをセット
			words = MyString::Split(lines[row++], ' ');
			Vector3 localRote = Vector3(std::stof(words[2]), std::stof(words[4]), std::stof(words[6]));
			transform->localRotation = localRote;

			//localScaleをセット
			words = MyString::Split(lines[row++], ' ');
			Vector3 localScale = Vector3(std::stof(words[2]), std::stof(words[4]), std::stof(words[6]));
			transform->localScale = localScale;

			//子の数セット
			int childNum = std::stoi(MyString::Split(lines[row++], ' ')[1]);
			for (int i = 0; i < childNum; i++, row++) {

			}

			//親をセット
			fileID = std::stoi(MyString::Split(lines[row++], ' ')[2]);
			Transform* parent = nullptr;
			//ファイルIDが0でないなら
			if (fileID != 0) {
				//セット
				parent = static_cast<Transform*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, new Transform()));
				//ローカルを変えずにワールドを変える
				transform->SetParent(parent, false);
			}
		}
		//Cameraなら
		else if (className == typeid(Camera).name()) {
			//ゲームオブジェクトのファイルIDを取得
			fileID = std::stoi(MyString::Split(lines[row++], ' ')[2]);
			//ゲームオブジェクトを取得
			GameObject* gameobject = static_cast<GameObject*>(sceneInfos[fileID]);
			//Cameraを作成、取得
			Camera* camera = gameobject->AddComponent<Camera>();

			//シーンにカメラを追加、設定
			scene->SetNowCamera(camera);
		}
		//ImageRendererなら
		else if (className == typeid(ImageRenderer).name()) {
			//ゲームオブジェクトのファイルIDを取得
			fileID = std::stoi(MyString::Split(lines[row++], ' ')[2]);
			//ゲームオブジェクトを取得
			GameObject* gameobject = static_cast<GameObject*>(sceneInfos[fileID]);
			//ImageRendererを作成、取得
			ImageRenderer* imageRenderer = gameobject->AddComponent<ImageRenderer>();

			//isFlipXを取得
			imageRenderer->isFlipX = (bool)(std::stoi(MyString::Split(lines[row++], ' ')[1]));

			//isFlipYを取得
			imageRenderer->isFlipY = (bool)(std::stoi(MyString::Split(lines[row++], ' ')[1]));

			//imageを取得
			imageRenderer->image = static_cast<Image*>(idInfos[MyString::Split(lines[row++], ' ')[2]]);
		}
		//else if (className == typeid(MonoBehaviour).name()) {
		//	//ゲームオブジェクトのファイルIDを取得
		//	fileID = std::stoi(MyString::Split(lines[row++], ' ')[2]);
		//	//ゲームオブジェクトを取得
		//	GameObject* gameobject = static_cast<GameObject*>(sceneInfos[fileID]);
		//	//MonoBehaviourを作成、取得
		//	MonoBehaviour* mono = gameobject->AddComponent<>();
		//}
	}
}

void ProjectFileManager::WriteToAnimFile(AnimatorController* ac)
{

}

void ProjectFileManager::LoadAnimFromFile(std::filesystem::path scenePath, AnimatorController* ac)
{

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
std::filesystem::path ProjectFileManager::resourceFilePath;
std::filesystem::path ProjectFileManager::imageFilePath;

std::filesystem::path ProjectFileManager::currentPath;

std::string ProjectFileManager::assetParentPathName = "";

std::vector<std::filesystem::path> ProjectFileManager::dragFilePathes;

std::unordered_map<std::string, Info*> ProjectFileManager::idInfos;

//ランダム生成期の初期化
std::random_device ProjectFileManager::rd;
std::default_random_engine ProjectFileManager::eng(ProjectFileManager::rd());
std::uniform_int_distribution<int> ProjectFileManager::distr(ProjectFileManager::MIN, ProjectFileManager::MAX);
