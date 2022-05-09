#pragma once

#include <typeinfo>
#include <iostream>

class GameObject;
class Component
{
	public:
		GameObject* gameobject = nullptr;	//このComponentを持つGameObject

		bool canPutSameComponent = true;	//同じComponentを入れられるか

		virtual void Update() = 0;
};
