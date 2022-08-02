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
	//�A�Z�b�g�̃p�X���쐬
	assetFilePath = std::filesystem::current_path().string() + "\\Assets";
	//�A�Z�b�g�̐e�̐�΃p�X�Ƀo�b�N�X���b�V���ǉ�
	assetParentPathName = assetFilePath.parent_path().string() + "\\";
	//�A�Z�b�g�t�H���_�����݂��Ȃ��Ȃ�
	if (!std::filesystem::exists(assetFilePath)) {
		//�t�H���_���쐬
		std::filesystem::create_directory(assetFilePath);
	}
	currentPath = assetFilePath;	//�����̓A�Z�b�g�p�X

	imageFilePath = std::filesystem::current_path().string() + "\\Images";	//Images�t�H���_�p�X�ݒ�

	//���\�[�X�t�H���_�p�X���쐬
	resourceFilePath = assetFilePath.string() + "\\Resources";
	//���\�[�X�t�H���_�����݂��Ȃ��Ȃ�
	if (!std::filesystem::exists(resourceFilePath)) {
		//�t�H���_���쐬
		std::filesystem::create_directory(resourceFilePath);
	}

	//�V�[���t�H���_�p�X���쐬
	sceneFilePath = assetFilePath.string() + "\\Scenes";
	//�V�[���t�H���_�����݂��Ȃ��Ȃ�
	if (!std::filesystem::exists(sceneFilePath)) {
		//�t�H���_���쐬
		std::filesystem::create_directory(sceneFilePath);
	}

	

	//�A�Z�b�g�t�@�C���̎q�����Ă���
	for (filesystem::path childPath : filesystem::directory_iterator(assetFilePath)) {
		//�t�@�C�����`�F�b�N
		CheckAddFile(childPath);
	}

	////���\�[�X�t�H���_���ɓ��ꂽ���摜���R�s�[&�y�[�X�g
	////�l�p�̉摜�p�X���R�s�[&�y�[�X�g
	//std::filesystem::path copyPath = std::filesystem::path(imageFilePath.string() + "\\Square.png");
	//std::filesystem::path pastePath = std::filesystem::path(resourceFilePath.string() + "\\" + copyPath.filename().string());
	//if (!std::filesystem::exists(pastePath)) {
	//	filesystem::copy(copyPath, pastePath);
	//}
	////�V�C����̉摜�p�X���R�s�[&�y�[�X�g
	//copyPath = std::filesystem::path(imageFilePath.string() + "\\Tenkikun.png");
	//pastePath = std::filesystem::path(resourceFilePath.string() + "\\" + copyPath.filename().string());
	//if (!std::filesystem::exists(pastePath)) {
	//	filesystem::copy(copyPath, pastePath);
	//}
}

void ProjectFileManager::Update()
{
	//�h���b�O�t�@�C�����X�g�̃��Z�b�g
	dragFilePathes.clear();
	//�h���b�O����Ă���t�@�C��������Ȃ�
	if (GetDragFileNum != 0) {
		for (int i = 0; i < GetDragFileNum(); i++) {
			TCHAR currentPath[100] = {};
			//�ǂݍ��߂���
			if (GetDragFilePath(currentPath) != -1) {
				//�h���b�O���ꂽ�t�@�C���̃p�X���쐬
				std::filesystem::path path = std::filesystem::path(std::string(currentPath));
				//���X�g�ɒǉ�
				dragFilePathes.push_back(path);
			}
		}
	}
}

ProjectFileManager::FileType ProjectFileManager::GetFileType(std::filesystem::path path) {
	//�p�X�̊g���q���擾
	std::string extensionName = path.extension().string();

	//������
	FileType targetFileType = FileType::None;

	//�p�X���f�B���N�g����������
	if (std::filesystem::is_directory(path)) {
		targetFileType = FileType::Folder;
	}
	else {
		//�摜��������
		if (extensionName == ".png" || extensionName == ".jpg") {
			targetFileType = FileType::Image;
		}
		//�X�N���v�g��������(cpp)
		else if (extensionName == ".cpp") {
			targetFileType = FileType::Script_cpp;
		}
		//�X�N���v�g��������(hpp)
		else if (extensionName == ".hpp") {
			targetFileType = FileType::Script_hpp;
		}
		//�X�N���v�g��������(h)
		else if (extensionName == ".h") {
			targetFileType = FileType::Script_h;
		}
		//�_�t�@�C���Ȃ�
		else if (extensionName == ".kumo") {
			targetFileType = FileType::Kumo;
		}
		//�V�[���t�@�C���Ȃ�
		else if (extensionName == ".scene") {
			targetFileType = FileType::Scene;
		}
		//�A�j���[�V�����t�@�C���Ȃ�
		else if (extensionName == ".anim") {
			targetFileType = FileType::Animation;
		}
		//�A�j���[�V�����R���g���[���[�Ȃ�
		else if (extensionName == ".animctr") {
			targetFileType = FileType::AnimatorController;
		}
	}

	//�^�C�v��Ԃ�
	return targetFileType;
}

