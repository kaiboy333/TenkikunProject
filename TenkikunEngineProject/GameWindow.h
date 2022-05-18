#pragma once

#include "Window.h"
#include "Scene.h"
#include "Camera.h"

class Scene;
class Camera;
class GameWindow :  public Window
{
	public:
		GameWindow(int width, int height);
		void Draw() override;	//Sceneã‚ÌGameObject‚ğ•`‰æ
};

