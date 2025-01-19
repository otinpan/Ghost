#pragma once
#include "Escapee_Game.h"

class Flashlight {
public:
	Flashlight(class Escapee_Game* owner);
	~Flashlight();

	enum LightSize {
		LightLarge,
		LightMid,
		LightSmall,
	};

	void Initialize_Game();
	void Initialize_CreateStage();

	void Update_Game(float deltaTime);

	void SetIsLightOn(bool isLightOn) { mIsLightOn = isLightOn; }
	bool GetIsLightOn() { return mIsLightOn; }
	void SetLightSize(LightSize lightSize);
	LightSize GetLightSize() { return mLightSize; }

	class TriangleComponent* &GetTriangleComponent() { return mLightTri; }

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
	LightSize mLightSize;

	void SetLightPos0();
	void SetLightPos1();
	void SetLightPos2();
};