bool ProjectFileManager::IsFileType(std::filesystem::path path)
{
	//�t�@�C���^�C�v���Ȃ��ł͂Ȃ��Ȃ�true
	return GetFileType(path) != FileType::None;
}

void ProjectFileManager::CreateAndLoadKumoFile(std::filesystem::path path)
{
	//�t�@�C���^�C�v���Ȃ����_�t�@�C���Ȃ�
	if (!IsFileType(path) || GetFileType(path) == FileType::Kumo)
		//�I���
		return;

	//�_�t�@�C���p�X���쐬
	std::filesystem::path kumoPath = std::filesystem::path(path.string() + ".kumo");

	//�t�@�C���ɋL�q����
	WriteToKumoFile(kumoPath);
	//�_�t�@�C���ǂݍ���
	LoadFromKumoFile(kumoPath);
}

std::string ProjectFileManager::WriteToKumoFile(std::filesystem::path kumoPath)
{
	std::string guid = "0";

	//�t�@�C�������݂��Ȃ��Ȃ�
	if (!std::filesystem::exists(kumoPath)) {
		//�_�t�@�C���Ȃ�
		if (GetFileType(kumoPath) == FileType::Kumo) {
			//�_�g���q�𔲂����p�X���擾
			std::filesystem::path originPath = GetNameWithoutExtensionName(kumoPath);

			//���̃p�X���Ȃ��Ȃ�
			if (!std::filesystem::exists(originPath)) {
				//�_�t�@�C�����폜
				std::filesystem::remove(kumoPath);
				//�����
				return guid;
			}

			//�t�@�C�����쐬�A�J��
			std::ofstream ofs(kumoPath.c_str());
			//�J������
			if (ofs) {
				//guid���쐬
				guid = CreateGUID();
				ofs << "guid: " << guid << std::endl;	//guid����������
			}
			else {
				Debug::Log(kumoPath.string() + "�͊J���܂���ł����B");
			}
		}
	}
	//���݂���Ȃ�
	else {
		//guid���擾
		guid = GetGUIDFromKumoFile(kumoPath);
	}

	return guid;
}

