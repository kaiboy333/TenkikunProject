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
		bool isFlipX = false;	//ถEฝ]ฉ
		bool isFlipY = false;	//ใบฝ]ฉ
		//bool isCameraAffected = true;	//Cameraฬฺฎลฉฆ๛ชฯํ้ฉ

		Image* image = nullptr;	//ๆ

		ImageRenderer(GameObject* gameobject);

		void Update() override;

		void Draw();	//ๆ๐`ๆ

		virtual void PreparationLibrate() override;
};

