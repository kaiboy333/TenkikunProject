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

		//TreeList* treeList = nullptr;

		std::filesystem::path scenePath;

		std::vector<function<void()>> addAndRemoveEvents;	//�ǉ��A�폜�̊֐��������

		Scene();

		void Update();

		void Draw();

		GameObject* CreateEmpty(bool isLaterAdd = true);	//��̃Q�[���I�u�W�F�N�g���쐬(��Œǉ����邩)
		GameObject* CreateSquare(bool isLaterAdd = true);	//�l�p���摜�̃Q�[���I�u�W�F�N�g���쐬
		GameObject* CreateCircle(bool isLaterAdd = true);	//�~�̉摜�̃Q�[���I�u�W�F�N�g���쐬
		GameObject* CreateCamera(bool isLaterAdd = true);	//�J�����Q�[���I�u�W�F�N�g���쐬
		GameObject* CreateTenkikun(bool isLaterAdd = true);	//�V�C����̉摜�̃Q�[���I�u�W�F�N�g���쐬
		GameObject* CreateUnityChan(bool isLaterAdd = true);	//�A�j���[�V����������Unity�����̃Q�[���I�u�W�F�N�g�쐬

		void Destroy(GameObject* gameobject);	//�w���GameObject���폜

		void SetNowCamera(Camera* camera);	//�J�������Z�b�g
		Camera* GetNowCamera();	//�J�������擾

		void AddCamera(Camera* camera);	//�J������ǉ�

		std::vector<Camera*> GetCameras();

		std::string GetName();
		void SetName(std::string name, bool isForce = false);	//���O��ς���(�����ł��̖��O�ɂ���)

		virtual void PreparationLibrate() override;

		GameObject* Find(std::string name);

	private:
		std::string name = "Scene";	//Scene�̖��O

		Camera* nowCamera = nullptr;

		std::vector<Camera*> cameras;	//Camera����
};