void ProjectFileManager::LoadFromKumoFile(std::filesystem::path kumoPath)
{
	//�_�t�@�C���Ȃ�
	if (GetFileType(kumoPath) == FileType::Kumo) {
		//�_�g���q�𔲂����p�X���擾
		std::filesystem::path originPath = GetNameWithoutExtensionName(kumoPath);

		//�s������ǂݍ���
		std::vector<std::string> lines = MyString::GetLines(kumoPath);
		int row = 0;

		//guid���擾
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
	//�_�t�@�C���Ȃ�
	if (GetFileType(kumoPath) == FileType::Kumo) {
		//�s������ǂݍ���
		std::vector<std::string> lines = MyString::GetLines(kumoPath);

		//guid���擾
		return MyString::Split(lines[0], ' ')[1];
	}

	return "0";
}

void ProjectFileManager::WriteToFile() {
	for (std::pair<std::filesystem::path, Info*> pair : pathAndInfo) {
		switch (GetFileType(pair.first)) {
			case FileType::Animation:
				//�A�j���[�V�����t�@�C����ǂݍ���
				WriteToAnimationFile(static_cast<Animation*>(pair.second));
				break;
			case FileType::AnimatorController:
				//�A�j���[�V�����R���g���[���[�t�@�C����ǂݍ���
				WriteToAnimatorControllerFile(static_cast<AnimatorController*>(pair.second));
				break;
			}
	}
}

void ProjectFileManager::LoadFromFile() {
	for (std::pair<std::string, std::filesystem::path> pair : guidAndPath) {
		switch (GetFileType(pair.second)) {
			case FileType::Animation:
				//�A�j���[�V�����t�@�C����ǂݍ���
				LoadFromAnimationFile(pair.second);
				break;
			case FileType::AnimatorController:
				//�A�j���[�V�����R���g���[���[�t�@�C����ǂݍ���
				LoadFromAnimatorControllerFile(pair.second);
				break;
		}
	}
}

void ProjectFileManager::WriteToSceneFile(Scene* scene)
{
	int fileID;
	std::string guid;

	//�V�[���t�@�C�����J��
	std::ofstream ofs(scene->scenePath);
	//�J������
	if (ofs) {
		for (GameObject* gameobject : scene->gameobjects) {
			//�N���X����������
			ofs << typeid(*gameobject).name() << std::endl;

			//�t�@�C��ID�𐶐�
			fileID = gameobject->fileID;

			//�t�@�C��ID����������
			ofs << "\tfileID: " << fileID << std::endl;

			//���O����������
			ofs << "\tname: " << gameobject->GetName() << std::endl;

			//�R���|�[�l���g�̐�����������
			ofs << "\tcomponents: " << gameobject->components.size() << std::endl;
			for (Component* component : gameobject->components) {
				//�t�@�C��ID���擾
				fileID = component->fileID;
				//ID����������
				ofs << "\t\tcomponent: {fileID: " << fileID << " }" << std::endl;
			}

			for (Component* component : gameobject->components) {
				//�N���X����������
				ofs << typeid(*component).name() << std::endl;

				//�t�@�C��ID���擾
				fileID = component->fileID;

				//�t�@�C��ID����������
				ofs << "\tfileID: " << fileID << std::endl;

				//�Q�[���I�u�W�F�N�g�̃t�@�C��ID���擾
				fileID = gameobject->fileID;
				//�Q�[���I�u�W�F�N�g�̃t�@�C��ID����������
				ofs << "\tgameobject: {fileID: " << fileID << " }" << std::endl;

				//�^�C�v�擾
				const std::type_info& type = typeid(*component);
				//Transform��������
				if (type == typeid(Transform)) {
					Transform* transform = static_cast<Transform*>(component);
					//localPosition����������
					Vector3 localPos = transform->localPosition;
					ofs << "\tlocalPosition: {x: " << localPos.x << " ,y: " << localPos.y << " ,z: " << localPos.z << " }" << std::endl;

					//localRotation����������
					Vector3 localRote = transform->localRotation;
					ofs << "\tlocalRotation: {x: " << localRote.x << " ,y: " << localRote.y << " ,z: " << localRote.z << " }" << std::endl;

					//localScale����������
					Vector3 localScale = transform->localScale;
					ofs << "\tlocalScale: {x: " << localScale.x << " ,y: " << localScale.y << " ,z: " << localScale.z << " }" << std::endl;

					//�q��Transform�̐�����������
					ofs << "\tchildren: " << transform->children.size() << std::endl;
					//�q��Transform���擾
					for (Transform* child : transform->children) {
						//�q��Transform��ID���擾
						fileID = child->fileID;
						//ID����������
						ofs << "\t\tchild: fileID:{ " << fileID << " }" << std::endl;
					}

					//�e��Transform��ID�擾
					if (transform->parent) {
						fileID = transform->parent->fileID;
					}
					//transform->parent��null�Ȃ�
					else {
						//�t�@�C��ID��0
						fileID = 0;
					}
					//ID����������
					ofs << "\tparent: {fileID: " << fileID << " }" << std::endl;
				}
				//Camera�Ȃ�
				else if (type == typeid(Camera)) {

				}
				//ImageRenderer�Ȃ�
				else if (type == typeid(ImageRenderer)) {
					ImageRenderer* imageRenderer = static_cast<ImageRenderer*>(component);
					//isFlipX����������
					ofs << "\tisFlipX: " << (int)imageRenderer->isFlipX << std::endl;

					//isFlipY����������
					ofs << "\tisFlipY: " << (int)imageRenderer->isFlipY << std::endl;

					if (imageRenderer->image) {
						//image�̃t�@�C��ID�擾
						fileID = imageRenderer->image->fileID;
						//image��guid���擾
						guid = imageRenderer->image->guid;
					}
					else {
						//fileID��0�ɂ���
						fileID = 0;
						//guid��0
						guid = "0";
					}
					//image����������(guid��)
					ofs << "\timage: {fileID: " << fileID << " ,guid: " << guid << " }" << std::endl;
				}
				//Animator�Ȃ�
				else if (type == typeid(Animator)) {
					Animator* animator = static_cast<Animator*>(component);

					//ac�̃t�@�C��ID�擾
					fileID = animator->ac->fileID;
					//ac����������(guid��)
					ofs << "\tanimatorController: {fileID: " << fileID << " ,guid: " << animator->ac->guid << " }" << std::endl;

					//nowState�̃t�@�C��ID���擾
					fileID = animator->nowState->fileID;
					//nowState�̃t�@�C��ID����������
					ofs << "\tnowState: {fileID: " << fileID << " }" << std::endl;

				}
				//BoxCollider�Ȃ�
				else if (type == typeid(BoxCollider)) {
					BoxCollider* boxCollider = static_cast<BoxCollider*>(component);

					//offset����������
					Vector3 offset = boxCollider->offset;
					ofs << "\toffset: {x: " << offset.x << " ,y: " << offset.y << " ,z: " << offset.z << " }" << std::endl;

					//size����������
					Vector3 size = boxCollider->size;
					ofs << "\tsize: {x: " << size.x << " ,y: " << size.y << " ,z: " << size.z << " }" << std::endl;
				}
				//CircleCollider�Ȃ�
				else if (type == typeid(CircleCollider)) {
					CircleCollider* circleCollider = static_cast<CircleCollider*>(component);

					//offset����������
					Vector3 offset = circleCollider->offset;
					ofs << "\toffset: {x: " << offset.x << " ,y: " << offset.y << " ,z: " << offset.z << " }" << std::endl;

					//radious����������
					ofs << "\tradious: " << circleCollider->radious << std::endl;
				}
				////MonoBehaviour�Ȃ�
				//else if (type == typeid(MonoBehaviour)) {
				//	MonoBehaviour* mono = static_cast<MonoBehaviour*>(component);
				//	//MonoBehaviour��fileID���擾
				//	fileID = GetValue<SceneInfo*, int>(fileIDs, mono, CreateFileID());
				//	Type
				//	//�w�b�_�[��cpp��ID����������(fileID, guid)
				//	ofs << "mono: {fileID: " << fileID  << " ,guid: {header: " << mono->GetGUID() << " ,cpp: " << script->GetMonoBehaviour()->GetCPPGUID() << " }" << " }" << std::endl;
				//}
			}
		}
	}
}

void ProjectFileManager::LoadFromSceneFile(std::filesystem::path scenePath)
{
	//�V�[�����쐬
	Scene* scene = new Scene();
	//�V�[���̃p�X��ݒ�
	scene->scenePath = scenePath;
	SceneManager::SetNowScene(scene);	//�o�^
	scene->Init();	//������
	//�p�X�̃t�@�C��������V�[�������擾�A�Z�b�g
	scene->SetName(GetNameWithoutExtensionName(scenePath.filename()), true);

	//�s������ǂݍ���
	std::vector<std::string> lines = MyString::GetLines(scenePath);
	int row = 0;
	std::string guid;

	//�ǂݍ��߂����
	while (lines.size() - 1 > row) {
		//�N���X�����擾
		std::string className = lines[row++];
		SceneInfo* sceneInfo = nullptr;
		int fileID;

		//�t�@�C��ID���擾
		fileID = std::stoi(MyString::Split(lines[row++], ' ')[1]);

		//GameObject�Ȃ�
		if (className == typeid(GameObject).name()) {
			//�N���X����
			GameObject* gameobject = static_cast<GameObject*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, scene->CreateEmpty()));
			//���O�擾
			gameobject->SetName(MyString::Split(lines[row++], ' ')[1]);
			//�R���|�[�l���g�̐��擾
			int componentNum = std::stoi(MyString::Split(lines[row++], ' ')[1]);
			//��΂�
			row += componentNum;
		}
		//Transform�Ȃ�
		else if (className == typeid(Transform).name()) {
			//�Q�[���I�u�W�F�N�g�̃t�@�C��ID���擾
			fileID = std::stoi(MyString::Split(lines[row++], ' ')[2]);
			//�Q�[���I�u�W�F�N�g���擾
			GameObject* gameobject = static_cast<GameObject*>(sceneInfos[fileID]);
			//Transform���擾
			Transform* transform = gameobject->transform;

			//localPosition���Z�b�g
			std::vector<std::string> words = MyString::Split(lines[row++], ' ');
			Vector3 localPos = Vector3(std::stof(words[2]), std::stof(words[4]), std::stof(words[6]));
			transform->localPosition = localPos;

			//localRotation���Z�b�g
			words = MyString::Split(lines[row++], ' ');
			Vector3 localRote = Vector3(std::stof(words[2]), std::stof(words[4]), std::stof(words[6]));
			transform->localRotation = localRote;

			//localScale���Z�b�g
			words = MyString::Split(lines[row++], ' ');
			Vector3 localScale = Vector3(std::stof(words[2]), std::stof(words[4]), std::stof(words[6]));
			transform->localScale = localScale;

			//�q�̐��Z�b�g
			int childNum = std::stoi(MyString::Split(lines[row++], ' ')[1]);
			//��΂�
			row += childNum;

			//�e���Z�b�g
			fileID = std::stoi(MyString::Split(lines[row++], ' ')[2]);
			Transform* parent = nullptr;
			//�t�@�C��ID��0�łȂ��Ȃ�
			if (fileID != 0) {
				//�Z�b�g
				parent = static_cast<Transform*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, new Transform(nullptr)));
				//���[�J����ς����Ƀ��[���h��ς���
				transform->SetParent(parent, false);
			}
		}
		//Camera�Ȃ�
		else if (className == typeid(Camera).name()) {
			//�Q�[���I�u�W�F�N�g�̃t�@�C��ID���擾
			fileID = std::stoi(MyString::Split(lines[row++], ' ')[2]);
			//�Q�[���I�u�W�F�N�g���擾
			GameObject* gameobject = static_cast<GameObject*>(sceneInfos[fileID]);
			//Camera���쐬�A�擾
			Camera* camera = gameobject->AddComponent<Camera>();

			//�V�[���ɃJ������ǉ��A�ݒ�
			scene->SetNowCamera(camera);
		}
		//ImageRenderer�Ȃ�
		else if (className == typeid(ImageRenderer).name()) {
			//�Q�[���I�u�W�F�N�g�̃t�@�C��ID���擾
			fileID = std::stoi(MyString::Split(lines[row++], ' ')[2]);
			//�Q�[���I�u�W�F�N�g���擾
			GameObject* gameobject = static_cast<GameObject*>(sceneInfos[fileID]);
			//ImageRenderer���쐬�A�擾
			ImageRenderer* imageRenderer = gameobject->AddComponent<ImageRenderer>();

			//isFlipX���擾
			imageRenderer->isFlipX = (bool)(std::stoi(MyString::Split(lines[row++], ' ')[1]));

			//isFlipY���擾
			imageRenderer->isFlipY = (bool)(std::stoi(MyString::Split(lines[row++], ' ')[1]));

			//image�̃t�@�C��ID���擾
			fileID = std::stoi(MyString::Split(lines[row], ' ')[2]);
			//image��guid���擾
			guid = MyString::Split(lines[row++], ' ')[4];
			Image* image = nullptr;
			//fileID�Aguid�Ƃ���0�ł͂Ȃ��Ȃ�
			if (fileID != 0 && guid != "0") {
				//image���擾
				image = static_cast<Image*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, pathAndInfo[guidAndPath[guid]]));
			}
			//image���Z�b�g
			imageRenderer->image = image;
		}
		//Animator�Ȃ�
		else if (className == typeid(Animator).name()) {
			//�Q�[���I�u�W�F�N�g�̃t�@�C��ID���擾
			fileID = std::stoi(MyString::Split(lines[row++], ' ')[2]);
			//�Q�[���I�u�W�F�N�g���擾
			GameObject* gameobject = static_cast<GameObject*>(sceneInfos[fileID]);
			//Animator���쐬�A�擾
			Animator* animator = gameobject->AddComponent<Animator>();

			//ac�̃t�@�C��ID���擾
			fileID = std::stoi(MyString::Split(lines[row], ' ')[2]);
			//ac��guid���擾
			guid = MyString::Split(lines[row++], ' ')[4];
			//ac���擾�A���X�g�ɂ��o�^
			AnimatorController* ac = static_cast<AnimatorController*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, pathAndInfo[guidAndPath[guid]]));
			//ac���Z�b�g
			animator->ac = ac;

			//nowState�̃t�@�C��ID���擾
			fileID = std::stoi(MyString::Split(lines[row++], ' ')[2]);
			//nowState���Z�b�g
			animator->nowState = static_cast<AnimationState*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, new AnimationState()));
		}
		else if (className == typeid(BoxCollider).name()) {
			//�Q�[���I�u�W�F�N�g�̃t�@�C��ID���擾
			fileID = std::stoi(MyString::Split(lines[row++], ' ')[2]);
			//�Q�[���I�u�W�F�N�g���擾
			GameObject* gameobject = static_cast<GameObject*>(sceneInfos[fileID]);
			//BoxCollider���쐬�A�擾
			BoxCollider* boxCollider = gameobject->AddComponent<BoxCollider>();

			//offset���擾
			std::vector<std::string> words = MyString::Split(lines[row++], ' ');
			Vector3 offset = Vector3(std::stof(words[2]), std::stof(words[4]), std::stof(words[6]));
			//offset���Z�b�g
			boxCollider->offset = offset;

			//size���擾
			words = MyString::Split(lines[row++], ' ');
			Vector3 size = Vector3(std::stof(words[2]), std::stof(words[4]), std::stof(words[6]));
			//size���Z�b�g
			boxCollider->size = size;
		}
		else if (className == typeid(CircleCollider).name()) {
			//�Q�[���I�u�W�F�N�g�̃t�@�C��ID���擾
			fileID = std::stoi(MyString::Split(lines[row++], ' ')[2]);
			//�Q�[���I�u�W�F�N�g���擾
			GameObject* gameobject = static_cast<GameObject*>(sceneInfos[fileID]);
			//BoxCollider���쐬�A�擾
			CircleCollider* circleCollider = gameobject->AddComponent<CircleCollider>();

			//offset���擾
			std::vector<std::string> words = MyString::Split(lines[row++], ' ');
			Vector3 offset = Vector3(std::stof(words[2]), std::stof(words[4]), std::stof(words[6]));
			//offset���Z�b�g
			circleCollider->offset = offset;

			//radious���Z�b�g
			circleCollider->radious = std::stof(MyString::Split(lines[row++], ' ')[1]);
		}
		//else if (className == typeid(MonoBehaviour).name()) {
		//	//�Q�[���I�u�W�F�N�g�̃t�@�C��ID���擾
		//	fileID = std::stoi(MyString::Split(lines[row++], ' ')[2]);
		//	//�Q�[���I�u�W�F�N�g���擾
		//	GameObject* gameobject = static_cast<GameObject*>(sceneInfos[fileID]);
		//	//MonoBehaviour���쐬�A�擾
		//	MonoBehaviour* mono = gameobject->AddComponent<>();
		//}
	}
}

