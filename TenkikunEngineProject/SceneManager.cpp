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
		Debug::Log("����Scene�̖��O�͑��݂��܂���B\n");
	}
}

Scene* SceneManager::GetNowScene()
{
	return nowScene;
}

void SceneManager::MakeScene()
{
	Scene* scene = nullptr;

	//���̃p�X�ɃV�[���t�@�C����ݒ�
	std::filesystem::path scenePath(ProjectFileManager::currentPath.string() + ".scene");

	std::ofstream ofs(scenePath.c_str());
	//�V�[���t�@�C�����쐬�A�J��
	if (ofs) {
		//�V�[�����쐬
		scene = new Scene();
		//�V�[���̃p�X��ݒ�
		scene->scenePath = scenePath;
		//�����A���݂̃V�[�����o�^����Ă��Ȃ�������
		if (nowScene == nullptr) {
			nowScene = scene;	//�o�^
		}
		scene->Init();	//������

		scene->CreateCamera();	//�J��������
		scene->CreateSquare();	//�l�p����


		//�c���[���X�g�ɒǉ��A�_�t�@�C�����쐬
		WindowManager::projectWindow->SetFileChildrenToTreeList(scenePath);
		//�t�@�C���A�C�R���X�V
		WindowManager::projectWindow->filePrintRect->LoadFoler();
	}
}

Scene* SceneManager::nowScene = nullptr;	//���݂�Scene
SceneManager::PlayMode SceneManager::playMode = PlayMode::EDIT;	//�����͕ҏW���[�h

std::unordered_map<std::string, std::filesystem::path> SceneManager::scenePathes;
