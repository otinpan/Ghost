#pragma once
#include"StageObject.h"

class TreasureChest :public StageObject {
public:
	TreasureChest(Vec2 pos, float width,float height);
	~TreasureChest();

	void InitializeStageObject_CreateStage(class CreateStage* createStage) override;

	void UpdateStageObject_CreateStage(float deltaTime)override;

};
