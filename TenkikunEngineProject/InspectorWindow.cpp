#include "InspectorWindow.h"
#include "TransformRect.h"

InspectorWindow::InspectorWindow() : Window(1000, 0, 300, 800)
{
	
}

void InspectorWindow::Draw()
{
	//裏の画面描画
	Window::Draw();
}

void InspectorWindow::SetGameObject(GameObject* gameobject)
{
	this->gameobject = gameobject;	//ゲームオブジェクトセット
	componentRects.clear();	//リスト初期化
	Init();	//リストセット
}

void InspectorWindow::Init()
{
	float startRectY = startY;	//ComponentRectの位置Y
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
