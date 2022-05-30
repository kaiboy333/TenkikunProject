#pragma once

#include "Window.h"
#include "Scene.h"
#include "Camera.h"

class Scene;
class Camera;
class GameWindow :  public Window
{
	public:
		GameWindow();
		void Draw() override;	//Sceneã‚ÌGameObject‚ğ•`‰æ
};

