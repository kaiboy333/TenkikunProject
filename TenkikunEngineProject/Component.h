#pragma once

#include <typeinfo>
#include <iostream>

class GameObject;
class Component
{
	public:
		GameObject* gameobject = nullptr;	//����Component������GameObject

		bool canPutSameComponent = true;	//����Component�������邩

		virtual void Update() = 0;
};
