#pragma once
#include"StageObject.h"


class Candle:public StageObject{
public:
	Candle(Vec2 pos,float width,float height,float rad);
	~Candle();

	void InitializeStageObject_CreateStage(class CreateStage* createStage)override;
	void UpdateStageObject_CreateStage(float deltaTime)override;

	class CircleComponent*& GetCircleComponent() { return cc; }



private:
	class CircleComponent* cc;

	Vec2 mCenter;
	float mMaxLightRadius;
	float mMinLightRadius;
	
};
