#pragma once

#include <iostream>
#include <vector>
#include "Scene.h"
#include <filesystem>
#include <fstream>
#include <unordered_map>

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

		static std::unordered_map<std::string, std::filesystem::path> scenePathes;	//�V�[�����Ƃ��̃p�X

		SceneManager();

		static void LoadScene(std::string sceneName);	//�V�[���̖��O����V�[�����쐬���A�ǂݍ���

		static Scene* GetNowScene();	//���݂̃V�[��(getter)

		//static Scene* AddScene();	//�V�[�����쐬�A�o�^

		static void MakeScene();	//�V�[�����쐬

	private:
		static Scene* nowScene;	//���݂�Scene
};

