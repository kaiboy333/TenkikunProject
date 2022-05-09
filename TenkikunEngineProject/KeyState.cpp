#include "KeyState.h"

void KeyState::Push()
{
	isFirst = !isPush;
	isPush = true;
}

void KeyState::Release()
{
	isFirst = isPush;
	isPush = false;
}

bool KeyState::GetIsPush()
{
	return isPush;
}

bool KeyState::GetIsFirst()
{
	return isFirst;
}
