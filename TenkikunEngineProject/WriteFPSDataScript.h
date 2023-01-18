#pragma once

#include "MonoBehaviour.h"

class WriteFPSDataScript : public MonoBehaviour
{
	public:
		std::ofstream ofs;

		WriteFPSDataScript(GameObject* gameobject);

		virtual void OnColliderEnter(Collision* collision) override;
		virtual void OnTriggerEnter(Collider* collider) override;

		virtual void OnColliderStay(Collision* collision) override;
		virtual void OnTriggerStay(Collider* collider) override;

		virtual void OnColliderExit(Collision* collision) override;
		virtual void OnTriggerExit(Collider* collider) override;

	protected:
		virtual void MonoStart() override;
		virtual void MonoUpdate() override;

	private:
		std::string fileName = "FPS_NONE";

		bool canWrite = false;

		int count = 0;
		int const MAX_COUNT = 1;

		float beforeFPS = 0;
};

