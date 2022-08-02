#include "ProjectFileManager.h"
#include "DxLib.h"
#include <fstream>
#include <iostream>
#include "Debug.h"
#include <rpcdce.h>
#include "MyString.h"
#include "Image.h"
#include "Info.h"
#include "BoxCollider.h"
#include "CircleCollider.h"

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

	//シーンフォルダパスを作成
	sceneFilePath = assetFilePath.string() + "\\Scenes";
	//シーンフォルダが存在しないなら
	if (!std::filesystem::exists(sceneFilePath)) {
		//フォルダを作成
		std::filesystem::create_directory(sceneFilePath);
	}

	

	//アセットファイルの子を見ていく
	for (filesystem::path childPath : filesystem::directory_iterator(assetFilePath)) {
		//ファイルをチェック
		CheckAddFile(childPath);
	}

	////リソースフォルダ内に入れたい画像をコピー&ペースト
	////四角の画像パスをコピー&ペースト
	//std::filesystem::path copyPath = std::filesystem::path(imageFilePath.string() + "\\Square.png");
	//std::filesystem::path pastePath = std::filesystem::path(resourceFilePath.string() + "\\" + copyPath.filename().string());
	//if (!std::filesystem::exists(pastePath)) {
	//	filesystem::copy(copyPath, pastePath);
	//}
	////天気くんの画像パスをコピー&ペースト
	//copyPath = std::filesystem::path(imageFilePath.string() + "\\Tenkikun.png");
	//pastePath = std::filesystem::path(resourceFilePath.string() + "\\" + copyPath.filename().string());
	//if (!std::filesystem::exists(pastePath)) {
	//	filesystem::copy(copyPath, pastePath);
	//}
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
			targetFileType = FileType::Animation;
		}
		//アニメーションコントローラーなら
		else if (extensionName == ".animctr") {
			targetFileType = FileType::AnimatorController;
		}
	}

	//タイプを返す
	return targetFileType;
}

bool ProjectFileManager::IsFileType(std::filesystem::path path)
{
	//ファイルタイプがなしではないならtrue
	return GetFileType(path) != FileType::None;
}

void ProjectFileManager::CreateAndLoadKumoFile(std::filesystem::path path)
{
	//ファイルタイプがないか雲ファイルなら
	if (!IsFileType(path) || GetFileType(path) == FileType::Kumo)
		//終わり
		return;

	//雲ファイルパスを作成
	std::filesystem::path kumoPath = std::filesystem::path(path.string() + ".kumo");

	//ファイルに記述する
	WriteToKumoFile(kumoPath);
	//雲ファイル読み込み
	LoadFromKumoFile(kumoPath);
}

std::string ProjectFileManager::WriteToKumoFile(std::filesystem::path kumoPath)
{
	std::string guid = "0";

	//ファイルが存在しないなら
	if (!std::filesystem::exists(kumoPath)) {
		//雲ファイルなら
		if (GetFileType(kumoPath) == FileType::Kumo) {
			//雲拡張子を抜いたパスを取得
			std::filesystem::path originPath = GetNameWithoutExtensionName(kumoPath);

			//元のパスがないなら
			if (!std::filesystem::exists(originPath)) {
				//雲ファイルを削除
				std::filesystem::remove(kumoPath);
				//おわり
				return guid;
			}

			//ファイルを作成、開く
			std::ofstream ofs(kumoPath.c_str());
			//開けたら
			if (ofs) {
				//guidを作成
				guid = CreateGUID();
				ofs << "guid: " << guid << std::endl;	//guidを書き込む
			}
			else {
				Debug::Log(kumoPath.string() + "は開けませんでした。");
			}
		}
	}
	//存在するなら
	else {
		//guidを取得
		guid = GetGUIDFromKumoFile(kumoPath);
	}

	return guid;
}

void ProjectFileManager::LoadFromKumoFile(std::filesystem::path kumoPath)
{
	//雲ファイルなら
	if (GetFileType(kumoPath) == FileType::Kumo) {
		//雲拡張子を抜いたパスを取得
		std::filesystem::path originPath = GetNameWithoutExtensionName(kumoPath);

		//行たちを読み込み
		std::vector<std::string> lines = MyString::GetLines(kumoPath);
		int row = 0;

		//guidを取得
		std::string guid = MyString::Split(lines[row++], ' ')[1];

		Info* info = nullptr;

		switch (GetFileType(originPath)) {
			case FileType::Image:
				info = new Image(originPath);
				break;
			case FileType::Animation:
				info = new Animation(originPath);
				break;
			case FileType::AnimatorController:
				info = new AnimatorController(originPath);
				break;
		}
	}
}

