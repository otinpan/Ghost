#pragma once
#include "Escapee_Game.h"

class Flashlight {
public:
	Flashlight(class Escapee_Game* owner);
	~Flashlight();

	void Initialize_Game();
	void Initialize_CreateStage();

	void Update_Game(float deltaTime);

	void SetIsLightOn(bool isLightOn) { mIsLightOn = isLightOn; }
	bool GetIsLightOn() { return mIsLightOn; }

	class TriangleComponent* &GetTriagleComponent() { return mLightTri; }

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

	bool mIsLightOn;

	void SetLightPos0();
	void SetLightPos1();
	void SetLightPos2();
};
