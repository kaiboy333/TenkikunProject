#include "MenuList.h"
#include "FontManager.h"

MenuList::MenuList(float startX, float startY, std::vector<std::string> elements) : Rect(startX, startY, WIDTH, FontManager::systemFont->GetFontHeight())
{

}
