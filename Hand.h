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

private:
	class CircleComponent* cc;
	class InputComponent_Keyboard* ic;
	class StageObject* mGrapping;

	float StandardSpeed;

	InputGroup inputUp;
	InputGroup inputDown;
	InputGroup inputRight;
	InputGroup inputLeft;
	InputGroup inputGrap;
	InputGroup inputBack;

	std::vector<int> dx;
	std::vector<int> dy;

	bool mIsGrap;
	bool mIsExpand;
};

