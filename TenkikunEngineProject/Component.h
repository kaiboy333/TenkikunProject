#pragma once

#include <typeinfo>
#include <iostream>
#include "SceneInfo.h"
#include "Vector3.h"
#include "Window.h"

class GameObject;
class Transform;
class Component : public SceneInfo
{
	public:
		GameObject* gameobject = nullptr;	//����Component������GameObject

		Transform* transform = nullptr;	//Transform

		bool canPutSameComponent = true;	//����Component�������邩

		Component(GameObject* gameobject);

		virtual void Update() = 0;

		virtual void PreparationLibrate();
};
