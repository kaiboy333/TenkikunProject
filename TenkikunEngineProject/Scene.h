#pragma once

#include <iostream>
#include <vector>
#include "GameObject.h"
#include "Camera.h"
#include "ImageRenderer.h"

class Scene
{
	public:
		enum SceneState
		{
			EDIT,	//�G���W���̕ҏW��
			PLAY,	//Play���[�h
			STOP	//Play���[�h�ł̈ꎞ��~
		};

		std::string sceneName = "Scene1";	//Scene�̖��O
		std::vector<GameObject*> gameobjects;	//GameObject����
		std::vector<Camera*> cameras;	//Camera����

		void Init();

		void Update();

		void Draw(Window* window);

		GameObject* CreateEmpty();	//��̃Q�[���I�u�W�F�N�g���쐬
		GameObject* CreateSquare();	//�l�p���摜�̃Q�[���I�u�W�F�N�g���쐬
		GameObject* CreateCamera();	//�J�����Q�[���I�u�W�F�N�g���쐬

		//void DestroyGameObject(GameObject* gameobject);	//�w���GameObject���폜

		void RemoveGameObject(GameObject* gameobject);	//�w���GameObject�����X�g����폜

		Camera* GetNowCamera();

	private:
		int drawCameraNo = 0;
};

