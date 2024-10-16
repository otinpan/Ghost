#pragma once
#include"Actor.h"

class Hand :public Actor {
public:
	Hand();
	~Hand();

	void InitializeActor_CreateStage(class CreateStage* createstage) override;

	void UpdateActor_CreateStage(float deltaTime)override;
	void ActorInput(std::vector<Input> keyState)override;

	class CircleComponent* GetCircleComponent() { return cc; }

	bool GetIsGrap() { return mIsGrap; }
	void SetIsGrap(bool isGrap) { mIsGrap = isGrap; }
	bool GetIsExpand() { return mIsExpand; }
	void SetIsExpand(bool isExpand) { mIsExpand = isExpand; }
	bool GetIsChoose() { return mIsChoose; }
	void SetIsChoose(bool isChoose) { mIsChoose = isChoose; }

	class StageObject* & GetChoosing() { return mChoosing; }

private:
	class CircleComponent* cc;
	class InputComponent_Keyboard* ic;
	class StageObject* mGrapping;
	class StageObject* mChoosing;

	float StandardSpeed;

	InputGroup inputUp;
	InputGroup inputDown;
	InputGroup inputRight;
	InputGroup inputLeft;
	InputGroup inputGrap;
	InputGroup inputBack;
	InputGroup inputR;
	InputGroup inputL;
	InputGroup inputChoose;

	std::vector<int> dx;
	std::vector<int> dy;

	bool mIsGrap;
	bool mIsExpand;
	bool mIsChoose;
};

