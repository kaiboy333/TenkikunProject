#pragma once

#include <typeinfo>
#include <iostream>
#include "SceneInfo.h"

class GameObject;
class Component : public SceneInfo
{
	public:
		GameObject* gameobject = nullptr;	//このComponentを持つGameObject

		bool canPutSameComponent = true;	//同じComponentを入れられるか

		virtual void Update() = 0;
};
