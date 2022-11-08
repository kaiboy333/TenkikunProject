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
	Transform* transform = nullptr;	//位置などの情報

	std::vector<Component*> components;	//Componentたち

	GameObject();

	template<class T>
	T* AddComponent();		//指定のComponentを追加

	template<class T>
	T* GetComponent();		//GameObjectに追加されている指定のComponentを取得

	template<class T>
	std::vector<T*> GetComponents();		//GameObjectに追加されている指定のComponentをすべて取得

	void RemoveComponent(Component* component);	//Component削除

	void Update();	//Componentの更新

	void Draw();	//GameObjectの描画Componentを描画

	static GameObject* Find(std::string name);	//名前からオブジェクトを取得する

	void SetName(std::string name);
	std::string GetName();

	std::string GetPath();	//親などを含めたパスを取得(TreeList用)

	virtual void PreparationLibrate() override;

	void SetScene(Scene* scene);
	Scene* GetScene();
};

template<class T>
inline T* GameObject::AddComponent()
{
	Component* component = new T(this);	//Componentの親を生成

	//もし同じものを入れてはいけなかったら
	if (!component->canPutSameComponent) {
		auto* pushedComponent = this->GetComponent<T>();
		//既に入っていたら
		if (pushedComponent != nullptr) {
			return nullptr;	//nullptrを返す
		}
	}

	this->components.emplace_back(component);	//末尾に追加
	component->transform = this->GetComponent<Transform>();	//Transformをセット
	
	return dynamic_cast<T*>(component);	//インスタンスを返す
}

template<class T>
inline T* GameObject::GetComponent()
{
	const std::type_info& type = typeid(T);
	for (Component* targetComponent : components) {
		//同じ型だったら
		if (type == typeid(*targetComponent)) {
			return dynamic_cast<T*>(targetComponent);	//見つかったComponent返す
		}
		//別の型だったら(親の型だったら)
		else if (type == typeid(targetComponent)) {
			return dynamic_cast<T*>(targetComponent);	//見つかったComponent返す
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
		//同じ型だったら
		if (type == typeid(*targetComponent)) {
			targetComponents.push_back(dynamic_cast<T*>(targetComponent));	//見つかったComponent追加
		}
		//親の型だったら(キャスト変換可能なら)
		else if (dynamic_cast<T*>(targetComponent) != nullptr) {
			targetComponents.push_back(dynamic_cast<T*>(targetComponent));	//見つかったComponent追加
		}
	}

	return targetComponents;
}
