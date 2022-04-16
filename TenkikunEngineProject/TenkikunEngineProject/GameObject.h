#pragma once

#include "Component.h"
#include "Transform.h"
#include <vector>

class Component;
class Transform;
class GameObject
{
	public:
		Transform* transform = nullptr;	//位置などの情報

		GameObject();

		template<class T>
		inline T* AddComponent();		//指定のComponentを追加

		template<class T>
		inline T* GetComponent();		//GameObjectに追加されている指定のComponentを取得

	private:
		std::vector<Component*> components;	//Componentたち

		inline void InternalAddComponent(Component* component);	//実際に追加する関数
};