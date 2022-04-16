#include "GameObject.h"

GameObject::GameObject()
{
	Transform* transform = this->AddComponent<Transform>();	//Transformをついか
	this->transform = transform;
}

inline void GameObject::InternalAddComponent(Component* component)
{
	component->gameobject = this;	//ComponentにGameObjectを紐づける
	components.emplace_back();	//末尾に追加
}

template<class T>
inline T* GameObject::AddComponent()
{
	auto component = new T();	//Componentの親を生成
	//もし同じものを入れてはいけなかったら
	if (!component->canPutSameComponent) {
		auto* pushedComponent = this->GetComponent<T>();
		//既に入っていたら
		if (pushedComponent == nullptr) {
			return nullptr;	//nullptrを返す
		}
	}
	InternalAddComponent(component);
	return static_cast<T*>(component);	//インスタンスを返す
}

template<class T>
inline T* GameObject::GetComponent()
{
	return nullptr;
}