std::string ProjectFileManager::GetGUIDFromKumoFile(std::filesystem::path kumoPath) {
	//雲ファイルなら
	if (GetFileType(kumoPath) == FileType::Kumo) {
		//行たちを読み込み
		std::vector<std::string> lines = MyString::GetLines(kumoPath);

		//guidを取得
		return MyString::Split(lines[0], ' ')[1];
	}

	return "0";
}

void ProjectFileManager::WriteToFile() {
	for (std::pair<std::filesystem::path, Info*> pair : pathAndInfo) {
		switch (GetFileType(pair.first)) {
			case FileType::Animation:
				//アニメーションファイルを読み込む
				WriteToAnimationFile(static_cast<Animation*>(pair.second));
				break;
			case FileType::AnimatorController:
				//アニメーションコントローラーファイルを読み込む
				WriteToAnimatorControllerFile(static_cast<AnimatorController*>(pair.second));
				break;
			}
	}
}

void ProjectFileManager::LoadFromFile() {
	for (std::pair<std::string, std::filesystem::path> pair : guidAndPath) {
		switch (GetFileType(pair.second)) {
			case FileType::Animation:
				//アニメーションファイルを読み込む
				LoadFromAnimationFile(pair.second);
				break;
			case FileType::AnimatorController:
				//アニメーションコントローラーファイルを読み込む
				LoadFromAnimatorControllerFile(pair.second);
				break;
		}
	}
}

