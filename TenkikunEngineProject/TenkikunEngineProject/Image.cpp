#include "Image.h"
#include "ImageManager.h"

inline void Image::Draw()
{
	if (gh != 0) {
		Vector3 pos = this->gameobject->transform->position;
		Vector3 scale = this->gameobject->transform->scale;
		Vector3 rota = this->gameobject->transform->rotation;
		DrawRotaGraph3F(pos.x, pos.y, 0, 0, scale.x, scale.y, rota.z, *gh, TRUE, isFlipX, isFlipY);	//‰æ‘œ‚Ì’†S‚ð‚à‚Æ‚É•`‰æ
	}
}

void Image::SetImage(std::string path)
{
	this->gh = ImageManager::LoadImageA(path);
}
