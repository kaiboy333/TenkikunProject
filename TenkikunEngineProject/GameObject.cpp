#include "GameObject.h"
#include "ImageRenderer.h"
#include "Animator.h"

GameObject::GameObject()
{
	Transform* transform = this->AddComponent<Transform>();	//Transformをついか
	this->transform = transform;
}

void GameObject::Update()
{
	for (Component* component : components) {
		component->Update();
	}
}

void GameObject::Draw(Window* window, Camera* camera)
{
	Component* component = nullptr;
	//ImageComponentがあるなら
	if ((component = this->GetComponent<ImageRenderer>()) != nullptr) {
		ImageRenderer* image = static_cast<ImageRenderer*>(component);
		image->Draw(window, camera);	//描画
	}
}

void GameObject::SetTreeNodeName(std::string name)
{
	//TreeListの名前を変える
	TreeList* treeList = SceneManager::GetNowScene()->treeList;
	//名前セット
	TreeNode* node = treeList->FindNode(this->name);
	if (node) {
		node->SetElement(name);
	}
}

GameObject* GameObject::Find(std::string name)
{
	Scene* scene = SceneManager::GetNowScene();

	for (GameObject* gameobject : scene->gameobjects) {
		if (gameobject->name == name) {
			return gameobject;
		}
	}
	return nullptr;
}

void GameObject::SetName(std::string name)
{
	SetTreeNodeName(name);	//TreeNodeの名前を変えて
	this->name = name;	//実際に変える
}

std::string GameObject::GetName()
{
	return name;
}
