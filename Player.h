#pragma once
#include"Actor.h"
#include"CreateStage.h"

class Player :public Actor {
public:
	Player(Vec2 pos);
	~Player();

	void InitializeActor_CreateStage(class CreateStage* createStage)override;
	virtual void InitializePlayer_CreateStage(class CreateStage* createStage);

	void UpdateActor_CreateStage(float deltaTime)override;
	virtual void UpdatePlayer_CreateStage(float deltaTime);
	void ActorInput(std::vector<Input> keyState)override;

private:
	class CircleComponent* cc;

	bool mIsGripen;
	float mRectWidth;
	float mRectHeight;
};
