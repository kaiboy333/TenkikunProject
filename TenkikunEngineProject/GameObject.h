#pragma once

#include <vector>
#include "Transform.h"
#include <iostream>
#include "Window.h"
#include "Camera.h"
#include "Scene.h"
#include <typeinfo>
#include "SceneManager.h"
#include "Property.h"

class Scene;
class Camera;
class GameObject
{
	private:
		std::string name = "";

		void SetTreeNodeName(std::string name);	//���O�ύX

		void InternalAddComponent(Component* component);	//���ۂɒǉ�����֐�

	public:
		Transform* transform = nullptr;	//�ʒu�Ȃǂ̏��

		std::vector<Component*> components;	//Component����

		GameObject();

		template<class T>
		T* AddComponent();		//�w���Component��ǉ�

		template<class T>
		T* GetComponent();		//GameObject�ɒǉ�����Ă���w���Component���擾

		void Update();	//Component�̍X�V

		void Draw(Window* parentWindow, Camera* camera);	//GameObject�̕`��Component��`��

		static GameObject* Find(std::string name);	//���O����I�u�W�F�N�g���擾����

		void SetName(std::string name);
		std::string GetName();
};

inline void GameObject::InternalAddComponent(Component* component)
{
	component->gameobject = this;	//Component��GameObject��R�Â���
	this->components.emplace_back(component);	//�����ɒǉ�
}

template<class T>
inline T* GameObject::AddComponent()
{
	Component* component = new T();	//Component�̐e�𐶐�
	//�����������̂����Ă͂����Ȃ�������
	if (!component->canPutSameComponent) {
		auto* pushedComponent = this->GetComponent<T>();
		//���ɓ����Ă�����
		if (pushedComponent != nullptr) {
			return nullptr;	//nullptr��Ԃ�
		}
	}
	InternalAddComponent(component);
	return dynamic_cast<T*>(component);	//�C���X�^���X��Ԃ�
}

template<class T>
inline T* GameObject::GetComponent()
{
	Component* component = new T();	//Component�̐e�𐶐�
	const std::type_info& type = typeid(*component);
	for (Component* targetComponent : components) {
		//�L���X�g�ϊ��\�Ȃ�
		if (dynamic_cast<T*>(component) != nullptr) {
			//�����^��������
			if (type == typeid(*targetComponent)) {
				delete(component);	//�s�v��component���
				component = nullptr;
				return dynamic_cast<T*>(targetComponent);	//��������Component�Ԃ�
			}
			//�ʂ̌^��������(�e�̌^��������)
			else if (type == typeid(targetComponent)) {
				delete(component);	//�s�v��component���
				component = nullptr;
				return dynamic_cast<T*>(targetComponent);	//��������Component�Ԃ�
			}
		}
	}
	delete(component);	//�s�v��component���
	component = nullptr;
	return nullptr;
}