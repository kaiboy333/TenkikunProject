#include "Debug.h"
#include <debugapi.h>

void Debug::Log(stringstream ss)
{
	OutputDebugString(ss.str().c_str());
}
