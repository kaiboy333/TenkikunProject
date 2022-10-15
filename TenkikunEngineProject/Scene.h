#pragma once

#include <iostream>
#include <vector>
#include "GameObject.h"
#include "Camera.h"
#include "ImageRenderer.h"
#include "WindowManager.h"
#include "Window.h"

class TreeList;
class Scene : public SceneInfo
{
	public:
		std::vector<GameObject*> gameobjects;	//GameObjectたち

		//TreeList* treeList = nullptr;

		std::filesystem::path scenePath;

		std::vector<function<void()>> addAndRemoveEvents;	//追加、削除の関数をいれる

		Scene();

		void Update();

		void Draw();

		GameObject* CreateEmpty(bool isLaterAdd = true);	//空のゲームオブジェクトを作成(後で追加するか)
		GameObject* CreateSquare(bool isLaterAdd = true);	//四角い画像のゲームオブジェクトを作成
		GameObject* CreateCircle(bool isLaterAdd = true);	//円の画像のゲームオブジェクトを作成
		GameObject* CreateCamera(bool isLaterAdd = true);	//カメラゲームオブジェクトを作成
		GameObject* CreateTenkikun(bool isLaterAdd = true);	//天気くんの画像のゲームオブジェクトを作成
		GameObject* CreateUnityChan(bool isLaterAdd = true);	//アニメーションがついたUnityちゃんのゲームオブジェクト作成

		void Destroy(GameObject* gameobject);	//指定のGameObjectを削除

		void SetNowCamera(Camera* camera);	//カメラをセット
		Camera* GetNowCamera();	//カメラを取得

		void AddCamera(Camera* camera);	//カメラを追加

		std::vector<Camera*> GetCameras();

		std::string GetName();
		void SetName(std::string name, bool isForce = false);	//名前を変える(強制でその名前にする)

		virtual void PreparationLibrate() override;

		GameObject* Find(std::string name);

	private:
		std::string name = "Scene";	//Sceneの名前

		Camera* nowCamera = nullptr;

		std::vector<Camera*> cameras;	//Cameraたち
};

