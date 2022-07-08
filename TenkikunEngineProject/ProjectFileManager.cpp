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
	//�A�Z�b�g�̃p�X���쐬
	assetFilePath = std::filesystem::current_path().string() + "\\Asset";
	//�A�Z�b�g�̐e�̐�΃p�X�Ƀo�b�N�X���b�V���ǉ�
	assetParentPathName = assetFilePath.parent_path().string() + "\\";
	//�A�Z�b�g�t�H���_�����݂��Ȃ��Ȃ�
	if (!std::filesystem::exists(assetFilePath)) {
		//�t�H���_���쐬
		std::filesystem::create_directory(assetFilePath);
	}
	currentPath = assetFilePath;	//�����̓A�Z�b�g�p�X
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
		std::string guidStr = MyString::Split(lines[0], ':')[1];

		//�ǉ��œǂݍ����Info���쐬
		Info* info = nullptr;
		//�_�g���q�𔲂����p�X���擾
		std::filesystem::path originPath(kumoPath.string().substr(0, kumoPath.string().length() - kumoPath.extension().string().length()));
		//���t�@�C���̎�ނɂ���ėl�X�ȃN���X���쐬
		switch (GetFileType(originPath)) {
			case FileType::Image:
				info = new Image(originPath.string());
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
			ofs << "guid : " + CreateGUID() << std::endl;	//guid����������
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

		for (GameObject* gameobject : scene->gameobjects) {
			//�N���X����������
			ofs << typeid(gameobject).name() << std::endl;
			//�t�@�C��ID�𐶐�
			int fileID = CreateFileID();
			//�}�b�v�ɒǉ�
			fileIDs.insert(std::make_pair(gameobject, fileID));

			//�t�@�C��ID����������
			ofs << "fileID : " << fileID << std::endl;
			//���O����������
			ofs << gameobject->GetName() << std::endl;
			//�R���|�[�l���g����������
			ofs << "components :" << std::endl;
			for (Component* component : gameobject->components) {
				//�R���|�[�l���g�̃t�@�C��ID����������Ă��Ȃ��Ȃ�
				if (!fileIDs.contains(component)) {
					//ID���쐬
					fileID++;
					//�}�b�v�ɒǉ�
					fileIDs.insert(std::make_pair(component, fileID));
				}
				//����ID����������
				ofs << " component : {fileID : " << fileIDs[component] << "}" << std::endl;
			}

			for (Component* component : gameobject->components) {
				//�N���X����������
				ofs << typeid(component).name() << std::endl;
				//�t�@�C��ID����������
				ofs << "fileID : " << fileIDs[component] << std::endl;
				//�Q�[���I�u�W�F�N�g����������
				ofs << "gameobject : {fileID : " << fileIDs[gameobject] << "}" << std::endl;

				//�^�C�v�擾
				const std::type_info& type = typeid(*component);
				//Transform��������
				if (type == typeid(Transform)) {
					Transform* transform = static_cast<Transform*>(component);
					//localPosition����������
					Vector3 localPos = transform->localPosition;
					ofs << "localPosition : {x : " << localPos.x << ", y : " << localPos.y << ", z : " << localPos.z << "}";
					//localRotation����������
					Vector3 localRote = transform->localRotation;
					ofs << "localRotation : {x : " << localRote.x << ", y : " << localRote.y << ", z : " << localRote.z << "}";
					//localScale����������
					Vector3 localScale = transform->localScale;
					ofs << "localScale : {x : " << localScale.x << ", y : " << localScale.y << ", z : " << localScale.z << "}";
				}
				//Camera�Ȃ�
				else if (type == typeid(Camera)) {

				}
				//ImageRenderer�Ȃ�
				else if (type == typeid(ImageRenderer)) {
					ImageRenderer* imageRenderer = static_cast<ImageRenderer*>(component);
					//isFlipX����������
					ofs << "isFlipX : " << (int)imageRenderer->isFlipX << std::endl;
					//isFlipY����������
					ofs << "isFlipY : " << (int)imageRenderer->isFlipY << std::endl;
					//image����������(guid)
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

std::filesystem::path ProjectFileManager::currentPath;

std::string ProjectFileManager::assetParentPathName = "";

std::vector<std::filesystem::path> ProjectFileManager::dragFilePathes;

std::unordered_map<std::string, Info*> ProjectFileManager::idInfos;

//�����_���������̏�����
std::random_device ProjectFileManager::rd;
std::default_random_engine ProjectFileManager::eng = std::default_random_engine(rd);
std::uniform_int_distribution<int> ProjectFileManager::distr = std::uniform_int_distribution<int>(ProjectFileManager::MIN, ProjectFileManager::MAX);