void ProjectFileManager::WriteToAnimatorControllerFile(AnimatorController* ac)
{
	//�A�j���[�V�����R���g���[���[�t�@�C�����J��
	std::ofstream ofs(ac->path);
	//�J������
	if (ofs) {
		//�t�@�C��ID
		int fileID;
		//guid
		std::string guid;

		//AnimatorController
		//�N���X����������
		ofs << typeid(*ac).name() << std::endl;

		//�t�@�C��ID���擾
		fileID = ac->fileID;
		//�t�@�C��ID����������
		ofs << "\tfileID: " << fileID << std::endl;

		//paramaters�̐�����������
		ofs << "\tparamaters: " << (int)ac->paramaters.size() << std::endl;
		for (AnimationParamater* paramater : ac->paramaters) {
			//paramater�̃t�@�C��ID���擾
			fileID = paramater->fileID;
			//paramater�̃t�@�C��ID����������
			ofs << "\t\tparamater: {fileID: " << fileID << " }" << std::endl;
		}

		//states�̐�����������
		ofs << "\tstates: " << (int)ac->states.size() << std::endl;
		for (AnimationState* state : ac->states) {
			//state�̃t�@�C��ID���擾
			fileID = state->fileID;
			//paramater�̃t�@�C��ID����������
			ofs << "\t\tstate: {fileID: " << fileID << " }" << std::endl;
		}

		//AnimationParamater
		for (AnimationParamater* paramater : ac->paramaters) {

			//�N���X����������
			ofs << typeid(*paramater).name() << std::endl;

			//�t�@�C��ID�𐶐�
			fileID = paramater->fileID;
			//�t�@�C��ID����������
			ofs << "\tfileID: " << fileID << std::endl;

			//���O����������
			ofs << "\tname: " << paramater->name << std::endl;

			//type����������
			ofs << "\ttype: " << (int)paramater->type << std::endl;

			//intValue����������
			ofs << "\tintValue: " << paramater->intValue << std::endl;

			//floatValue����������
			ofs << "\tfloatValue: " << paramater->floatValue << std::endl;

			//boolValue����������
			ofs << "\tboolValue: " << (int)paramater->boolValue << std::endl;
		}

		//AnimationState
		for (AnimationState* state : ac->states) {
			//�N���X����������
			ofs << typeid(*state).name() << std::endl;

			//�t�@�C��ID�𐶐�
			fileID = state->fileID;
			//�t�@�C��ID����������
			ofs << "\tfileID: " << fileID << std::endl;

			//animation�̃t�@�C��ID���擾
			fileID = state->animation->fileID;
			//animation��guid���擾
			guid = state->animation->guid;
			//animation����������(guid��)
			ofs << "\tanimation: {fileID: " << fileID << " ,guid: " << state->animation->guid << " }" << std::endl;

			//name����������
			ofs << "\tname: " << state->name << std::endl;

			//speed����������
			ofs << "\tspeed: " << state->speed << std::endl;

			//transitions�̃T�C�Y����������
			ofs << "\ttransitions: " << (int)state->transitions.size() << std::endl;
			for (AnimationTransition* transition : state->transitions) {
				//transition�̃t�@�C��ID���擾
				fileID = transition->fileID;
				//transition�̃t�@�C��ID����������
				ofs << "\t\ttransition: {fileID: " << fileID << " }" << std::endl;
			}

			for (AnimationTransition* transition : state->transitions) {
				//AnimationTransition
				//�N���X����������
				ofs << typeid(*transition).name() << std::endl;

				//�t�@�C��ID�𐶐�
				fileID = transition->fileID;
				//�t�@�C��ID����������
				ofs << "\tfileID: " << fileID << std::endl;

				//fromState�̃t�@�C��ID���擾
				fileID = transition->fromState->fileID;
				//fromState�̃t�@�C��ID����������
				ofs << "\tfromState: {fileID: " << fileID << " }" << std::endl;

				//toState�̃t�@�C��ID���擾
				fileID = transition->toState->fileID;
				//toState�̃t�@�C��ID����������
				ofs << "\ttoState: {fileID: " << fileID << " }" << std::endl;

				//conditions�̐�����������
				ofs << "\tconditions: " << (int)transition->conditions.size() << std::endl;
				for (AnimationCondition* condition : transition->conditions) {
					//condition�̃t�@�C��ID���擾
					fileID = condition->fileID;
					//condition�̃t�@�C��ID����������
					ofs << "\t\tcondition: {fileID: " << fileID << " }" << std::endl;
				}

				//AnimationCondition
				for (AnimationCondition* condition : transition->conditions) {
					//�N���X����������
					ofs << typeid(*condition).name() << std::endl;

					//�t�@�C��ID���擾
					fileID = condition->fileID;
					//�t�@�C��ID����������
					ofs << "\tfileID: " << fileID << std::endl;

					//name����������
					ofs << "\tname: " << condition->name << std::endl;

					//mode����������
					ofs << "\tmode: " << (int)condition->mode << std::endl;

					//value����������
					ofs << "\tvalue: " << condition->value << std::endl;
				}
			}
		}
	}
}

