#include "GameObject.h"
#include "ImageRenderer.h"
#include "Animator.h"

GameObject::GameObject()
{
	Transform* transform = this->AddComponent<Transform>();	//Transform������
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
	//ImageComponent������Ȃ�
	if ((component = this->GetComponent<ImageRenderer>()) != nullptr) {
		ImageRenderer* image = static_cast<ImageRenderer*>(component);
		image->Draw(parentWindow, camera);	//�`��
	}
}

void GameObject::SetTreeNodeName(std::string name)
{
	//TreeList�̖��O��ς���
	TreeList* treeList = SceneManager::GetNowScene()->treeList;
	TreeNode* node = treeList->FindNode(this->name);	//���̖��O�ŒT��
	if (node) {
		//���O�Z�b�g
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
	int no = 1;	//���h�~�p�ԍ�
	string newName = name;	//�V�������̖��O
	//���Ȃ��Ȃ�܂ŌJ��Ԃ�
	while (GameObject::Find(newName)) {
		newName = name + " (" + std::to_string(no++) + ")";	//�V�������̖��O���쐬
	}
	name = newName;	//name��V�������O��
	SetTreeNodeName(name);	//TreeNode�̖��O��ς���
	this->name = name;	//���ۂɕς���
}

std::string GameObject::GetName()
{
	return name;
}
