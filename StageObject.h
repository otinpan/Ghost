#pragma once
#include"Actor.h"

class StageObject :public Actor {
public:
	StageObject();
	~StageObject();

	void InitializeActor_CreateStage(class CreateStage* createstage) override;

	void UpdateActor_CreateStage(float deltaTime)override;
	void ActorInput(std::vector<Input> keyState)override;

private:
	class SquareComponent* sqc;
};
