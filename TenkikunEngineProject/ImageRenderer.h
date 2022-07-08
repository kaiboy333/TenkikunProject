#pragma once

#include "ImageManager.h"
#include "Component.h"
#include "Camera.h"
#include "Window.h"
#include "Image.h"

class Camera;
class ImageRenderer :  public Component
{
	public:
		bool isFlipX = false;	//¶‰E”½“]‚©
		bool isFlipY = false;	//ã‰º”½“]‚©
		//bool isCameraAffected = true;	//Camera‚ÌˆÚ“®‚ÅŒ©‚¦•û‚ª•Ï‚í‚é‚©

		Image* image = nullptr;	//‰æ‘œ

		void Update() override;

		void Draw(Window* parentWindow, Camera* camera);	//‰æ‘œ‚ğ•`‰æ
};

