#pragma once
#include"Actor.h"

class Ghost_Game :public Actor{
public:
	Ghost_Game(Vec2 pos,float speed);
	~Ghost_Game();

	void InitializeActor_Game(class Game* game)override;

	void UpdateActor_Game(float deltaTime)override;

private:
	
};