void ProjectFileManager::LoadFromAnimatorControllerFile(std::filesystem::path acPath)
{
	//�s������ǂݍ���
	std::vector<std::string> lines = MyString::GetLines(acPath);
	int row = 0;
	std::string guid;

	//�ǂݍ��߂����
	while (lines.size() - 1 > row) {
		int fileID;
		std::string guid;

		//�N���X�����擾
		std::string className = lines[row++];

		//�t�@�C��ID���擾
		fileID = std::stoi(MyString::Split(lines[row++], ' ')[1]);

		//AnimatorController�Ȃ�
		if (className == typeid(AnimatorController).name()) {
			//AnimatorController���擾
			AnimatorController* ac = static_cast<AnimatorController*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, pathAndInfo[acPath]));

			//animationparamaters�̐����擾
			int paramaterNum = std::stoi(MyString::Split(lines[row++], ' ')[1]);
			for (int i = 0; i < paramaterNum; i++) {
				//paramater�̃t�@�C��ID���擾
				fileID = std::stoi(MyString::Split(lines[row++], ' ')[2]);
				//paramater���擾
				AnimationParamater* paramater = static_cast<AnimationParamater*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, new AnimationParamater()));
				//paramater�����X�g�ɒǉ�
				ac->paramaters.push_back(paramater);
			}

			//states�̐����擾
			int stateNum = std::stoi(MyString::Split(lines[row++], ' ')[1]);
			for (int i = 0; i < stateNum; i++) {
				//state�̃t�@�C��ID���擾
				fileID = std::stoi(MyString::Split(lines[row++], ' ')[2]);
				//state���擾
				AnimationState* state = static_cast<AnimationState*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, new AnimationState()));
				//state�����X�g�ɒǉ�
				ac->states.push_back(state);
			}
		}
		//AnimationParamater�Ȃ�
		else if (className == typeid(AnimationParamater).name()) {
			//AnimationParamater����
			AnimationParamater* paramater = static_cast<AnimationParamater*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, new AnimationParamater()));

			//���O���Z�b�g
			paramater->name = MyString::Split(lines[row++], ' ')[1];

			//type���Z�b�g
			paramater->type = (AnimationParamater::Type)std::stoi(MyString::Split(lines[row++], ' ')[1]);

			//intValue���Z�b�g
			paramater->intValue = std::stoi(MyString::Split(lines[row++], ' ')[1]);

			//floatValue����������
			paramater->floatValue = std::stof(MyString::Split(lines[row++], ' ')[1]);

			//boolValue����������
			paramater->boolValue = (bool)std::stoi(MyString::Split(lines[row++], ' ')[1]);
		}
		//AnimationState�Ȃ�
		else if (className == typeid(AnimationState).name()) {
			//AnimationState����
			AnimationState* state = static_cast<AnimationState*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, new AnimationState()));

			//animation�̃t�@�C��ID���擾
			fileID = std::stoi(MyString::Split(lines[row], ' ')[2]);
			//animation��guid���擾
			guid = MyString::Split(lines[row++], ' ')[4];
			//animation�Z�b�g
			//std::filesystem::path path = guidAndPath[guid];
			//Info* info = pathAndInfo[path];
			state->animation = static_cast<Animation*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, pathAndInfo[guidAndPath[guid]]));

			//���O���Z�b�g
			state->name = MyString::Split(lines[row++], ' ')[1];

			//speed���Z�b�g
			state->speed = std::stof(MyString::Split(lines[row++], ' ')[1]);

			//transitions�̐����擾
			int transitionNum = std::stoi(MyString::Split(lines[row++], ' ')[1]);
			for (int i = 0; i < transitionNum; i++) {
				//transition�̃t�@�C��ID���擾
				fileID = std::stoi(MyString::Split(lines[row++], ' ')[2]);
				//transition���擾
				AnimationTransition* transition = static_cast<AnimationTransition*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, new AnimationTransition()));
				//transition���Z�b�g
				state->transitions.push_back(transition);
			}
		}
		//AnimationTransition
		else if (className == typeid(AnimationTransition).name()) {
			//AnimationTransition����
			AnimationTransition* transition = static_cast<AnimationTransition*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, new AnimationTransition()));

			//fromState�̃t�@�C��ID���擾
			fileID = std::stoi(MyString::Split(lines[row++], ' ')[2]);
			//fromState���Z�b�g
			transition->fromState = static_cast<AnimationState*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, new AnimationState()));

			//toState�̃t�@�C��ID���擾
			fileID = std::stoi(MyString::Split(lines[row++], ' ')[2]);
			//toState���Z�b�g
			transition->toState = static_cast<AnimationState*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, new AnimationState()));

			//conditions�̐����擾
			int conditionNum = std::stoi(MyString::Split(lines[row++], ' ')[1]);
			for (int i = 0; i < conditionNum; i++) {
				//condition�̃t�@�C��ID���擾
				fileID = std::stoi(MyString::Split(lines[row++], ' ')[2]);
				//condition���擾
				AnimationCondition* condition = static_cast<AnimationCondition*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, new AnimationCondition()));
				//condition���Z�b�g
				transition->conditions.push_back(condition);
			}
		}
		//AnimationCondition
		else if (className == typeid(AnimationCondition).name()) {
			//AnimationCondition����
			AnimationCondition* condition = static_cast<AnimationCondition*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, new AnimationCondition()));

			//name���Z�b�g
			condition->name = MyString::Split(lines[row++], ' ')[1];

			//mode���Z�b�g
			condition->mode = (AnimationCondition::Mode)std::stoi(MyString::Split(lines[row++], ' ')[1]);

			//value���Z�b�g
			condition->value = std::stof(MyString::Split(lines[row++], ' ')[1]);
		}
	}
}

