#pragma once

#include "Window.h"
#include "GameObject.h"
#include <vector>
#include "ComponentRect.h"
#include "ComponentRectManager.h"
#include "TextRect.h"

using namespace std;

class ComponentRect;
class InspectorWindow : public Window
{
	public:
		InspectorWindow();

		virtual void Update() override;

		virtual void Draw() override;

		void SetGameObject(GameObject* gameobject);
		GameObject* GetGameObject();

	private:
		GameObject* gameobject = nullptr;

		TextRect* nameRect = nullptr;	//ゲームオブジェクトの名前のTextRect

		vector<ComponentRect*> componentRects;

		void Init();
};

