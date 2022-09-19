#include "SceneManager.h"
#include "ProjectFileManager.h"
#include "MyString.h"
#include "Debug.h"
#include "CreateBallScript.h"

SceneManager::SceneManager()
{
	//�V�[���������Ȃ��Ȃ�
	if (scenePathes.size() == 0) {
		MakeScene(ProjectFileManager::sceneFilePath);	//�V�[�����쐬
	}
	//����Ȃ�
	else {
		//�}�b�v�̍ŏ��̃V�[���p�X��ǂݍ���
		LoadScene(scenePathes.begin()->first);
	}
}

void SceneManager::LoadScene(std::string sceneName)
{
	//�V�[�������݂���Ȃ�
	if (scenePathes.contains(sceneName)) {
		//�V�[���p�X���擾
		std::filesystem::path scenePath = scenePathes[sceneName];
		//�V�[���t�@�C����������
		if (ProjectFileManager::GetFileType(scenePath) == ProjectFileManager::FileType::Scene) {
			//�V�[���t�@�C�����J��
			std::ifstream ifs(scenePath);
			//�J������
			if (ifs) {
				ProjectFileManager::LoadFromFile();	//���̃t�@�C����ǂݍ���
				ProjectFileManager::LoadFromSceneFile(scenePath);	//�V�[���t�@�C������V�[�����Č�
			}
		}
	}
	else {
		Debug::Log("����Scene�̖��O�͑��݂��܂���B");
	}
}

Scene* SceneManager::GetNowScene()
{
	return nowScene;
}

void SceneManager::MakeScene(std::filesystem::path parentPath)
{
	//�e���t�H���_�[����Ȃ��Ȃ���Ȃ�
	if (ProjectFileManager::GetFileType(parentPath) != ProjectFileManager::FileType::Folder)
		return;

	//�V�[�����쐬
	Scene* scene = new Scene();

	//�����A���݂̃V�[�����o�^����Ă��Ȃ�������
	if (nowScene == nullptr) {
		nowScene = scene;	//�o�^
	}
	scene->Init();	//������

	//�e�̃t�H���_���̒��ɃV�[���t�@�C����ݒ�
	std::filesystem::path scenePath(parentPath.string() + "\\" + scene->GetName() + ".scene");
	//�V�[���̃p�X��ݒ�
	scene->scenePath = scenePath;	//�t�@�C�����쐬
	std::ofstream ofs(scenePath.c_str());

	//�_�t�@�C�����쐬
	ProjectFileManager::WriteToKumoFile(scenePath.string() + ".kumo");
	WindowManager::projectWindow->filePrintRect->LoadFoler();

	//�V�[�����X�g�ɒǉ�
	scenePathes.insert(std::make_pair(scene->GetName(), scenePath));

	scene->CreateCamera(false);	//�J��������
	//scene->CreateTenkikun(false);	//�V�C���񐶐�
	//scene->CreateSquare(false);
	//GameObject* circle = scene->CreateCircle(false);
	//circle->transform->position = Vector3(-50, 0, 0);
	//GameObject* circle2 = scene->CreateCircle(false);
	//circle2->transform->position = Vector3(50, 0, 0);
	//scene->CreateUnityChan(false);	//Unity����񐶐�

	GameObject* o = scene->CreateEmpty(false);
	o->AddComponent<CreateBallScript>();

	//�V�[�����Z�[�u
	SaveScene();
}

void SceneManager::SetNowScene(Scene* scene)
{
	nowScene = scene;
}

void SceneManager::SaveScene()
{
	//�ҏW���[�h�Ȃ�
	if (playMode == PlayMode::EDIT) {
		std::unordered_map<SceneInfo*, int> idInfos;
		//�V�[���ȊO�̏����t�@�C���ɏ�������
		ProjectFileManager::WriteToFile();
		//���݂̃V�[�����Z�[�u(�V�[���t�@�C���ɏ�������)
		ProjectFileManager::WriteToSceneFile(nowScene);
		Debug::Log(nowScene->GetName() + "���Z�[�u���܂����B");
	}
	else {
		Debug::Log("�v���C���̓Z�[�u�ł��܂���B");
	}
}

Scene* SceneManager::nowScene = nullptr;	//���݂�Scene
SceneManager::PlayMode SceneManager::playMode = PlayMode::EDIT;	//�����͕ҏW���[�h

std::map<std::string, std::filesystem::path> SceneManager::scenePathes;