void ProjectFileManager::WriteToAnimationFile(Animation* animation)
{
	int fileID;
	std::string guid;

	//�V�[���t�@�C�����J��
	std::ofstream ofs(animation->path);
	//�J������
	if (ofs) {
		//�N���X������������
		ofs <<  typeid(*animation).name() << std::endl;

		//�t�@�C��ID���擾
		fileID = animation->fileID;
		//�t�@�C��ID����������
		ofs << "\tfileID: " << fileID << std::endl;

		////name����������
		//ofs << "\tname: " << animation->name << std::endl;

		//animationKey�̃}�b�v�̐�����������
		ofs << "\tanimationKeys: " << (int)animation->animationKeys.size() << std::endl;
		for (std::pair<int, Image*> animationKey : animation->animationKeys) {
			//animationKey����������
			ofs << "\t\tanimationKey:" << std::endl;

			//�t���[��������������
			ofs << "\t\t\ttime: " << animationKey.first << std::endl;

			//Image�̃t�@�C��ID���擾
			fileID = animationKey.second->fileID;
			//Image��guid���擾
			std::string guid = animationKey.second->guid;
			//Image����������(guid)
			ofs << "\t\t\timage: {fileID: " << fileID << " ,guid: " << guid << " }" << std::endl;
		}

		//isLoop����������
		ofs << "\tisLoop: " << (int)animation->isLoop << std::endl;
	}
}

