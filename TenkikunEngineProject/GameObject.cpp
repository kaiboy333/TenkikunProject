#include "GameObject.h"
#include "ImageRenderer.h"
#include "Animator.h"
#include "Collider.h"

GameObject::GameObject()
{

}

void GameObject::RemoveComponent(Component* component)
{
	if ((int)components.size() != 0) {
		auto iter = std::find(components.begin(), components.end(), component);
		//見つかったなら
		if (iter != components.end()) {
			//コンポーネントのリストから削除
			components.erase(std::remove(components.begin(), components.end(), component));
			//解放
			delete(component);
			component = nullptr;
		}
	}
}

void GameObject::Update()
{
	for (Component* component : components) {
		component->Update();
	}
}

void GameObject::Draw()
{
	for (Component* component : components) {
		auto& type = typeid(*component);
		//DrawComponentがあるなら
		if (dynamic_cast<DrawComponent*>(component) != nullptr) {
			DrawComponent* drawComponent = static_cast<DrawComponent*>(component);
			drawComponent->Draw();	//描画
		}
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
	std::string newName = name;
	int no = 1;	//被り防止用番号
	//被らなくなるまで繰り返す
	while (GameObject::Find(newName)) {
		newName = name + " (" + std::to_string(no++) + ")";	//新しい候補の名前を作成
	}
	SetTreeNodeName(newName);	//TreeNodeの名前を変えて
	this->name = newName;	//実際に変える
}

std::string GameObject::GetName()
{
	return name;
}
