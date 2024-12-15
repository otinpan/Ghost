#pragma once
#include"Player.h"

class Escapee_Game :public Player {
public:
	Escapee_Game(Vec2 pos,float speed,int num);
	~Escapee_Game();

	void InitializePlayer_Game(class Game* game)override;
	void UpdatePlayer_Game(float deltaTime)override;


	class Flashlight* &GetFlashlight() { return mFlashlight; }

private:
	class Flashlight* mFlashlight;

	//Flashlight
	bool mIsLightOn;
	float mBattery;
	InputGroup inputFlashlight;

	bool mIsAlive;

	void UpdateFlashlight_Game(float deltaTime);
	void UpdateIntersectGhost_Game(float deltaTime);
};