void ProjectFileManager::LoadFromAnimationFile(std::filesystem::path animationPath)
{
	//�t�@�C�����J��
	std::ifstream ifs(animationPath.c_str());
	int fileID;
	std::string guid;

	//�J������
	if (ifs) {
		//�s������ǂݍ���
		std::vector<std::string> lines = MyString::GetLines(animationPath);
		int row = 0;

		//�N���X�����擾
		std::string className = lines[row++];
		//�N���X�����A�j���[�V�����Ȃ�
		if (className == typeid(Animation).name()) {
			//�t�@�C��ID���擾
			fileID = std::stoi(MyString::Split(lines[row++], ' ')[1]);
			//�A�j���[�V�������擾
			Animation* animation = static_cast<Animation*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, pathAndInfo[animationPath]));

			////���O���Z�b�g
			//animation->name = MyString::Split(lines[row++], ' ')[1];

			////�p�X��ݒ�
			//animation->path = animationPath;

			//animationKey�̃}�b�v�̐����擾
			int animationKeyNum = std::stoi(MyString::Split(lines[row++], ' ')[1]);
			for (int i = 0; i < animationKeyNum; i++) {
				row++;	//1�s��΂�
				//�t���[�������擾
				int time = std::stoi(MyString::Split(lines[row++], ' ')[1]);
				//image�̃t�@�C��ID���擾
				fileID = std::stoi(MyString::Split(lines[row], ' ')[2]);
				//image��guid���擾
				std::string guid = MyString::Split(lines[row++], ' ')[4];
				//image���擾
				Image* image = static_cast<Image*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, pathAndInfo[guidAndPath[guid]]));
				//time��image(animationKey)���Z�b�g
				animation->animationKeys.insert(std::make_pair(time, image));
			}

			//isLoop���Z�b�g
			animation->isLoop = (bool)std::stoi(MyString::Split(lines[row++], ' ')[1]);

		}
	}
}

