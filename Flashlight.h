#pragma once
#include "Escapee_Game.h"

class Flashlight {
public:
	Flashlight(class Escapee_Game* owner);
	~Flashlight();

	void Initialize_Game();
	void Initialize_CreateStage();

	void Update_Game(float deltaTime);

	class TriangleComponent* GetTriagleComponent() { return mLightTri; }

private:
	class Escapee_Game* mOwner;
	class TriangleComponent* mLightTri;

	float mLightRange;
	float mHandRange;
	float mLightRad;
	float Pi;
	Vec2 mPos0;
	Vec2 mPos1;
	Vec2 mPos2;

	void SetLightPos0();
	void SetLightPos1();
	void SetLightPos2();
};
