#include "Script.h"

void Script::Update()
{
	if (isFirstUpdate) {
		ScriptStart();
		isFirstUpdate = false;	//2��ڂ���͌Ă΂�Ȃ�
	}
	ScriptUpdate();
}
