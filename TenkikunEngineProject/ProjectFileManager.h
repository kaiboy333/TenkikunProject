#pragma once

#include <filesystem>
#include <unordered_map>
#include "Info.h"
#include <random>
#include "Scene.h"
#include "AnimatorController.h"

class ProjectFileManager
{
	public:
		//�t�@�C���̎��
		enum class FileType {
			Image,
			Folder,
			Script_cpp,
			Script_hpp,
			Script_h,
			Kumo,
			Scene,
			Animation,
			AnimatorController,
			None,
		};

		//�����_���֘A(fileID)
		static const int MIN = 1;
		static const int MAX = 100000000;

		static std::random_device rd;
		static std::default_random_engine eng;
		static std::uniform_int_distribution<int> distr;

		static std::filesystem::path currentPath;	//���݂̃p�X

		static std::filesystem::path assetFilePath;	//�A�Z�b�g�t�H���_������p�X
		static std::filesystem::path resourceFilePath;	//���\�[�X�t�H���_������p�X
		static std::filesystem::path imageFilePath;	//�G���W���Ŏg���摜�������Ă���t�H���_�̃p�X

		//�A�Z�b�g�̐�΃p�X�̃t�@�C������������������
		static std::string assetParentPathName;

		//�h���b�O���ꂽ�t�@�C���̃p�X����
		static std::vector<std::filesystem::path> dragFilePathes;

		//static std::unordered_map<Info*, int> infoAndFileID;

		static std::unordered_map<std::string, Info*> guidAndInfo;

		//sceneInfos
		static std::unordered_map<int, SceneInfo*> sceneInfos;

		static std::unordered_map<std::string, std::filesystem::path> guidAndPath;

		ProjectFileManager();

		static void Update();

		static FileType GetFileType(std::filesystem::path path);	//�w��̃t�@�C���͂��̃^�C�v�ł��邩

		static void CreateAndLoadKumoFile(std::filesystem::path kumoPath);	//�t�@�C����p�̂���(���^)�t�@�C�����`�F�b�N

		static Info* CreateInfo(std::filesystem::path path);	//�t�@�C������Info���쐬

		static void WriteToKumoFile(std::filesystem::path kumoPath, Info* info);	//�_�t�@�C���ɋL�q����

		static void WriteToFile();	//�ۑ�����t�@�C���ɏ����L�q����
		static void LoadFromFile();	//���ׂĂ̕ۑ��t�@�C���������ǂݍ���

		static void WriteToSceneFile(Scene* scene);	//���݂̃V�[���̏����V�[���t�@�C���ɏ�������
		static void LoadFromSceneFile(std::filesystem::path scenePath);	//�V�[���t�@�C������V�[�����쐬

		//template<class T>
		//static std::vector<T*> GetSpecificGUIDInfos();	//guidInfos�ɂ������(T)�̃N���X���擾����

		static int CreateFileID();	//fileID�𐶐�����(int��)
		static std::string CreateGUID();	//GUID�𐶐�����(string��)

		static std::string GetNameWithoutExtensionName(std::filesystem::path path);	//�g���q�𔲂����t�@�C�����擾

	private:
		static void WriteToAnimationFile(Animation* animation);	//�A�j���[�V�����t�@�C���ɋL�q����
		static void LoadFromAnimationFile(std::filesystem::path animationPath);	//�A�j���[�V�����t�@�C������A�j���[�V�������쐬

		static void WriteToAnimatorControllerFile(AnimatorController* ac);	//���݂�ac�̏���ac�t�@�C���ɏ�������
		static void LoadFromAnimatorControllerFile(std::filesystem::path acPath);	//ac�t�@�C������ac���쐬

		template<class T, class K>
		static K GetValue(std::unordered_map<T, K>& map, T key, K value);	//�}�b�v��value���擾�A�Ȃ�������V����value��ǉ��A�擾

		static std::string GetGUIDFromKumoPath(std::filesystem::path kumoPath);	//kumoPath����guid���擾
};

template<class T, class K>
inline K ProjectFileManager::GetValue(std::unordered_map<T, K>& map, T key, K value)
{
	//�L�[��������Ȃ������Ȃ�
	if (!map.contains(key)) {
		//�V�������
		map.insert(std::make_pair(key, value));
		//���̒l��Ԃ�
		return value;
	}
	else {
		//���ɂ���l��Ԃ�
		return map[key];
	}
}

//template<class T>
//inline std::vector<T*> ProjectFileManager::GetSpecificGUIDInfos()
//{
//	std::vector<T*> infos;
//
//	//��
//	for (std::pair pair : idInfos) {
//		//����Info�N���X��T�N���X�ł���Ȃ�
//		//�L���X�g�ϊ��\�Ȃ�
//		if (static_cast<T*>(pair.second) != nullptr) {
//			//�L���X�g����Info���擾
//			T* info = static_cast<T*>(pair.second);
//			//���X�g�ɒǉ�
//			infos.push_back(info);
//		}
//	}
//
//	return infos;
//}
