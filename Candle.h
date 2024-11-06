#pragma once
#include"StageObject.h"


class Candle:public StageObject{
public:
	Candle(Vec2 pos,float width,float height,float rad);
	~Candle();

	void InitializeStageObject_CreateStage(class CreateStage* createStage)override;
	void UpdateStageObject_CreateStage(float deltaTime)override;

	void InitializeStageMenu_CreateStage()override;
	void UpdateStageMenu_CreateStage(float deltaTime)override;
	void DrawStageMenu_CreateStage()override;
	void ShutdownStageMenu_CreateStage()override;

	class CircleComponent*& GetCircleComponent() { return cc; }
private:
	class CircleComponent* cc;

	class SquareComponent* mBarSC_CreateStage;

	Vec2 mCenter;
	float mMaxLightRadius;
	float mMinLightRadius;
	float mLightRadRange;

	Vec2 mBarCenter;
	Vec2 mBarPos;
	float mBarMax;
	float mBarMin;
	float mBarHeight;

	bool mIsBarGripen;


	float ConvertToBar(float lightRad);
	float ConvertToLightRad(float bar);

};
