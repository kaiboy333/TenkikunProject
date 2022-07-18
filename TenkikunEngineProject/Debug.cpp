#include "Debug.h"

void Debug::Log(std::string string)
{
	OutputDebugString(std::string(string + "\n").c_str());
}
