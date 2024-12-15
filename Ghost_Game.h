#pragma once
#include"Player.h"

class Ghost_Game :public Player{
public:
	Ghost_Game(Vec2 pos,float speed);
	~Ghost_Game();

	void InitializePlayer_Game(class Game* game)override;

	void UpdatePlayer_Game(float deltaTime)override;

	void SetIsLighted(bool isLighted) { mIsLighted = isLighted; }
	bool GetIsLighted() { return mIsLighted; }
	void SetStopTime(float stopTime) { mStopTime = stopTime; }
	float GetStopTime() { return mStopTime; }
	void SetStopLimitTime(float stopLimitTime) { StopLimitTime = stopLimitTime; }
	float GetStopLimitTime() { return StopLimitTime; }

	class GhostClone_Game* &GetGhostClone() { return mGhostClone; }

private:
	class InputComponent_Keyboard* ic;
	class GhostClone_Game* mGhostClone;

	InputGroup inputUp;
	InputGroup inputDown;
	InputGroup inputRight;
	InputGroup inputLeft;
	InputGroup inputMakeGhost;

	float StandardSpeed;

	bool mCanMakeClone;
	float mMakeCloneTime;
	float MakeCloneCoolTime;
	bool mIsClone;
	float mCloneTime;
	float CloneLimitTime;

	//Flashlight
	bool mIsLighted;

	//Stop
	bool mIsStop;
	void UpdateStop_Game(float deltaTime);
	float mStopTime;
	float StopLimitTime;

	void UpdateClone_Game(float deltaTime);
};
