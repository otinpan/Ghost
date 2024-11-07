#pragma once
#include"Player.h"

class Ghost :public Player {
public:
	Ghost(Vec2 pos);
	~Ghost();

	void InitializePlayer_CreateStage(CreateStage* createStage)override;
	void UpdatePlayer_CreateStage(float deltaTime)override;

private:
};
