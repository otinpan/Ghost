#pragma once
#include"Player.h"

class Escapee_Game :public Player {
public:
	Escapee_Game(Vec2 pos,float speed,int num);
	~Escapee_Game();

	void InitializePlayer_Game(class Game* game)override;
	void UpdatePlayer_Game(float deltaTime)override;

	class Flashlight* GetFlashlight() { return mFlashlight; }

private:
	class CircleComponent* cc;
	class Flashlight* mFlashlight;
};
