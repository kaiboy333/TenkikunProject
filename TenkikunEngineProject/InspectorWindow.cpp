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

	//ComponentRectの更新
	for (ComponentRect* componentRect : componentRects) {
		componentRect->Update();
	}
}

void InspectorWindow::Draw()
{
	//裏の画面描画
	Window::Draw();

	if (gameobject) {
		nameRect->Draw();	//ゲームオブジェクトの名前描画
		for (ComponentRect* componentRect : componentRects) {
			componentRect->Draw();
		}
	}
}

void InspectorWindow::SetGameObject(GameObject* gameobject)
{
	//リセット
	PreparationLibrate();
	this->gameobject = gameobject;	//ゲームオブジェクトセット
	Init();	//リストセット
}

GameObject* InspectorWindow::GetGameObject()
{
	return gameobject;
}

void InspectorWindow::PreparationLibrate()
{
	gameobject = nullptr;

	//nameRectの解放準備
	if (nameRect) {
		nameRect->PreparationLibrate();
		//解放
		delete(nameRect);
		nameRect = nullptr;
	}

	if ((int)componentRects.size() != 0) {
		for (auto& componentRect : componentRects) {
			//componentRectの解放準備
			componentRect->PreparationLibrate();
			//解放
			delete(componentRect);
		}
		componentRects.clear();
	}
}

void InspectorWindow::Init()
{
	if (gameobject) {
		nameRect = new TextRect(startX, startY, gameobject->GetName());

		float startRectY = startY;	//Rectの位置Y

		startRectY += FontManager::systemFont->GetFontHeight();	//名前描画したの高さ分ずらす

		for (Component* component : gameobject->components) {
			const std::type_info& type = typeid(*component);

			ComponentRect* componentRect = nullptr;
			//Transformなら
			if (type == typeid(Transform)) {
				componentRect = new TransformRect(startX, startRectY, component);
				componentRects.insert(componentRects.begin(), componentRect);	//先頭に追加
			}
			//RigidBodyなら
			else if (type == typeid(RigidBody)) {
				componentRect = new RigidBodyRect(startX, startRectY, component);
				componentRects.insert(componentRects.begin(), componentRect);	//後ろに追加
			}

			if (componentRect) {
				startRectY += componentRect->height;	//ComponentRectの高さ分ずらす
			}
		}
	}
}
