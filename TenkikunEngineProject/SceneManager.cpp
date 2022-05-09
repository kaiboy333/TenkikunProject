#include "SceneManager.h"

SceneManager::SceneManager()
{
	AddScene();	//�V�[�����쐬
}

void SceneManager::LoadScene(std::string targetSceneName)
{
	for (Scene* scene : scenes) {
		//�������O��������
		if (scene->sceneName == targetSceneName) {
			//��������݂̃V�[���ɐݒ�
			nowScene = scene;
			return;
		}
	}
	std::cout << "Scene��������܂���" << std::endl;
}

void SceneManager::LoadScene(Scene* targetScene)
{
	for (Scene* scene : scenes) {
		//������������
		if (scene == targetScene) {
			//��������݂̃V�[���ɐݒ�
			nowScene = scene;
			return;
		}
	}
	std::cout << "Scene��������܂���" << std::endl;
}

Scene* SceneManager::GetNowScene()
{
	return nowScene;
}

Scene* SceneManager::AddScene()
{
	Scene* scene = new Scene();
	scenes.emplace_back(scene);	//���X�g�ɒǉ�
	//�����A���݂̃V�[�����o�^����Ă��Ȃ�������
	if (nowScene == nullptr) {
		nowScene = scene;	//�o�^
	}
	scene->Init();
	return scene;
}

std::vector<Scene*> SceneManager::scenes;	//�V�[������
Scene* SceneManager::nowScene;	//���݂�Scene
