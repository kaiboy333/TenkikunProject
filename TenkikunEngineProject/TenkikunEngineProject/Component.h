#pragma once
#include "GameObject.h"

class GameObject;
class Component
{
	public:
		GameObject* gameobject = nullptr;

		bool canPutSameComponent = false;	//同じComponentを入れられるか
};

