#pragma once

#include "Librate.h"

class SceneInfo : public Librate
{
	public:
		int fileID;

		SceneInfo();

		virtual void PreparationLibrate() = 0;
};

