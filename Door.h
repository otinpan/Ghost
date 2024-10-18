#pragma once
#include"StageObject.h"

class Door:public StageObject {
public:
	Door(Vec2 pos, float widht, float height);
	~Door();

	void InitializeStageObject_CreateStage(class CreateStage* createStage)override;

	void UpdateStageObject_CreateStage(float deltaTime)override;

	Vec2 GetDoorCenter() { return mDoorCenter; }
	float GetDoorWidth() { return mDoorWidth; }
	float GetDoorHeight() { return mDoorHeight; }


private:
	SquareComponent* sc;

	std::vector<float> DoorRel_dy;
	std::vector<float> DoorRel_dx;
	std::vector<float> DoorWidth;
	std::vector<float> DoorHeight;


	Vec2 mDoorCenter;
	float mDoorWidth;
	float mDoorHeight;
};
