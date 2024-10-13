#pragma once
#include"StageObject.h"

class Brock :public StageObject {
public:
	Brock(Vec2 pos,float width,float height);
	~Brock();

	void InitializeStageObject_CreateStage(class CreateStage* createStage)override;

	void UpdateStageObject_CreateStage(float deltaTime)override;

private:

};
