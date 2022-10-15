#pragma once

#include "Component.h"
#include <iostream>
#include "Window.h"
#include "Scene.h"

class Camera : public Component
{
    public:
        int width = 700,  height = 500;
        float zoom = 1.0f;
        //float zoomSpeed = 0.1f;

        Camera(GameObject* gameobject);

        void Update() override;

        static Vector3 ScreenToWorldPoint(Vector3 screenPosition);  //スクリーン座標からワールド座標に変換する

        static Vector3 WorldToScreenPoint(Vector3 worldPosition);   //ワールド座標からスクリーン座標に変換する

        virtual void PreparationLibrate() override;
};

