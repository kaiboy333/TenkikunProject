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

	//���\�[�X�t�H���_���ɓ��ꂽ���摜���R�s�[&�y�[�X�g
	//�l�p�̉摜�p�X���R�s�[&�y�[�X�g
	std::filesystem::path copyPath = std::filesystem::path(imageFilePath.string() + "\\Square.png");
	std::filesystem::path pastePath = std::filesystem::path(resourceFilePath.string() + "\\" + copyPath.filename().string());
	if (!std::filesystem::exists(pastePath)) {
		filesystem::copy(copyPath, pastePath);
	}
	//�V�C����̉摜�p�X���R�s�[&�y�[�X�g
	copyPath = std::filesystem::path(imageFilePath.string() + "\\Tenkikun.png");
	pastePath = std::filesystem::path(resourceFilePath.string() + "\\" + copyPath.filename().string());
	if (!std::filesystem::exists(pastePath)) {
		filesystem::copy(copyPath, pastePath);
	}
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
	}

	//�^�C�v��Ԃ�
	return targetFileType;
}

void ProjectFileManager::CreateAndLoadKumoFile(std::filesystem::path path)
{
	//�t�@�C���^�C�v�������i�V���_�t�@�C���Ȃ�
	if (GetFileType(path) == FileType::None || GetFileType(path) == FileType::Kumo)
		//�I���
		return;

	//�_�t�@�C���p�X���쐬
	std::filesystem::path kumoPath = std::filesystem::path(path.string() + ".kumo");

	//�t�@�C�������݂��Ȃ��Ȃ�
	if (!std::filesystem::exists(kumoPath)) {
		//�t�@�C���ɋL�q����
		WriteToKumoFile(kumoPath);
	}

	//�_�t�@�C������Info�N���X���쐬
	WriteToInfo(kumoPath);
}

void ProjectFileManager::WriteToInfo(std::filesystem::path kumoPath)
{
	//�t�@�C�����J��
	std::ifstream ifs(kumoPath.c_str());
	//�J������
	if (ifs) {
		std::string strBuf;

		//�s������ǂݍ���
		std::vector<std::string> lines = MyString::GetLines(kumoPath);

		//GUID���擾
		std::string guidStr = MyString::Split(lines[0], ' ')[1];

		//�ǉ��œǂݍ����Info���쐬
		Info* info = nullptr;
		//�_�g���q�𔲂����p�X���擾
		std::filesystem::path originPath(kumoPath.string().substr(0, kumoPath.string().length() - kumoPath.extension().string().length()));
		//���t�@�C���̎�ނɂ���ėl�X�ȃN���X���쐬
		switch (GetFileType(originPath)) {
			case FileType::Image:
				info = new Image(originPath);	//Image�𐶐�
				break;
		}

		//�쐬�ł����Ȃ�
		if (info) {
			//Info��guid���Z�b�g
			info->SetGUID(guidStr);
			//�}�b�v�ɓo�^
			idInfos.insert(std::make_pair(guidStr, info));
		}
	}
}

void ProjectFileManager::WriteToKumoFile(std::filesystem::path kumoPath)
{
	//�_�t�@�C���Ȃ�
	if (GetFileType(kumoPath) == FileType::Kumo) {
		//�t�@�C�����쐬�A�J��
		std::ofstream ofs(kumoPath.c_str());
		//�J������
		if (ofs) {
			std::string guid = CreateGUID();
			ofs << "guid: " << guid << std::endl;	//guid����������
			switch (GetFileType(kumoPath)) {
			case FileType::Image:
				break;
			}
		}
		else {
			Debug::Log(kumoPath.string() + "�͊J���܂���ł����B\n");
		}
	}
}

