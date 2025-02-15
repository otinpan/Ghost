#pragma once
#include"Player.h"

class Ghost_Game :public Player{
public:
	Ghost_Game(Vec2 pos,float speed);
	~Ghost_Game();

	void InitializePlayer_Game(class Game* game)override;

	void UpdatePlayer_Game(float deltaTime)override;

	void UpdatePlayerPos_Game(float deltaTime)override;

	void SetStopTime(float stopTime) { mStopTime = stopTime; }
	float GetStopTime() { return mStopTime; }
	void SetStopLimitTime(float stopLimitTime) { StopLimitTime = stopLimitTime; }
	float GetStopLimitTime() { return StopLimitTime; }

	void UpdatePlayerHeartbeat(float deltaTime)override;

	class GhostClone_Game* &GetGhostClone() { return mGhostClone; }

private:
	class InputComponent_Keyboard* ic;
	class GhostClone_Game* mGhostClone;

	InputGroup inputUp;
	InputGroup inputDown;
	InputGroup inputRight;
	InputGroup inputLeft;
	InputGroup inputMakeGhost;

	bool mCanMakeClone;
	float mMakeCloneTime;
	float MakeCloneCoolTime;
	bool mIsClone;
	float mCloneTime;
	float CloneLimitTime;

	//Flashlight

	//Stop
	bool mIsStop;
	void UpdateStop_Game(float deltaTime);
	float mStopTime;
	float StopLimitTime;

	//pos
	Vec2 mPos;

	void UpdateClone_Game(float deltaTime);
};
