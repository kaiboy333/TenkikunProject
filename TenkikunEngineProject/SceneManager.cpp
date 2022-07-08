#include "SceneManager.h"
#include "ProjectFileManager.h"
#include "MyString.h"

SceneManager::SceneManager()
{
	MakeScene();	//�V�[�����쐬
}

void SceneManager::LoadScene(std::filesystem::path scenePath)
{
	//�V�[���t�@�C����������
	if (ProjectFileManager::GetFileType(scenePath) == ProjectFileManager::FileType::Scene) {
		//�V�[���t�@�C�����J��
		std::ifstream ifs(scenePath);
		//�J������
		if (ifs) {
			//�V�[���t�@�C������ǂݍ��݁A�V�[�����쐬
			Scene* scene = MakeSceneFromFile(scenePath);
			//�V�[���̃p�X��ݒ�
			scene->scenePath = scenePath;
			nowScene = scene;	//�o�^
			scene->Init();	//������
		}
	}
}

Scene* SceneManager::GetNowScene()
{
	return nowScene;
}

//Scene* SceneManager::AddScene()
//{
//	Scene* scene = new Scene();
//	scenes.emplace_back(scene);	//���X�g�ɒǉ�
//	//�����A���݂̃V�[�����o�^����Ă��Ȃ�������
//	if (nowScene == nullptr) {
//		nowScene = scene;	//�o�^
//	}
//	scene->Init();
//	return scene;
//}

Scene* SceneManager::MakeScene()
{
	Scene* scene = nullptr;

	//���̃p�X�ɃV�[���t�@�C����ݒ�
	std::filesystem::path scenePath(ProjectFileManager::currentPath.string() + ".scene");

	std::ofstream ofs(scenePath.c_str());
	//�V�[���t�@�C�����쐬�A�J��
	if (ofs) {
		//�V�[�����쐬
		scene = new Scene();
		//�V�[���̃p�X��ݒ�
		scene->scenePath = scenePath;
		//�����A���݂̃V�[�����o�^����Ă��Ȃ�������
		if (nowScene == nullptr) {
			nowScene = scene;	//�o�^
		}
		scene->Init();	//������
		//�_�t�@�C�����쐬�A��������
		ProjectFileManager::WriteToKumoFile(std::filesystem::path(scenePath.string() + ".kumo"));
	}

	return scene;
}

Scene* SceneManager::MakeSceneFromFile(std::filesystem::path scenePath)
{
	//�s������ǂݍ���
	std::vector<std::string> lines = MyString::GetLines(scenePath);
}

Scene* SceneManager::nowScene = nullptr;	//���݂�Scene
SceneManager::PlayMode SceneManager::playMode = PlayMode::EDIT;	//�����͕ҏW���[�h
