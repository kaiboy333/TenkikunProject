#pragma once

#include <typeinfo>
#include <iostream>
#include "SceneInfo.h"

class GameObject;
class Component : public SceneInfo
{
	public:
		GameObject* gameobject = nullptr;	//����Component������GameObject

		bool canPutSameComponent = true;	//����Component�������邩

		virtual void Update();
};