void ProjectFileManager::WriteToSceneFile(Scene* scene)
{
	//�V�[���t�@�C�����J��
	std::ofstream ofs(scene->scenePath);
	//�J������
	if (ofs) {
		//�N���X�ƃt�@�C��ID�̃}�b�v���쐬
		std::unordered_map<SceneInfo*, int> fileIDs;

		//�V�[��������������
		ofs << "sceneName: " << scene->GetName() << std::endl;

		for (GameObject* gameobject : scene->gameobjects) {
			//�N���X����������
			ofs << typeid(*gameobject).name() << std::endl;

			//�t�@�C��ID�𐶐�
			int fileID = GetValue<SceneInfo*, int>(fileIDs, gameobject, CreateFileID());

			//�t�@�C��ID����������
			ofs << "\tfileID: " << fileID << std::endl;

			//���O����������
			ofs << "\tname: " << gameobject->GetName() << std::endl;

			//�R���|�[�l���g�̐�����������
			ofs << "\tcomponents: " << gameobject->components.size() << std::endl;
			for (Component* component : gameobject->components) {
				//�t�@�C��ID���擾
				fileID = GetValue<SceneInfo*, int>(fileIDs, component, CreateFileID());
				//ID����������
				ofs << "\t\tcomponent: {fileID: " << fileID << " }" << std::endl;
			}

			for (Component* component : gameobject->components) {
				//�N���X����������
				ofs << typeid(*component).name() << std::endl;

				//�t�@�C��ID���擾
				fileID = GetValue<SceneInfo*, int>(fileIDs, component, CreateFileID());

				//�t�@�C��ID����������
				ofs << "\tfileID: " << fileID << std::endl;

				//�Q�[���I�u�W�F�N�g����������
				ofs << "\tgameobject: {fileID: " << fileIDs[gameobject] << " }" << std::endl;

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
						fileID = GetValue<SceneInfo*, int>(fileIDs, child, CreateFileID());
						//ID����������
						ofs << "\t\tchild: fileID:{ " << fileID << " }" << std::endl;
					}

					//�e��Transform��ID�擾
					if (transform->parent) {
						fileID = GetValue<SceneInfo*, int>(fileIDs, transform->parent, CreateFileID());
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
					//image����������(guid)
					ofs << "\timage: {guid: " << imageRenderer->image->GetGUID() << " }" << std::endl;
				}
				////Script�Ȃ�
				//else if (type == typeid(Script)) {

				//}
			}
		}
	}
}

