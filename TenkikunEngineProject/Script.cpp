#include "Script.h"

void Script::Update()
{
	if (isFirstUpdate) {
		ScriptStart();
		isFirstUpdate = false;	//2回目からは呼ばれない
	}
	ScriptUpdate();
}
