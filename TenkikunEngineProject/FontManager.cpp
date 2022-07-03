#include "FontManager.h"

FontManager::FontManager()
{
	systemFont = new Font(nullptr, 12, -1, -1);
	systemFontMini = new Font(nullptr, 10, -1, -1);
}

Font* FontManager::systemFont = nullptr;

Font* FontManager::systemFontMini = nullptr;
