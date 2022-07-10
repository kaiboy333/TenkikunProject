#pragma once

#include <iostream>
#include <vector>
#include "GameObject.h"
#include "Camera.h"
#include "ImageRenderer.h"
#include "WindowManager.h"
#include "Window.h"

class TreeList;
class Scene
{
	public:
		std::vector<GameObject*> gameobjects;	//GameObject����
		std::vector<Camera*> cameras;	//Camera����

		TreeList* treeList = nullptr;

		int generateNum = 0;

		std::filesystem::path scenePath;	//�V�[���t�@�C���p�X

		Scene();

		void Init();

		void Update();

		void Draw(Window* parentWindow);

		GameObject* CreateEmpty();	//��̃Q�[���I�u�W�F�N�g���쐬
		GameObject* CreateSquare();	//�l�p���摜�̃Q�[���I�u�W�F�N�g���쐬
		GameObject* CreateCamera();	//�J�����Q�[���I�u�W�F�N�g���쐬

		void Destroy(GameObject* gameobject);	//�w���GameObject���폜

		Camera* GetNowCamera();

		std::string GetName();
		void SetName(std::string name);

	private:
		std::string name = "";	//Scene�̖��O

		int drawCameraNo = 0;
};

