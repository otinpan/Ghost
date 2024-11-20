#pragma once
#include"StageObject.h"

class Key :public StageObject {
public:
	Key(Vec2 pos, float width, float height);
	~Key();

	void InitializeStageObject_CreateStage(class CreateStage* createStage)override;
	void InitializeStageObject_Game(class Game* game)override;

	void UpdateStageObject_CreateStage(float deltaTime)override;
	void UpdateStageObject_Game(float deltaTime)override;
};
