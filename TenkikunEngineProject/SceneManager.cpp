#include "SceneManager.h"
#include "ProjectFileManager.h"

SceneManager::SceneManager()
{
	AddScene();	//�V�[�����쐬
}

void SceneManager::LoadScene(std::filesystem::path scenePath)
{
	//�V�[���t�@�C�����J��

	//�V�[���t�@�C������ǂݍ��݁A�V�[�����쐬

	//���̃V�[���ɓo�^
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
	//���̃p�X�ɃV�[���t�@�C����ݒ�
	std::filesystem::path scenePath(ProjectFileManager::currentPath.string() + ".scene");

	std::ofstream ofs(scenePath.c_str());
	//�V�[���t�@�C�����쐬�A�J��
	if (ofs) {
		//�V�[�����쐬
		Scene* scene = new Scene();
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

}

Scene* SceneManager::nowScene = nullptr;	//���݂�Scene
SceneManager::PlayMode SceneManager::playMode = PlayMode::EDIT;	//�����͕ҏW���[�h
