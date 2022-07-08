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
		std::string sceneName = "Scene1";	//Scene�̖��O
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

		//void RemoveGameObject(GameObject* gameobject);	//�w���GameObject�����X�g����폜

		Camera* GetNowCamera();

		void WriteToSceneFile();	//���݂̃V�[���̏����V�[���t�@�C���ɏ�������

	private:
		int drawCameraNo = 0;
};

