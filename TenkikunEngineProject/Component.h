#pragma once

#include <typeinfo>
#include <iostream>
#include "Info.h"

class GameObject;
class Component : public Info
{
	public:
		GameObject* gameobject = nullptr;	//‚±‚ÌComponent‚ğ‚ÂGameObject

		bool canPutSameComponent = true;	//“¯‚¶Component‚ğ“ü‚ê‚ç‚ê‚é‚©

		virtual void Update() = 0;
};
