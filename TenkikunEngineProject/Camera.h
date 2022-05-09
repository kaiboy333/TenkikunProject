#pragma once

#include "Component.h"
#include <iostream>
#include "Window.h"
#include "Scene.h"

class Camera : public Component
{
    public:
        int width = 700,  height = 500;
        float zoom = 1;

        Camera();

        void Update() override;

        void Draw(Window* window);  //Scene‚É‚ ‚éGameObject‚ð•`‰æ
};

