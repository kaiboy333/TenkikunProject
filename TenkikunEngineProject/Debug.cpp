#include "Debug.h"

void Debug::Log(std::string string)
{
	OutputDebugString(string.c_str());
}
