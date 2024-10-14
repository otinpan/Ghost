#pragma once
#include"StageObject.h"

class Door:public StageObject {
public:
	Door(Vec2 pos, float widht, float height);
	~Door();

	void InitializeStageObject_CreateStage(class CreateStage* createStage)override;

	void UpdateStageObject_CreateStage(float deltaTime)override;
private:
};
