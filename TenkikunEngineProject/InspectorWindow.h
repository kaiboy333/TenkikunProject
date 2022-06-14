#pragma once

#include "Window.h"
#include "GameObject.h"
#include <vector>
#include "ComponentRect.h"
#include "ComponentRectManager.h"

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

		vector<ComponentRect*> componentRects;

		void Init();
};

