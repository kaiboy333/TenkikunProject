#pragma once
#include "GameObject.h"

class GameObject;
class Component
{
	public:
		GameObject* gameobject = nullptr;

		bool canPutSameComponent = false;	//����Component�������邩
};

