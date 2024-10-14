#pragma once
#include"StageObject.h"

class Battery :public StageObject {
public:
	Battery(Vec2 pos, float width, float height);
	~Battery();

	void InitializeStageObject_CreateStage(class CreateStage* createStage)override;

	void UpdateStageObject_CreateStage(float deltaTime)override;
};