void ProjectFileManager::WriteToSceneFile(Scene* scene)
{
	int fileID;
	std::string guid;

	//シーンファイルを開く
	std::ofstream ofs(scene->scenePath);
	//開けたら
	if (ofs) {
		for (GameObject* gameobject : scene->gameobjects) {
			//クラス名書き込む
			ofs << typeid(*gameobject).name() << std::endl;

			//ファイルIDを生成
			fileID = gameobject->fileID;

			//ファイルIDを書き込む
			ofs << "\tfileID: " << fileID << std::endl;

			//名前を書き込む
			ofs << "\tname: " << gameobject->GetName() << std::endl;

			//コンポーネントの数を書き込む
			ofs << "\tcomponents: " << gameobject->components.size() << std::endl;
			for (Component* component : gameobject->components) {
				//ファイルIDを取得
				fileID = component->fileID;
				//IDを書き込む
				ofs << "\t\tcomponent: {fileID: " << fileID << " }" << std::endl;
			}

			for (Component* component : gameobject->components) {
				//クラス名書き込む
				ofs << typeid(*component).name() << std::endl;

				//ファイルIDを取得
				fileID = component->fileID;

				//ファイルIDを書き込む
				ofs << "\tfileID: " << fileID << std::endl;

				//ゲームオブジェクトのファイルIDを取得
				fileID = gameobject->fileID;
				//ゲームオブジェクトのファイルIDを書き込む
				ofs << "\tgameobject: {fileID: " << fileID << " }" << std::endl;

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
						fileID = child->fileID;
						//IDを書き込む
						ofs << "\t\tchild: fileID:{ " << fileID << " }" << std::endl;
					}

					//親のTransformのID取得
					if (transform->parent) {
						fileID = transform->parent->fileID;
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

					if (imageRenderer->image) {
						//imageのファイルID取得
						fileID = imageRenderer->image->fileID;
						//imageのguidを取得
						guid = imageRenderer->image->guid;
					}
					else {
						//fileIDを0にする
						fileID = 0;
						//guidも0
						guid = "0";
					}
					//imageを書き込む(guidも)
					ofs << "\timage: {fileID: " << fileID << " ,guid: " << guid << " }" << std::endl;
				}
				//Animatorなら
				else if (type == typeid(Animator)) {
					Animator* animator = static_cast<Animator*>(component);

					//acのファイルID取得
					fileID = animator->ac->fileID;
					//acを書き込む(guidも)
					ofs << "\tanimatorController: {fileID: " << fileID << " ,guid: " << animator->ac->guid << " }" << std::endl;

					//nowStateのファイルIDを取得
					fileID = animator->nowState->fileID;
					//nowStateのファイルIDを書き込む
					ofs << "\tnowState: {fileID: " << fileID << " }" << std::endl;

				}
				//BoxColliderなら
				else if (type == typeid(BoxCollider)) {
					BoxCollider* boxCollider = static_cast<BoxCollider*>(component);

					//offsetを書き込む
					Vector3 offset = boxCollider->offset;
					ofs << "\toffset: {x: " << offset.x << " ,y: " << offset.y << " ,z: " << offset.z << " }" << std::endl;

					//sizeを書き込む
					Vector3 size = boxCollider->size;
					ofs << "\tsize: {x: " << size.x << " ,y: " << size.y << " ,z: " << size.z << " }" << std::endl;
				}
				//CircleColliderなら
				else if (type == typeid(CircleCollider)) {
					CircleCollider* circleCollider = static_cast<CircleCollider*>(component);

					//offsetを書き込む
					Vector3 offset = circleCollider->offset;
					ofs << "\toffset: {x: " << offset.x << " ,y: " << offset.y << " ,z: " << offset.z << " }" << std::endl;

					//radiousを書き込む
					ofs << "\tradious: " << circleCollider->radious << std::endl;
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

void ProjectFileManager::LoadFromSceneFile(std::filesystem::path scenePath)
{
	//シーンを作成
	Scene* scene = new Scene();
	//シーンのパスを設定
	scene->scenePath = scenePath;
	SceneManager::SetNowScene(scene);	//登録
	scene->Init();	//初期化
	//パスのファイル名からシーン名を取得、セット
	scene->SetName(GetNameWithoutExtensionName(scenePath.filename()), true);

	//行たちを読み込み
	std::vector<std::string> lines = MyString::GetLines(scenePath);
	int row = 0;
	std::string guid;

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
			//飛ばす
			row += componentNum;
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
			//飛ばす
			row += childNum;

			//親をセット
			fileID = std::stoi(MyString::Split(lines[row++], ' ')[2]);
			Transform* parent = nullptr;
			//ファイルIDが0でないなら
			if (fileID != 0) {
				//セット
				parent = static_cast<Transform*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, new Transform(nullptr)));
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

			//imageのファイルIDを取得
			fileID = std::stoi(MyString::Split(lines[row], ' ')[2]);
			//imageのguidを取得
			guid = MyString::Split(lines[row++], ' ')[4];
			Image* image = nullptr;
			//fileID、guidともに0ではないなら
			if (fileID != 0 && guid != "0") {
				//imageを取得
				image = static_cast<Image*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, pathAndInfo[guidAndPath[guid]]));
			}
			//imageをセット
			imageRenderer->image = image;
		}
		//Animatorなら
		else if (className == typeid(Animator).name()) {
			//ゲームオブジェクトのファイルIDを取得
			fileID = std::stoi(MyString::Split(lines[row++], ' ')[2]);
			//ゲームオブジェクトを取得
			GameObject* gameobject = static_cast<GameObject*>(sceneInfos[fileID]);
			//Animatorを作成、取得
			Animator* animator = gameobject->AddComponent<Animator>();

			//acのファイルIDを取得
			fileID = std::stoi(MyString::Split(lines[row], ' ')[2]);
			//acのguidを取得
			guid = MyString::Split(lines[row++], ' ')[4];
			//acを取得、リストにも登録
			AnimatorController* ac = static_cast<AnimatorController*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, pathAndInfo[guidAndPath[guid]]));
			//acをセット
			animator->ac = ac;

			//nowStateのファイルIDを取得
			fileID = std::stoi(MyString::Split(lines[row++], ' ')[2]);
			//nowStateをセット
			animator->nowState = static_cast<AnimationState*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, new AnimationState()));
		}
		else if (className == typeid(BoxCollider).name()) {
			//ゲームオブジェクトのファイルIDを取得
			fileID = std::stoi(MyString::Split(lines[row++], ' ')[2]);
			//ゲームオブジェクトを取得
			GameObject* gameobject = static_cast<GameObject*>(sceneInfos[fileID]);
			//BoxColliderを作成、取得
			BoxCollider* boxCollider = gameobject->AddComponent<BoxCollider>();

			//offsetを取得
			std::vector<std::string> words = MyString::Split(lines[row++], ' ');
			Vector3 offset = Vector3(std::stof(words[2]), std::stof(words[4]), std::stof(words[6]));
			//offsetをセット
			boxCollider->offset = offset;

			//sizeを取得
			words = MyString::Split(lines[row++], ' ');
			Vector3 size = Vector3(std::stof(words[2]), std::stof(words[4]), std::stof(words[6]));
			//sizeをセット
			boxCollider->size = size;
		}
		else if (className == typeid(CircleCollider).name()) {
			//ゲームオブジェクトのファイルIDを取得
			fileID = std::stoi(MyString::Split(lines[row++], ' ')[2]);
			//ゲームオブジェクトを取得
			GameObject* gameobject = static_cast<GameObject*>(sceneInfos[fileID]);
			//BoxColliderを作成、取得
			CircleCollider* circleCollider = gameobject->AddComponent<CircleCollider>();

			//offsetを取得
			std::vector<std::string> words = MyString::Split(lines[row++], ' ');
			Vector3 offset = Vector3(std::stof(words[2]), std::stof(words[4]), std::stof(words[6]));
			//offsetをセット
			circleCollider->offset = offset;

			//radiousをセット
			circleCollider->radious = std::stof(MyString::Split(lines[row++], ' ')[1]);
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

void ProjectFileManager::WriteToAnimatorControllerFile(AnimatorController* ac)
{
	//アニメーションコントローラーファイルを開く
	std::ofstream ofs(ac->path);
	//開けたら
	if (ofs) {
		//ファイルID
		int fileID;
		//guid
		std::string guid;

		//AnimatorController
		//クラス名書き込む
		ofs << typeid(*ac).name() << std::endl;

		//ファイルIDを取得
		fileID = ac->fileID;
		//ファイルIDを書き込む
		ofs << "\tfileID: " << fileID << std::endl;

		//paramatersの数を書き込む
		ofs << "\tparamaters: " << (int)ac->paramaters.size() << std::endl;
		for (AnimationParamater* paramater : ac->paramaters) {
			//paramaterのファイルIDを取得
			fileID = paramater->fileID;
			//paramaterのファイルIDを書き込む
			ofs << "\t\tparamater: {fileID: " << fileID << " }" << std::endl;
		}

		//statesの数を書き込む
		ofs << "\tstates: " << (int)ac->states.size() << std::endl;
		for (AnimationState* state : ac->states) {
			//stateのファイルIDを取得
			fileID = state->fileID;
			//paramaterのファイルIDを書き込む
			ofs << "\t\tstate: {fileID: " << fileID << " }" << std::endl;
		}

		//AnimationParamater
		for (AnimationParamater* paramater : ac->paramaters) {

			//クラス名書き込む
			ofs << typeid(*paramater).name() << std::endl;

			//ファイルIDを生成
			fileID = paramater->fileID;
			//ファイルIDを書き込む
			ofs << "\tfileID: " << fileID << std::endl;

			//名前を書き込む
			ofs << "\tname: " << paramater->name << std::endl;

			//typeを書き込む
			ofs << "\ttype: " << (int)paramater->type << std::endl;

			//intValueを書き込む
			ofs << "\tintValue: " << paramater->intValue << std::endl;

			//floatValueを書き込む
			ofs << "\tfloatValue: " << paramater->floatValue << std::endl;

			//boolValueを書き込む
			ofs << "\tboolValue: " << (int)paramater->boolValue << std::endl;
		}

		//AnimationState
		for (AnimationState* state : ac->states) {
			//クラス名書き込む
			ofs << typeid(*state).name() << std::endl;

			//ファイルIDを生成
			fileID = state->fileID;
			//ファイルIDを書き込む
			ofs << "\tfileID: " << fileID << std::endl;

			//animationのファイルIDを取得
			fileID = state->animation->fileID;
			//animationのguidを取得
			guid = state->animation->guid;
			//animationを書き込む(guidも)
			ofs << "\tanimation: {fileID: " << fileID << " ,guid: " << state->animation->guid << " }" << std::endl;

			//nameを書き込む
			ofs << "\tname: " << state->name << std::endl;

			//speedを書き込む
			ofs << "\tspeed: " << state->speed << std::endl;

			//transitionsのサイズを書き込む
			ofs << "\ttransitions: " << (int)state->transitions.size() << std::endl;
			for (AnimationTransition* transition : state->transitions) {
				//transitionのファイルIDを取得
				fileID = transition->fileID;
				//transitionのファイルIDを書き込む
				ofs << "\t\ttransition: {fileID: " << fileID << " }" << std::endl;
			}

			for (AnimationTransition* transition : state->transitions) {
				//AnimationTransition
				//クラス名書き込む
				ofs << typeid(*transition).name() << std::endl;

				//ファイルIDを生成
				fileID = transition->fileID;
				//ファイルIDを書き込む
				ofs << "\tfileID: " << fileID << std::endl;

				//fromStateのファイルIDを取得
				fileID = transition->fromState->fileID;
				//fromStateのファイルIDを書き込む
				ofs << "\tfromState: {fileID: " << fileID << " }" << std::endl;

				//toStateのファイルIDを取得
				fileID = transition->toState->fileID;
				//toStateのファイルIDを書き込む
				ofs << "\ttoState: {fileID: " << fileID << " }" << std::endl;

				//conditionsの数を書き込む
				ofs << "\tconditions: " << (int)transition->conditions.size() << std::endl;
				for (AnimationCondition* condition : transition->conditions) {
					//conditionのファイルIDを取得
					fileID = condition->fileID;
					//conditionのファイルIDを書き込む
					ofs << "\t\tcondition: {fileID: " << fileID << " }" << std::endl;
				}

				//AnimationCondition
				for (AnimationCondition* condition : transition->conditions) {
					//クラス名書き込む
					ofs << typeid(*condition).name() << std::endl;

					//ファイルIDを取得
					fileID = condition->fileID;
					//ファイルIDを書き込む
					ofs << "\tfileID: " << fileID << std::endl;

					//nameを書き込む
					ofs << "\tname: " << condition->name << std::endl;

					//modeを書き込む
					ofs << "\tmode: " << (int)condition->mode << std::endl;

					//valueを書き込む
					ofs << "\tvalue: " << condition->value << std::endl;
				}
			}
		}
	}
}

void ProjectFileManager::LoadFromAnimatorControllerFile(std::filesystem::path acPath)
{
	//行たちを読み込み
	std::vector<std::string> lines = MyString::GetLines(acPath);
	int row = 0;
	std::string guid;

	//読み込める限り
	while (lines.size() - 1 > row) {
		int fileID;
		std::string guid;

		//クラス名を取得
		std::string className = lines[row++];

		//ファイルIDを取得
		fileID = std::stoi(MyString::Split(lines[row++], ' ')[1]);

		//AnimatorControllerなら
		if (className == typeid(AnimatorController).name()) {
			//AnimatorControllerを取得
			AnimatorController* ac = static_cast<AnimatorController*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, pathAndInfo[acPath]));

			//animationparamatersの数を取得
			int paramaterNum = std::stoi(MyString::Split(lines[row++], ' ')[1]);
			for (int i = 0; i < paramaterNum; i++) {
				//paramaterのファイルIDを取得
				fileID = std::stoi(MyString::Split(lines[row++], ' ')[2]);
				//paramaterを取得
				AnimationParamater* paramater = static_cast<AnimationParamater*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, new AnimationParamater()));
				//paramaterをリストに追加
				ac->paramaters.push_back(paramater);
			}

			//statesの数を取得
			int stateNum = std::stoi(MyString::Split(lines[row++], ' ')[1]);
			for (int i = 0; i < stateNum; i++) {
				//stateのファイルIDを取得
				fileID = std::stoi(MyString::Split(lines[row++], ' ')[2]);
				//stateを取得
				AnimationState* state = static_cast<AnimationState*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, new AnimationState()));
				//stateをリストに追加
				ac->states.push_back(state);
			}
		}
		//AnimationParamaterなら
		else if (className == typeid(AnimationParamater).name()) {
			//AnimationParamater生成
			AnimationParamater* paramater = static_cast<AnimationParamater*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, new AnimationParamater()));

			//名前をセット
			paramater->name = MyString::Split(lines[row++], ' ')[1];

			//typeをセット
			paramater->type = (AnimationParamater::Type)std::stoi(MyString::Split(lines[row++], ' ')[1]);

			//intValueをセット
			paramater->intValue = std::stoi(MyString::Split(lines[row++], ' ')[1]);

			//floatValueを書き込む
			paramater->floatValue = std::stof(MyString::Split(lines[row++], ' ')[1]);

			//boolValueを書き込む
			paramater->boolValue = (bool)std::stoi(MyString::Split(lines[row++], ' ')[1]);
		}
		//AnimationStateなら
		else if (className == typeid(AnimationState).name()) {
			//AnimationState生成
			AnimationState* state = static_cast<AnimationState*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, new AnimationState()));

			//animationのファイルIDを取得
			fileID = std::stoi(MyString::Split(lines[row], ' ')[2]);
			//animationのguidを取得
			guid = MyString::Split(lines[row++], ' ')[4];
			//animationセット
			//std::filesystem::path path = guidAndPath[guid];
			//Info* info = pathAndInfo[path];
			state->animation = static_cast<Animation*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, pathAndInfo[guidAndPath[guid]]));

			//名前をセット
			state->name = MyString::Split(lines[row++], ' ')[1];

			//speedをセット
			state->speed = std::stof(MyString::Split(lines[row++], ' ')[1]);

			//transitionsの数を取得
			int transitionNum = std::stoi(MyString::Split(lines[row++], ' ')[1]);
			for (int i = 0; i < transitionNum; i++) {
				//transitionのファイルIDを取得
				fileID = std::stoi(MyString::Split(lines[row++], ' ')[2]);
				//transitionを取得
				AnimationTransition* transition = static_cast<AnimationTransition*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, new AnimationTransition()));
				//transitionをセット
				state->transitions.push_back(transition);
			}
		}
		//AnimationTransition
		else if (className == typeid(AnimationTransition).name()) {
			//AnimationTransition生成
			AnimationTransition* transition = static_cast<AnimationTransition*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, new AnimationTransition()));

			//fromStateのファイルIDを取得
			fileID = std::stoi(MyString::Split(lines[row++], ' ')[2]);
			//fromStateをセット
			transition->fromState = static_cast<AnimationState*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, new AnimationState()));

			//toStateのファイルIDを取得
			fileID = std::stoi(MyString::Split(lines[row++], ' ')[2]);
			//toStateをセット
			transition->toState = static_cast<AnimationState*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, new AnimationState()));

			//conditionsの数を取得
			int conditionNum = std::stoi(MyString::Split(lines[row++], ' ')[1]);
			for (int i = 0; i < conditionNum; i++) {
				//conditionのファイルIDを取得
				fileID = std::stoi(MyString::Split(lines[row++], ' ')[2]);
				//conditionを取得
				AnimationCondition* condition = static_cast<AnimationCondition*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, new AnimationCondition()));
				//conditionをセット
				transition->conditions.push_back(condition);
			}
		}
		//AnimationCondition
		else if (className == typeid(AnimationCondition).name()) {
			//AnimationCondition生成
			AnimationCondition* condition = static_cast<AnimationCondition*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, new AnimationCondition()));

			//nameをセット
			condition->name = MyString::Split(lines[row++], ' ')[1];

			//modeをセット
			condition->mode = (AnimationCondition::Mode)std::stoi(MyString::Split(lines[row++], ' ')[1]);

			//valueをセット
			condition->value = std::stof(MyString::Split(lines[row++], ' ')[1]);
		}
	}
}

