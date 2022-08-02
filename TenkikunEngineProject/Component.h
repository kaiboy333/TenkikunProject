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
		GameObject* gameobject = nullptr;	//‚±‚ÌComponent‚ğ‚ÂGameObject

		bool canPutSameComponent = true;	//“¯‚¶Component‚ğ“ü‚ê‚ç‚ê‚é‚©

		Component(GameObject* gameobject);

		virtual void Update() = 0;
};
