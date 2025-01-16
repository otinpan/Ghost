#pragma once
#include"Player.h"
#include"StageObject.h"

class Escapee_Game :public Player {
public:
	Escapee_Game(Vec2 pos,float speed,int num);
	~Escapee_Game();

	void InitializePlayer_Game(class Game* game)override;
	void UpdatePlayer_Game(float deltaTime)override;

	void UpdatePlayerPos_Game(float deltaTime)override;

	void SetIsItemAvailable(bool isItemAvailable) { mIsItemAvailable = isItemAvailable; }
	bool GetIsItemAvailable() { return mIsItemAvailable; }

	class Flashlight* &GetFlashlight() { return mFlashlight; }

private:
	class Flashlight* mFlashlight;
	class InputComponent_Keyboard* ic;

	//Input
	InputGroup inputUp;
	InputGroup inputDown;
	InputGroup inputRight;
	InputGroup inputLeft;

	//Flashlight
	bool mIsLightOn;
	float mBattery;
	InputGroup inputFlashlight;

	//Key
	bool mIsKey;

	//Treasure
	StageObject::Treasure mTreasure;
	StageObject::BatterySize mBatterySize;
	std::pair<int,int> mIteration;

	bool mIsAlive;

	//Item
	bool mIsItemAvailable;
	float mItemInavailableLimitTime;
	float mItemInavailableTime;

	void UpdateFlashlight_Game(float deltaTime);
	void UpdateIntersectGhost_Game(float deltaTime);
	void UpdateItemAvailable(float deltaTime);

	//intersect
	Line LineL;
	Line LineR;
	Line LineU;
	Line LineD;
	Vec2 mPos;
};
