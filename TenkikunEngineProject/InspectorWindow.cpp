#include "InspectorWindow.h"
#include "TransformRect.h"
#include "RigidBody.h"
#include "RigidBodyRect.h"

InspectorWindow::InspectorWindow() : Window(1000, 0, 300, 800)
{
	Init();
}

void InspectorWindow::Update()
{
	Window::Update();

	//ComponentRect�̍X�V
	for (ComponentRect* componentRect : componentRects) {
		componentRect->Update();
	}
}

void InspectorWindow::Draw()
{
	//���̉�ʕ`��
	Window::Draw();

	if (gameobject) {
		nameRect->Draw();	//�Q�[���I�u�W�F�N�g�̖��O�`��
		for (ComponentRect* componentRect : componentRects) {
			componentRect->Draw();
		}
	}
}

void InspectorWindow::SetGameObject(GameObject* gameobject)
{
	//���Z�b�g
	PreparationLibrate();
	this->gameobject = gameobject;	//�Q�[���I�u�W�F�N�g�Z�b�g
	Init();	//���X�g�Z�b�g
}

GameObject* InspectorWindow::GetGameObject()
{
	return gameobject;
}

void InspectorWindow::PreparationLibrate()
{
	gameobject = nullptr;

	//nameRect�̉������
	if (nameRect) {
		nameRect->PreparationLibrate();
		//���
		delete(nameRect);
		nameRect = nullptr;
	}

	if ((int)componentRects.size() != 0) {
		for (auto& componentRect : componentRects) {
			//componentRect�̉������
			componentRect->PreparationLibrate();
			//���
			delete(componentRect);
		}
		componentRects.clear();
	}
}

void InspectorWindow::Init()
{
	if (gameobject) {
		nameRect = new TextRect(startX, startY, gameobject->GetName());

		float startRectY = startY;	//Rect�̈ʒuY

		startRectY += FontManager::systemFont->GetFontHeight();	//���O�`�悵���̍��������炷

		for (Component* component : gameobject->components) {
			const std::type_info& type = typeid(*component);

			ComponentRect* componentRect = nullptr;
			//Transform�Ȃ�
			if (type == typeid(Transform)) {
				componentRect = new TransformRect(startX, startRectY, component);
				componentRects.insert(componentRects.begin(), componentRect);	//�擪�ɒǉ�
			}
			//RigidBody�Ȃ�
			else if (type == typeid(RigidBody)) {
				componentRect = new RigidBodyRect(startX, startRectY, component);
				componentRects.insert(componentRects.begin(), componentRect);	//���ɒǉ�
			}

			if (componentRect) {
				startRectY += componentRect->height;	//ComponentRect�̍��������炷
			}
		}
	}
}
