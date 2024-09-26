#pragma once
#include"Actor.h"

class StageObject :public Actor {
public:
	StageObject();
	~StageObject();

	void InitializeActor_CreateStage(class CreateStage* createstage) override;


	void UpdateActor_CreateStage(float deltaTime)override;
	void ActorInput(std::vector<Input> keyState)override;

	class SquareComponent* GetSquareComponent() { return sqc; }

	bool GetIsGripen() { return mIsGripen; }
	void SetIsGripen(bool b) { mIsGripen = b; }


private:
	class SquareComponent* sqc;
	bool mIsGripen;
};
