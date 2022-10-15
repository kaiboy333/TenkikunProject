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
		//���������Ȃ�
		if (iter != components.end()) {
			//�R���|�[�l���g�̃��X�g����폜
			components.erase(std::remove(components.begin(), components.end(), component));
			//���
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
		//DrawComponent������Ȃ�
		if (dynamic_cast<DrawComponent*>(component) != nullptr) {
			DrawComponent* drawComponent = static_cast<DrawComponent*>(component);
			drawComponent->Draw();	//�`��
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
	int no = 1;	//���h�~�p�ԍ�
	//���Ȃ��Ȃ�܂ŌJ��Ԃ�
	while (scene->Find(newName)) {
		newName = name + " (" + std::to_string(no++) + ")";	//�V�������̖��O���쐬
	}

	if (SceneManager::GetNowScene() == scene) {
		//TreeList�̖��O��ς���
		TreeNode* node = WindowManager::hierarchyWindow->treeList->FindNode(this->GetPath());	//���̖��O�ŒT��
		if (node) {
			//���O�Z�b�g
			node->SetElement(newName);
		}
	}
	this->name = newName;	//���ۂɕς���
}

std::string GameObject::GetName()
{
	return name;
}

std::string GameObject::GetPath()
{
	Transform* transform = this->transform;
	string path = "";

	//�m�[�h��null�ɂȂ�܂�(���[�g�̐e��null�Ȃ̂ł����܂�)
	for (int i = 0; transform; i++) {
		//�ŏ��ȊO��
		if (i != 0) {
			//\\��ǉ�
			path = "\\" + path;
		}
		//�m�[�h�̖��O��ǉ�
		path = transform->gameobject->name + path;
		//�m�[�h�̐e���Q�Ƃ���悤�ɂ���
		transform = transform->parent;
	}

	//�Ō�ɃV�[���̖��O��ǉ�
	path = SceneManager::GetNowScene()->GetName() + "\\" + path;

	return path;

}

void GameObject::PreparationLibrate()
{
	scene = nullptr;
	transform = nullptr;

	//components�̍폜
	for (auto& component : components) {
		//�������
		component->PreparationLibrate();
		//���
		delete(component);
		component = nullptr;
	}
	components.clear();

	//sceneInfos����폜
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
