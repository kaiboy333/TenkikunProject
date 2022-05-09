#pragma once

#include "Input.h"

class KeyState
{
	public:
		void Push();
		void Release();

		bool GetIsPush();
		bool GetIsFirst();

	private:
		bool isPush = false;
		bool isFirst = false;
};

