#include "InspectorWindow.h"
#include "TransformRect.h"

InspectorWindow::InspectorWindow() : Window(1000, 0, 300, 800)
{
	
}

void InspectorWindow::Draw()
{
	//���̉�ʕ`��
	Window::Draw();
}

void InspectorWindow::SetGameObject(GameObject* gameobject)
{
	this->gameobject = gameobject;	//�Q�[���I�u�W�F�N�g�Z�b�g
	componentRects.clear();	//���X�g������
	Init();	//���X�g�Z�b�g
}

void InspectorWindow::Init()
{
	float startRectY = startY;	//ComponentRect�̈ʒuY
	for (Component* component : gameobject->components) {
		const std::type_info& type = typeid(*component);

		ComponentRect* componentRect = nullptr;
		if (type == typeid(Transform)) {
			componentRect = new TransformRect(startX, startRectY, component);
			componentRects.push_back(componentRect);
		}

		if (componentRect) {
			startRectY += componentRect->height;
		}
	}
}
