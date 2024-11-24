#pragma once
#include "Escapee_Game.h"

class Flashlight {
public:
	Flashlight(class Escapee_Game* owner);
	~Flashlight();

	void Update_Game(float deltaTime);

private:
	class Escapee_Game* mOwner;
};