void ProjectFileManager::LoadSceneFromFile(std::filesystem::path scenePath, Scene* scene)
{
	//�s������ǂݍ���
	std::vector<std::string> lines = MyString::GetLines(scenePath);
	int row = 0;
	//�t�@�C��ID�ƃN���X�}�b�v���쐬
	std::unordered_map<int, SceneInfo*> sceneInfos;

	//�V�[�����擾
	scene->SetName(MyString::Split(lines[row++], ' ')[1], true);

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
			GameObject* gameobject = static_cast<GameObject*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, new GameObject()));
			//���O�擾
			gameobject->SetName(MyString::Split(lines[row++], ' ')[1]);
			//�R���|�[�l���g�̐��擾
			int componentNum = std::stoi(MyString::Split(lines[row++], ' ')[1]);
			for (int i = 0; i < componentNum; i++, row++) {
				////�R���|�[�l���g���擾(SceneInfo���𖳗����Component�ɂ��Ă���)
				//fileID = std::stoi(MyString::Split(lines[row], ' ')[2]);
				//Component* component = static_cast<Component*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, new Component()));
				////�Q�[���I�u�W�F�N�g��components�ɒǉ�
				//gameobject->components.push_back(component);
			}
			scene->treeList->Add(new TreeNode(gameobject->GetName(), scene->treeList, scene->treeList->isFirstOpen), scene->treeList->GetRoot());	//TreeNode�ɂ��ǉ�
			//�V�[���ɃQ�[���I�u�W�F�N�g��ǉ�
			scene->gameobjects.push_back(gameobject);
		}
		//Transform�Ȃ�
		else if (className == typeid(Transform).name()) {
			//Transform���쐬
			Transform* transform = new Transform();

			//�Q�[���I�u�W�F�N�g�̃t�@�C��ID���擾
			fileID = std::stoi(MyString::Split(lines[row++], ' ')[2]);
			//�Q�[���I�u�W�F�N�g���Z�b�g
			transform->gameobject = static_cast<GameObject*>(sceneInfos[fileID]);
			//�Q�[���I�u�W�F�N�g�Ɏ��g��ݒ�
			transform->gameobject->transform = transform;
			//���̃Q�[���I�u�W�F�N�g�Ɏ��g��ǉ�
			transform->gameobject->components.push_back(transform);

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
			for (int i = 0; i < childNum; i++, row++) {
				////�q���擾
				//fileID = std::stoi(MyString::Split(lines[row], ' ')[2]);
				//Transform* child = static_cast<Transform*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, new Transform()));
				//Transform->children�ɂ͂܂��ǉ����Ȃ�(SetParent�Œǉ����邽��)
			}

			//�e���Z�b�g
			fileID = std::stoi(MyString::Split(lines[row++], ' ')[2]);
			Transform* parent = nullptr;
			//�t�@�C��ID��0�łȂ��Ȃ�
			if (fileID != 0) {
				//�Z�b�g
				parent = static_cast<Transform*>(GetValue<int, SceneInfo*>(sceneInfos, fileID, new Transform()));
				//���[�J����ς����Ƀ��[���h��ς���
				transform->SetParent(parent, false);
			}

			////�R���|�[�l���g�̒��g��Transform�ɕς���
			//*(&component) = transform;
		}
		//Camera�Ȃ�
		else if (className == typeid(Camera).name()) {
			////�R���|�[�l���g���擾
			//Component* component = static_cast<Component*>(sceneInfos[fileID]);
			//Camera���쐬
			Camera* camera = new Camera();

			//�Q�[���I�u�W�F�N�g�̃t�@�C��ID���擾
			fileID = std::stoi(MyString::Split(lines[row++], ' ')[2]);
			//�Q�[���I�u�W�F�N�g���Z�b�g
			camera->gameobject = static_cast<GameObject*>(sceneInfos[fileID]);
			//���̃Q�[���I�u�W�F�N�g�Ɏ��g��ǉ�
			camera->gameobject->components.push_back(camera);
			//�V�[���ɃJ������ǉ��A�ݒ�
			scene->SetNowCamera(camera);

			////�R���|�[�l���g�̒��g��Camera�ɕς���
			//*(&component) = camera;
			//Debug::Log("");
		}
		//ImageRenderer�Ȃ�
		else if (className == typeid(ImageRenderer).name()) {
			////�R���|�[�l���g���擾
			//Component* component = static_cast<Component*>(sceneInfos[fileID]);
			//ImageRenderer���쐬
			ImageRenderer* imageRenderer = new ImageRenderer();

			//�Q�[���I�u�W�F�N�g�̃t�@�C��ID���擾
			fileID = std::stoi(MyString::Split(lines[row++], ' ')[2]);
			//�Q�[���I�u�W�F�N�g���Z�b�g
			imageRenderer->gameobject = static_cast<GameObject*>(sceneInfos[fileID]);
			//���̃Q�[���I�u�W�F�N�g�Ɏ��g��ǉ�
			imageRenderer->gameobject->components.push_back(imageRenderer);

			//isFlipX���擾
			imageRenderer->isFlipX = (bool)(std::stoi(MyString::Split(lines[row++], ' ')[1]));

			//isFlipY���擾
			imageRenderer->isFlipY = (bool)(std::stoi(MyString::Split(lines[row++], ' ')[1]));

			//image���擾
			imageRenderer->image = static_cast<Image*>(idInfos[MyString::Split(lines[row++], ' ')[2]]);

			////�R���|�[�l���g�̒��g��ImageRenderer�ɕς���
			//*(&component) = imageRenderer;
			//Debug::Log("");
		}
		//else if (className == typeid(Script).name()) {

		//}
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

std::filesystem::path ProjectFileManager::assetFilePath;
std::filesystem::path ProjectFileManager::resourceFilePath;
std::filesystem::path ProjectFileManager::imageFilePath;

std::filesystem::path ProjectFileManager::currentPath;

std::string ProjectFileManager::assetParentPathName = "";

std::vector<std::filesystem::path> ProjectFileManager::dragFilePathes;

std::unordered_map<std::string, Info*> ProjectFileManager::idInfos;

//�����_���������̏�����
std::random_device ProjectFileManager::rd;
std::default_random_engine ProjectFileManager::eng(ProjectFileManager::rd());
std::uniform_int_distribution<int> ProjectFileManager::distr(ProjectFileManager::MIN, ProjectFileManager::MAX);
