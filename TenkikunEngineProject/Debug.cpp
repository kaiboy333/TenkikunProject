#include "Debug.h"
#include <debugapi.h>

void Debug::Log(string string)
{
	OutputDebugString(string.c_str());
}
