#include "Script.h"

void Script::Update()
{
	if (isFirstUpdate) {
		ScriptStart();
		isFirstUpdate = false;	//2‰ñ–Ú‚©‚ç‚ÍŒÄ‚Î‚ê‚È‚¢
	}
	ScriptUpdate();
}
