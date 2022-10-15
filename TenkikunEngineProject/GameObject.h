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
#include "SceneInfo.h"

class Scene;
class Camera;
class GameObject : public SceneInfo
{
private:
	std::string name = "GameObject";

	Scene* scene = nullptr;

public:
	Transform* transform = nullptr;	//�ʒu�Ȃǂ̏��

	std::vector<Component*> components;	//Component����

	GameObject();

	template<class T>
	T* AddComponent();		//�w���Component��ǉ�

	template<class T>
	T* GetComponent();		//GameObject�ɒǉ�����Ă���w���Component���擾

	template<class T>
	std::vector<T*> GetComponents();		//GameObject�ɒǉ�����Ă���w���Component�����ׂĎ擾

	void RemoveComponent(Component* component);	//Component�폜

	void Update();	//Component�̍X�V

	void Draw();	//GameObject�̕`��Component��`��

	static GameObject* Find(std::string name);	//���O����I�u�W�F�N�g���擾����

	void SetName(std::string name);
	std::string GetName();

	std::string GetPath();	//�e�Ȃǂ��܂߂��p�X���擾(TreeList�p)

	virtual void PreparationLibrate() override;

	void SetScene(Scene* scene);
	Scene* GetScene();
};

template<class T>
inline T* GameObject::AddComponent()
{
	Component* component = new T(this);	//Component�̐e�𐶐�

	//�����������̂����Ă͂����Ȃ�������
	if (!component->canPutSameComponent) {
		auto* pushedComponent = this->GetComponent<T>();
		//���ɓ����Ă�����
		if (pushedComponent != nullptr) {
			return nullptr;	//nullptr��Ԃ�
		}
	}

	//component->gameobject = this;	//Component��GameObject��R�Â���
	this->components.emplace_back(component);	//�����ɒǉ�

	return dynamic_cast<T*>(component);	//�C���X�^���X��Ԃ�
}

template<class T>
inline T* GameObject::GetComponent()
{
	//Component* component = new T();	//Component�̐e�𐶐�
	const std::type_info& type = typeid(T);
	for (Component* targetComponent : components) {
		////�L���X�g�ϊ��\�Ȃ�
		//if (dynamic_cast<T*>(component) != nullptr) {
			//�����^��������
		if (type == typeid(*targetComponent)) {
			//delete(component);	//�s�v��component���
			//component = nullptr;
			return dynamic_cast<T*>(targetComponent);	//��������Component�Ԃ�
		}
		//�ʂ̌^��������(�e�̌^��������)
		else if (type == typeid(targetComponent)) {
			//delete(component);	//�s�v��component���
			//component = nullptr;
			return dynamic_cast<T*>(targetComponent);	//��������Component�Ԃ�
		}
		//}
	}
	//delete(component);	//�s�v��component���
	//component = nullptr;
	return nullptr;
}

template<class T>
inline std::vector<T*> GameObject::GetComponents()
{
	std::vector<T*> targetComponents;
	//Component* component = new T();	//Component�̐e�𐶐�
	const std::type_info& type = typeid(T);

	for (Component* targetComponent : components) {
		////�L���X�g�ϊ��\�Ȃ�
		//if (dynamic_cast<T*>(component) != nullptr) {
			//�����^��������
		if (type == typeid(*targetComponent)) {
			targetComponents.push_back(dynamic_cast<T*>(targetComponent));	//��������Component�ǉ�
		}
		//�e�̌^��������(�L���X�g�ϊ��\�Ȃ�)
		else if (dynamic_cast<T*>(targetComponent) != nullptr) {
			targetComponents.push_back(dynamic_cast<T*>(targetComponent));	//��������Component�ǉ�
		}
		//else if (type == typeid(targetComponent)) {
		//	targetComponents.push_back(dynamic_cast<T*>(targetComponent));	//��������Component�ǉ�
		//}
	//}
	}

	//delete(component);	//�s�v��component���
	//component = nullptr;
	return targetComponents;
}