void ProjectFileManager::WriteToAnimationFile(Animation* animation)
{
	int fileID;
	std::string guid;

	//シーンファイルを開く
	std::ofstream ofs(animation->path);
	//開けたら
	if (ofs) {
		//クラス名を書き込む
		ofs <<  typeid(*animation).name() << std::endl;

		//ファイルIDを取得
		fileID = animation->fileID;
		//ファイルIDを書き込む
		ofs << "\tfileID: " << fileID << std::endl;

		////nameを書き込む
		//ofs << "\tname: " << animation->name << std::endl;

		//animationKeyのマップの数を書き込む
		ofs << "\tanimationKeys: " << (int)animation->animationKeys.size() << std::endl;
		for (std::pair<int, Image*> animationKey : animation->animationKeys) {
			//animationKeyを書き込む
			ofs << "\t\tanimationKey:" << std::endl;

			//フレーム数を書き込む
			ofs << "\t\t\ttime: " << animationKey.first << std::endl;

			//ImageのファイルIDを取得
			fileID = animationKey.second->fileID;
			//Imageのguidを取得
			std::string guid = animationKey.second->guid;
			//Imageを書き込む(guid)
			ofs << "\t\t\timage: {fileID: " << fileID << " ,guid: " << guid << " }" << std::endl;
		}

		//isLoopを書き込む
		ofs << "\tisLoop: " << (int)animation->isLoop << std::endl;
	}
}

