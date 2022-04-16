#pragma once

#include "Component.h"
#include "Transform.h"
#include <vector>

class Component;
class Transform;
class GameObject
{
	public:
		Transform* transform = nullptr;	//�ʒu�Ȃǂ̏��

		GameObject();

		template<class T>
		inline T* AddComponent();		//�w���Component��ǉ�

		template<class T>
		inline T* GetComponent();		//GameObject�ɒǉ�����Ă���w���Component���擾

	private:
		std::vector<Component*> components;	//Component����

		inline void InternalAddComponent(Component* component);	//���ۂɒǉ�����֐�
};