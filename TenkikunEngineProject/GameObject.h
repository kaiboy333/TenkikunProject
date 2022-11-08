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
#include "Transform.h"

class Scene;
class Camera;
class GameObject : public SceneInfo
{
private:
	std::string name = "";

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

	this->components.emplace_back(component);	//�����ɒǉ�
	component->transform = this->GetComponent<Transform>();	//Transform���Z�b�g
	
	return dynamic_cast<T*>(component);	//�C���X�^���X��Ԃ�
}

template<class T>
inline T* GameObject::GetComponent()
{
	const std::type_info& type = typeid(T);
	for (Component* targetComponent : components) {
		//�����^��������
		if (type == typeid(*targetComponent)) {
			return dynamic_cast<T*>(targetComponent);	//��������Component�Ԃ�
		}
		//�ʂ̌^��������(�e�̌^��������)
		else if (type == typeid(targetComponent)) {
			return dynamic_cast<T*>(targetComponent);	//��������Component�Ԃ�
		}
	}
	return nullptr;
}

template<class T>
inline std::vector<T*> GameObject::GetComponents()
{
	std::vector<T*> targetComponents;
	const std::type_info& type = typeid(T);

	for (Component* targetComponent : components) {
		//�����^��������
		if (type == typeid(*targetComponent)) {
			targetComponents.push_back(dynamic_cast<T*>(targetComponent));	//��������Component�ǉ�
		}
		//�e�̌^��������(�L���X�g�ϊ��\�Ȃ�)
		else if (dynamic_cast<T*>(targetComponent) != nullptr) {
			targetComponents.push_back(dynamic_cast<T*>(targetComponent));	//��������Component�ǉ�
		}
	}

	return targetComponents;
}
