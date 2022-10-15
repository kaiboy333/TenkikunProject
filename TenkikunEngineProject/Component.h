#pragma once

#include <typeinfo>
#include <iostream>
#include "SceneInfo.h"
#include "Vector3.h"
#include "Window.h"

class GameObject;
class Component : public SceneInfo
{
	public:
		GameObject* gameobject = nullptr;	//このComponentを持つGameObject

		bool canPutSameComponent = true;	//同じComponentを入れられるか

		Component(GameObject* gameobject);

		virtual void Update() = 0;

		virtual void PreparationLibrate();
};
