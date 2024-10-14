#pragma once
#include"StageObject.h"

class Patrol :public StageObject{
public:
	Patrol(Vec2 pos, float width, float height);
	~Patrol();

	void InitializeStageObject_CreateStage(class CreateStage* createStage)override;

	void UpdateStageObject_CreateStage(float deltaTime)override;

private:

};
