#pragma once
#include"Actor.h"

class Escapee_Game :public Actor {
public:
	Escapee_Game(Vec2 pos,float speed);
	~Escapee_Game();

	void InitializeActor_Game(class Game* game)override;
	void UpdateActor_Game(float deltaTime)override;

private:
};
