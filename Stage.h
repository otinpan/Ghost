#pragma once
#include"CreateStage.h"

class Stage {
public:
	Stage(class CreateStae* createstage);
	~Stage();

	void Update(float deltaTime);
	void Draw();

private:
	class CreateStage* mCreateStage;

};
