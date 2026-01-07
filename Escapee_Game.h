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



	void SetIsAlive_Game(bool isAlive,Game* game) override;


	class Flashlight* &GetFlashlight() { return mFlashlight; }

	// 鼓動の更新
	void UpdateHeartbeat(float deltaTime);

	float GetHeartbeatLimitTime() { return HeartbeatLimitTime; }
	void SetHeartbeatLimitTime(float heartbeatLimitTime) { HeartbeatLimitTime = heartbeatLimitTime; }


private:
	class Flashlight* mFlashlight;
	class InputComponent_Keyboard* ic;


	// Pause
	void SetPauseInputGroup();

	// 鼓動の範囲
	class CircleComponent* mHeartLargeCC;
	class CircleComponent* mHeartMidCC;
	class CircleComponent* mHeartSmallCC;

	// 鼓動
	float mHeartbeatTime;
	float HeartbeatLimitTime;
	float mHeartLastingTime;
	bool mIsHeartLasting;
	class CircleComponent* mHeartDrawCC;

	//Flashlight
	bool mIsLightOn;
	float mBattery;

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


	void UpdateItemAvailable(float deltaTime);
	void UpdateUnAlive(float deltaTime);


	//intersect
	Line LineL;
	Line LineR;
	Line LineU;
	Line LineD;
	Vec2 mPos;
};
