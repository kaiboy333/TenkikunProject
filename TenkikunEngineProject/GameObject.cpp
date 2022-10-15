#include "GameObject.h"
#include "ImageRenderer.h"
#include "Animator.h"
#include "Collider.h"
#include "ProjectFileManager.h"

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
	while (scene->Find(newName)) {
		newName = name + " (" + std::to_string(no++) + ")";	//新しい候補の名前を作成
	}

	if (SceneManager::GetNowScene() == scene) {
		//TreeListの名前を変える
		TreeNode* node = WindowManager::hierarchyWindow->treeList->FindNode(this->GetPath());	//元の名前で探す
		if (node) {
			//名前セット
			node->SetElement(newName);
		}
	}
	this->name = newName;	//実際に変える
}

std::string GameObject::GetName()
{
	return name;
}

std::string GameObject::GetPath()
{
	Transform* transform = this->transform;
	string path = "";

	//ノードがnullになるまで(ルートの親がnullなのでそこまで)
	for (int i = 0; transform; i++) {
		//最初以外は
		if (i != 0) {
			//\\を追加
			path = "\\" + path;
		}
		//ノードの名前を追加
		path = transform->gameobject->name + path;
		//ノードの親を参照するようにする
		transform = transform->parent;
	}

	//最後にシーンの名前を追加
	path = SceneManager::GetNowScene()->GetName() + "\\" + path;

	return path;

}

void GameObject::PreparationLibrate()
{
	scene = nullptr;
	transform = nullptr;

	//componentsの削除
	for (auto& component : components) {
		//解放準備
		component->PreparationLibrate();
		//解放
		delete(component);
		component = nullptr;
	}
	components.clear();

	//sceneInfosから削除
	ProjectFileManager::sceneInfos.erase(this->fileID);
}

void GameObject::SetScene(Scene* scene)
{
	this->scene = scene;
}

Scene* GameObject::GetScene()
{
	return scene;
}
