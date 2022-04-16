#pragma once

#include "Component.h"
#include "Transform.h"
#include <vector>

class Component;
class Transform;
class GameObject
{
	public:
		Transform* transform = nullptr;	//ˆÊ’u‚È‚Ç‚Ìî•ñ

		GameObject();

		template<class T>
		inline T* AddComponent();		//w’è‚ÌComponent‚ğ’Ç‰Á

		template<class T>
		inline T* GetComponent();		//GameObject‚É’Ç‰Á‚³‚ê‚Ä‚¢‚éw’è‚ÌComponent‚ğæ“¾

	private:
		std::vector<Component*> components;	//Component‚½‚¿

		inline void InternalAddComponent(Component* component);	//ÀÛ‚É’Ç‰Á‚·‚éŠÖ”
};