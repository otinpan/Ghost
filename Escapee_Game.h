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

	void SetIsLighted(bool isLighted) { mIsLighted = isLighted; }
	bool GetIsLighted() { return mIsLighted; }

	void UpdatePlayerHeartbeat(float deltaTime)override;

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


	//Item
	bool mIsItemAvailable;
	float mItemInavailableLimitTime;
	float mItemInavailableTime;

	//Flashlight
	void UpdateFlashlight_Game(float deltaTime);
	void UpdateIntersectGhost_Game(float deltaTime);
	void UpdateIntersectEscapee_Game(float deltaTime);
	bool mIsLighted;
	float mLightedTime;
	float mLightedLimitTime;

	void UpdateItemAvailable(float deltaTime);
	void UpdateUnAlive(float deltaTime);


	//intersect
	Line LineL;
	Line LineR;
	Line LineU;
	Line LineD;
	Vec2 mPos;
};
