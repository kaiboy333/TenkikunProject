#include "SceneManager.h"
#include "ProjectFileManager.h"
#include "MyString.h"
#include "Debug.h"

SceneManager::SceneManager()
{
	//�V�[���������Ȃ��Ȃ�
	if (scenePathes.size() == 0) {
		MakeScene();	//�V�[�����쐬
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
				//�V�[�����쐬
				Scene* scene = new Scene();
				//�V�[���̃p�X��ݒ�
				scene->scenePath = scenePath;
				nowScene = scene;	//�o�^
				scene->Init();	//������
				//�V�[���t�@�C������ǂݍ���
				ProjectFileManager::LoadSceneFromFile(scenePath, scene);
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

void SceneManager::MakeScene()
{
	//�V�[�����쐬
	Scene* scene = new Scene();

	//�����A���݂̃V�[�����o�^����Ă��Ȃ�������
	if (nowScene == nullptr) {
		nowScene = scene;	//�o�^
	}
	scene->Init();	//������

	//���̃p�X�̒��ɂɃV�[���t�@�C����ݒ�
	std::filesystem::path scenePath(ProjectFileManager::currentPath.string() + "\\" + scene->GetName() + ".scene");
	//�V�[���̃p�X��ݒ�
	scene->scenePath = scenePath;

	//�V�[�����X�g�ɒǉ�
	scenePathes.insert(std::make_pair(scene->GetName(), scenePath));

	std::ofstream ofs(scenePath.c_str());
	//�V�[���t�@�C�����쐬�A�J��
	if (ofs) {
		//�c���[���X�g�ɒǉ��A�_�t�@�C�����쐬
		WindowManager::projectWindow->SetFileChildrenToTreeList(scenePath);
		//�t�@�C���A�C�R���X�V
		WindowManager::projectWindow->filePrintRect->LoadFoler();

		scene->CreateCamera();	//�J��������
		scene->CreateTenkikun();	//�V�C���񐶐�


		//�V�[�����Z�[�u
		SaveScene();
	}
}

void SceneManager::SaveScene()
{
	//�ҏW���[�h�Ȃ�
	if (playMode == PlayMode::EDIT) {
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

std::unordered_map<std::string, std::filesystem::path> SceneManager::scenePathes;