void ProjectFileManager::LoadFromAnimationFile(std::filesystem::path animationPath)
{
	//ファイルを開く
	std::ifstream ifs(animationPath.c_str());
	int fileID;
	std::string guid;

	//開けたら
	if (ifs) {
		//行たちを読み込み
		std::vector<std::string> lines = MyString::GetLines(animationPath);
		int row = 0;

		//クラス名を取得
		std::string className = lines[row++];
		//クラス名がアニメーションなら
		if (className == typeid(Animation).name()) {
			//ファイルIDを取得
			fileID = std::stoi(MyString::Split(lines[row++], ' ')[1]);
			//アニメーションを取得
			Animation* animation = static_cast<Animation*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, pathAndInfo[animationPath]));

			////名前をセット
			//animation->name = MyString::Split(lines[row++], ' ')[1];

			////パスを設定
			//animation->path = animationPath;

			//animationKeyのマップの数を取得
			int animationKeyNum = std::stoi(MyString::Split(lines[row++], ' ')[1]);
			for (int i = 0; i < animationKeyNum; i++) {
				row++;	//1行飛ばす
				//フレーム数を取得
				int time = std::stoi(MyString::Split(lines[row++], ' ')[1]);
				//imageのファイルIDを取得
				fileID = std::stoi(MyString::Split(lines[row], ' ')[2]);
				//imageのguidを取得
				std::string guid = MyString::Split(lines[row++], ' ')[4];
				//imageを取得
				Image* image = static_cast<Image*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, pathAndInfo[guidAndPath[guid]]));
				//timeとimage(animationKey)をセット
				animation->animationKeys.insert(std::make_pair(time, image));
			}

			//isLoopをセット
			animation->isLoop = (bool)std::stoi(MyString::Split(lines[row++], ' ')[1]);

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

