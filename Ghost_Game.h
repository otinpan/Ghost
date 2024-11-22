#pragma once
#include"Player.h"

class Ghost_Game :public Player{
public:
	Ghost_Game(Vec2 pos,float speed);
	~Ghost_Game();

	void InitializePlayer_Game(class Game* game)override;

	void UpdatePlayer_Game(float deltaTime)override;

private:
	CircleComponent* cc;

};
