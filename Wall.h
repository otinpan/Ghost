#pragma once
#include"StageObject.h"

class Wall :public StageObject {
public:
	Wall(Vec2 pos, float width, float height);
	~Wall();

	void InitializeStageObject_CreateStage(class CreateStage* createStage)override;
	void InitializeStageObject_Game(class Game* game)override;


};
