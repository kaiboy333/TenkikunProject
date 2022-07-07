#pragma once

#include <typeinfo>
#include <iostream>
#include "Info.h"

class GameObject;
class Component : public Info
{
	public:
		GameObject* gameobject = nullptr;	//����Component������GameObject

		bool canPutSameComponent = true;	//����Component�������邩

		virtual void Update() = 0;
};
