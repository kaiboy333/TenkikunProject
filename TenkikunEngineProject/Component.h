#pragma once

#include <typeinfo>
#include <iostream>
#include "Info.h"

class GameObject;
class Component : public Info
{
	public:
		GameObject* gameobject = nullptr;	//このComponentを持つGameObject

		bool canPutSameComponent = true;	//同じComponentを入れられるか

		virtual void Update() = 0;
};
