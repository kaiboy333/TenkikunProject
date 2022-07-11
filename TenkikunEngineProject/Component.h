#pragma once

#include <typeinfo>
#include <iostream>
#include "SceneInfo.h"

class GameObject;
class Component : public SceneInfo
{
	public:
		GameObject* gameobject = nullptr;	//‚±‚ÌComponent‚ğ‚ÂGameObject

		bool canPutSameComponent = true;	//“¯‚¶Component‚ğ“ü‚ê‚ç‚ê‚é‚©

		virtual void Update();
};
