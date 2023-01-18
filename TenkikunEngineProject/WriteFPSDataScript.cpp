#include "WriteFPSDataScript.h"
#include "ProjectFileManager.h"
#include "Time.h"
#include "Debug.h"

WriteFPSDataScript::WriteFPSDataScript(GameObject* gameobject) : MonoBehaviour(gameobject)
{
}

void WriteFPSDataScript::OnColliderEnter(Collision* collision)
{
}

void WriteFPSDataScript::OnTriggerEnter(Collider* collider)
{
}

void WriteFPSDataScript::OnColliderStay(Collision* collision)
{
}

void WriteFPSDataScript::OnTriggerStay(Collider* collider)
{
}

void WriteFPSDataScript::OnColliderExit(Collision* collision)
{
}

void WriteFPSDataScript::OnTriggerExit(Collider* collider)
{
}

void WriteFPSDataScript::MonoStart()
{
	//�e�̃t�H���_���̒��ɃV�[���t�@�C����ݒ�
	std::filesystem::path filePath(ProjectFileManager::assetFilePath.string() + "\\" + fileName + ".txt");
	ofs = std::ofstream(filePath);
}

void WriteFPSDataScript::MonoUpdate()
{
	//�E�N���b�N����������
	if ((Input::GetMouseButtonDown(Input::MouseCode::Mouse_Right) && !canWrite) || (canWrite && count >= MAX_COUNT)) {
		canWrite = !canWrite;
		Debug::Log(canWrite ? "�L�^�J�n" : "�L�^�I��");
		if (!canWrite) {
			count = 0;
		}
	}
	//�������ނƂ��ŁA�J����Ȃ�
	if (canWrite && ofs) {
		auto nowFPS = Time::GetFPS();
		//fps���ω�������
		if (beforeFPS != nowFPS) {
			ofs << std::to_string(nowFPS) << std::endl;
			beforeFPS = nowFPS;
			++count;
		}
	}
}
