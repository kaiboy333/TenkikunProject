#pragma once

#include "Window.h"
#include "GameObject.h"
#include <vector>
#include "ComponentRect.h"

using namespace std;

class InspectorWindow : public Window
{
	public:
		InspectorWindow();

		virtual void Draw() override;

		void SetGameObject(GameObject* gameobject);

	private:
		GameObject* gameobject = nullptr;
		vector<ComponentRect*> componentRects;

		void Init();
};

