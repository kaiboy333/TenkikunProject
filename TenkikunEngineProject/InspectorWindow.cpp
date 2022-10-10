#include "InspectorWindow.h"
#include "TransformRect.h"

InspectorWindow::InspectorWindow() : Window(1000, 0, 300, 800)
{
	nameRect = new TextRect(startX, startY, "");
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
	this->gameobject = gameobject;	//ゲームオブジェクトセット
	for (ComponentRect* componentRect : componentRects) {
		//ComponentRectの解放準備
		componentRect->PreparationLibrate();
		//解放
		delete(componentRect);
		componentRect = nullptr;
	}
	componentRects.clear();	//リスト初期化
	Init();	//リストセット
	nameRect->SetText(gameobject->GetName());	//TextRectに名前セット
}

GameObject* InspectorWindow::GetGameObject()
{
	return gameobject;
}

void InspectorWindow::Init()
{
	if (gameobject) {
		float startRectY = startY;	//Rectの位置Y

		startRectY += FontManager::systemFont->GetFontHeight();	//名前描画したの高さ分ずらす

		for (Component* component : gameobject->components) {
			const std::type_info& type = typeid(*component);

			ComponentRect* componentRect = nullptr;
			if (type == typeid(Transform)) {
				componentRect = new TransformRect(startX, startRectY, component);
				componentRects.insert(componentRects.begin(), componentRect);	//先頭に追加
			}

			if (componentRect) {
				startRectY += componentRect->height;	//ComponentRectの高さ分ずらす
			}
		}
	}
}
