#pragma once

#include "ImageManager.h"
#include "DrawComponent.h"
#include "Camera.h"
#include "Window.h"
#include "Image.h"

class Camera;
class Image;
class ImageRenderer :  public DrawComponent
{
	public:
		bool isFlipX = false;	//¶‰E”½“]‚©
		bool isFlipY = false;	//ã‰º”½“]‚©
		//bool isCameraAffected = true;	//Camera‚ÌˆÚ“®‚ÅŒ©‚¦•û‚ª•Ï‚í‚é‚©

		Image* image = nullptr;	//‰æ‘œ

		ImageRenderer(GameObject* gameobject);

		void Update() override;

		void Draw();	//‰æ‘œ‚ğ•`‰æ
};

