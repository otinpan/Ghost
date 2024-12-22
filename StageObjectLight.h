#pragma once
#include"StageObject.h"

class StageObjectLight {
public:
		StageObjectLight(class StageObject* owner);
		~StageObjectLight();

		void Initialize_Game();
		void Initialize_CreateStage();

		void Update_Game(float deltaTime);

private:
	class StageObject* mOwner;
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
