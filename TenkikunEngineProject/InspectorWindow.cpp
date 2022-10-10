#include "InspectorWindow.h"
#include "TransformRect.h"

InspectorWindow::InspectorWindow() : Window(1000, 0, 300, 800)
{
	nameRect = new TextRect(startX, startY, "");
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
	this->gameobject = gameobject;	//�Q�[���I�u�W�F�N�g�Z�b�g
	for (ComponentRect* componentRect : componentRects) {
		//ComponentRect�̉������
		componentRect->PreparationLibrate();
		//���
		delete(componentRect);
		componentRect = nullptr;
	}
	componentRects.clear();	//���X�g������
	Init();	//���X�g�Z�b�g
	nameRect->SetText(gameobject->GetName());	//TextRect�ɖ��O�Z�b�g
}

GameObject* InspectorWindow::GetGameObject()
{
	return gameobject;
}

void InspectorWindow::Init()
{
	if (gameobject) {
		float startRectY = startY;	//Rect�̈ʒuY

		startRectY += FontManager::systemFont->GetFontHeight();	//���O�`�悵���̍��������炷

		for (Component* component : gameobject->components) {
			const std::type_info& type = typeid(*component);

			ComponentRect* componentRect = nullptr;
			if (type == typeid(Transform)) {
				componentRect = new TransformRect(startX, startRectY, component);
				componentRects.insert(componentRects.begin(), componentRect);	//�擪�ɒǉ�
			}

			if (componentRect) {
				startRectY += componentRect->height;	//ComponentRect�̍��������炷
			}
		}
	}
}
