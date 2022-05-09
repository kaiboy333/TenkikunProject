#pragma once

#include <iostream>
#include <vector>
#include "Scene.h"

class Scene;
class SceneManager
{
	public:
		SceneManager();

		static void LoadScene(std::string targetSceneName);	//�V�[���̖��O���炻�̃V�[���Ɉړ�����
		static void LoadScene(Scene* targetScene);	//�V�[�����炻�̃V�[���Ɉړ�����

		static Scene* GetNowScene();	//���݂̃V�[��(getter)

		static Scene* AddScene();	//�V�[�����쐬�A�o�^

	private:
		static Scene* nowScene;	//���݂�Scene
		static std::vector<Scene*> scenes;	//�V�[������
};

