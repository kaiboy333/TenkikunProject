#pragma once

#include <iostream>
#include <vector>
#include "GameObject.h"
#include "Camera.h"
#include "ImageRenderer.h"
#include "WindowManager.h"
#include "Window.h"

class TreeList;
class Scene : public SceneInfo
{
	public:
		std::vector<GameObject*> gameobjects;	//GameObject����

		TreeList* treeList = nullptr;

		std::filesystem::path scenePath;

		//std::vector<function<void()>> addAndRemoveEvents;	//�ǉ��A�폜�̊֐��������

		void Init();

		void Update();

		void Draw();

		GameObject* CreateEmpty();	//��̃Q�[���I�u�W�F�N�g���쐬
		GameObject* CreateSquare();	//�l�p���摜�̃Q�[���I�u�W�F�N�g���쐬
		GameObject* CreateCircle();	//�~�̉摜�̃Q�[���I�u�W�F�N�g���쐬
		GameObject* CreateCamera();	//�J�����Q�[���I�u�W�F�N�g���쐬
		GameObject* CreateTenkikun();	//�V�C����̉摜�̃Q�[���I�u�W�F�N�g���쐬
		GameObject* CreateUnityChan();	//�A�j���[�V����������Unity�����̃Q�[���I�u�W�F�N�g�쐬

		void Destroy(GameObject* gameobject);	//�w���GameObject���폜

		void SetNowCamera(Camera* camera);	//�J�������Z�b�g
		Camera* GetNowCamera();	//�J�������擾

		void AddCamera(Camera* camera);	//�J������ǉ�

		std::vector<Camera*> GetCameras();

		std::string GetName();
		void SetName(std::string name, bool isForce);	//���O��ς���(�����ł��̖��O�ɂ���)

	private:
		std::string name = "";	//Scene�̖��O

		Camera* nowCamera = nullptr;

		std::vector<Camera*> cameras;	//Camera����
};

