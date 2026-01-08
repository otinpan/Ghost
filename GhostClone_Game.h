#pragma once
#include"Player.h"

class GhostClone_Game :public Player {
public:
	GhostClone_Game(Vec2 pos, float speed,Controller::ControllerType controller);
	~GhostClone_Game();

	void InitializePlayer_Game(class Game* game)override;

	void UpdatePlayer_Game(float deltaTime)override;

	void UpdatePlayerPos_Game(float deltaTime)override;

	void SetIsLighted(bool isLighted) { mIsLighted = isLighted; }
	bool GetIsLighted() { return mIsLighted; }

	void SetStopTime(float stopTime) { mStopTime = stopTime; }
	float GetStopTime() { return mStopTime; }
	void SetStopLimitTime(float stopLimitTime) { StopLimitTime = stopLimitTime; }
	float GetStopLimitTime() { return StopLimitTime; }


private:
	class InputComponent_Keyboard* ic;

	InputGroup inputUp;
	InputGroup inputDown;
	InputGroup inputRight;
	InputGroup inputLeft;

	bool mIsLighted;

	//Stop
	bool mIsStop;
	void UpdateStop_Game(float deltaTime);
	float mStopTime;
	float StopLimitTime;

	float StandardSpeed;
};
