#include "GameObject.h"

GameObject::GameObject()
{
	Transform* transform = this->AddComponent<Transform>();	//Transform������
	this->transform = transform;
}

inline void GameObject::InternalAddComponent(Component* component)
{
	component->gameobject = this;	//Component��GameObject��R�Â���
	components.emplace_back();	//�����ɒǉ�
}

template<class T>
inline T* GameObject::AddComponent()
{
	auto component = new T();	//Component�̐e�𐶐�
	//�����������̂����Ă͂����Ȃ�������
	if (!component->canPutSameComponent) {
		auto* pushedComponent = this->GetComponent<T>();
		//���ɓ����Ă�����
		if (pushedComponent == nullptr) {
			return nullptr;	//nullptr��Ԃ�
		}
	}
	InternalAddComponent(component);
	return static_cast<T*>(component);	//�C���X�^���X��Ԃ�
}

template<class T>
inline T* GameObject::GetComponent()
{
	return nullptr;
}

