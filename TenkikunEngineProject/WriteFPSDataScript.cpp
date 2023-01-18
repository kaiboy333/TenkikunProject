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
	//親のフォルダ内の中にシーンファイルを設定
	std::filesystem::path filePath(ProjectFileManager::assetFilePath.string() + "\\" + fileName + ".txt");
	ofs = std::ofstream(filePath);
}

void WriteFPSDataScript::MonoUpdate()
{
	//右クリックを押したら
	if ((Input::GetMouseButtonDown(Input::MouseCode::Mouse_Right) && !canWrite) || (canWrite && count >= MAX_COUNT)) {
		canWrite = !canWrite;
		Debug::Log(canWrite ? "記録開始" : "記録終了");
		if (!canWrite) {
			count = 0;
		}
	}
	//書き込むときで、開けるなら
	if (canWrite && ofs) {
		auto nowFPS = Time::GetFPS();
		//fpsが変化したら
		if (beforeFPS != nowFPS) {
			ofs << std::to_string(nowFPS) << std::endl;
			beforeFPS = nowFPS;
			++count;
		}
	}
}
