#pragma once

#include <iostream>
#include <vector>
#include "Scene.h"
#include <filesystem>
#include <fstream>

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

		SceneManager();

		static void LoadScene(std::filesystem::path scenePath);	//�V�[���t�@�C������V�[�����쐬���A�ǂݍ���

		static Scene* GetNowScene();	//���݂̃V�[��(getter)

		//static Scene* AddScene();	//�V�[�����쐬�A�o�^

		static Scene* MakeScene();	//�V�[�����쐬

		static Scene* MakeSceneFromFile(std::filesystem::path scenePath);	//�V�[���t�@�C������V�[�����쐬

	private:
		static Scene* nowScene;	//���݂�Scene
};

