#pragma once

#include <iostream>
#include <vector>
#include "Scene.h"
#include <filesystem>
#include <fstream>
#include <map>

class Scene;
class SceneManager
{
	public:
		enum class PlayMode
		{
			EDIT,	//�G���W���̕ҏW��
			PLAY,	//Play���[�h
			STOP	//Play���[�h�ł̈ꎞ��~
		};

		static PlayMode playMode;

		static std::map<std::string, std::filesystem::path> scenePathes;	//�V�[�����Ƃ��̃p�X

		SceneManager();

		static void LoadScene(std::string sceneName);	//�V�[���̖��O����V�[�����쐬���A�ǂݍ���

		static Scene* GetNowScene();	//���݂̃V�[��(getter)

		static void SetNowScene(Scene* scene);	//���݂̃V�[�����Z�b�g

		static void MakeScene(std::filesystem::path parentPath);	//�V�[�����쐬

		static void SaveScene();	//���݂̃V�[�����Z�[�u

	private:
		static Scene* nowScene;	//���݂�Scene
};

