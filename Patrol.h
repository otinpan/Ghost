#pragma once
#include"StageObject.h"

class Partol:public StageObject{
public:
	Patrol(Vec2 pos, float width, float height);
	~Patrol();

	void InitialzeStageObject_CreateStage(class CreateStage* createStage)override;

	void UpdateStageObject_CreateStage(float deltaTime)override;
};