std::string ProjectFileManager::GetNameWithoutExtensionName(std::filesystem::path path)
{
	return path.string().substr(0, path.string().length() - path.extension().string().length());
}

void ProjectFileManager::CheckAddFile(std::filesystem::path path)
{
	//アセットファイルだったら終わり
	if (path == assetFilePath)
		return;

	vector<filesystem::path> pathes;

	pathes.push_back(path);

	//ツリーリストにアセットのパスを追加
	while (pathes.size() != 0) {
		filesystem::path path = pathes[0];
		pathes.erase(pathes.begin());

		//雲ファイルがなければ作成、読み込み
		CreateAndLoadKumoFile(path);

		//パスがディレクトリだったら
		if (filesystem::is_directory(path)) {
			//子をリストに追加
			for (filesystem::path childPath : filesystem::directory_iterator(path)) {
				pathes.push_back(childPath);
			}
		}
		else {
			//ファイルがシーンファイルなら
			if (GetFileType(path) == FileType::Scene) {
				//ファイル名を取得
				std::string sceneName = GetNameWithoutExtensionName(path.filename());
				//シーンのマップに無かったら
				if (!SceneManager::scenePathes.contains(sceneName)) {
					//シーンマネージャーのリストに追加
					SceneManager::scenePathes.insert(std::make_pair(sceneName, path));
				}
			}
		}
	}
}

std::filesystem::path ProjectFileManager::assetFilePath;
std::filesystem::path ProjectFileManager::resourceFilePath;
std::filesystem::path ProjectFileManager::imageFilePath;
std::filesystem::path ProjectFileManager::sceneFilePath;

std::filesystem::path ProjectFileManager::currentPath;

std::string ProjectFileManager::assetParentPathName = "";

std::vector<std::filesystem::path> ProjectFileManager::dragFilePathes;

std::map<std::filesystem::path, Info*> ProjectFileManager::pathAndInfo;

std::map<int, SceneInfo*> ProjectFileManager::sceneInfos;

std::map<std::string, std::filesystem::path> ProjectFileManager::guidAndPath;

//ランダム生成期の初期化
std::random_device ProjectFileManager::rd;
std::default_random_engine ProjectFileManager::eng(ProjectFileManager::rd());
std::uniform_int_distribution<int> ProjectFileManager::distr(ProjectFileManager::MIN, ProjectFileManager::MAX);