std::string ProjectFileManager::CreateGUID()
{
	GUID guid;

	std::string guidStr;

	// GUID�̐���
	if (S_OK == CoCreateGuid(&guid)) {
		// GUID�𕶎���֕ϊ�
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
	//�����_���ɐ���
	return distr(eng);
}

std::string ProjectFileManager::GetNameWithoutExtensionName(std::filesystem::path path)
{
	return path.string().substr(0, path.string().length() - path.extension().string().length());
}

void ProjectFileManager::CheckAddFile(std::filesystem::path path)
{
	//�A�Z�b�g�t�@�C����������I���
	if (path == assetFilePath)
		return;

	vector<filesystem::path> pathes;

	pathes.push_back(path);

	//�c���[���X�g�ɃA�Z�b�g�̃p�X��ǉ�
	while (pathes.size() != 0) {
		filesystem::path path = pathes[0];
		pathes.erase(pathes.begin());

		//�_�t�@�C�����Ȃ���΍쐬�A�ǂݍ���
		CreateAndLoadKumoFile(path);

		//�p�X���f�B���N�g����������
		if (filesystem::is_directory(path)) {
			//�q�����X�g�ɒǉ�
			for (filesystem::path childPath : filesystem::directory_iterator(path)) {
				pathes.push_back(childPath);
			}
		}
		else {
			//�t�@�C�����V�[���t�@�C���Ȃ�
			if (GetFileType(path) == FileType::Scene) {
				//�t�@�C�������擾
				std::string sceneName = GetNameWithoutExtensionName(path.filename());
				//�V�[���̃}�b�v�ɖ���������
				if (!SceneManager::scenePathes.contains(sceneName)) {
					//�V�[���}�l�[�W���[�̃��X�g�ɒǉ�
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

//�����_���������̏�����
std::random_device ProjectFileManager::rd;
std::default_random_engine ProjectFileManager::eng(ProjectFileManager::rd());
std::uniform_int_distribution<int> ProjectFileManager::distr(ProjectFileManager::MIN, ProjectFileManager::MAX);