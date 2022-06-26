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

void GameObject::Draw(Window* parentWindow, Camera* camera)
{
	Component* component = nullptr;
	//ImageComponentがあるなら
	if ((component = this->GetComponent<ImageRenderer>()) != nullptr) {
		ImageRenderer* image = static_cast<ImageRenderer*>(component);
		image->Draw(parentWindow, camera);	//描画
	}
}

void GameObject::SetTreeNodeName(std::string name)
{
	//TreeListの名前を変える
	TreeList* treeList = SceneManager::GetNowScene()->treeList;
	TreeNode* node = treeList->FindNode(this->name);	//元の名前で探す
	if (node) {
		//名前セット
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
	int no = 1;	//被り防止用番号
	string newName = name;	//新しい候補の名前
	//被らなくなるまで繰り返す
	while (GameObject::Find(newName)) {
		newName = name + " (" + std::to_string(no++) + ")";	//新しい候補の名前を作成
	}
	name = newName;	//nameを新しい名前に
	SetTreeNodeName(name);	//TreeNodeの名前を変えて
	this->name = name;	//実際に変える
}

std::string GameObject::GetName()
{
	return name;
}
