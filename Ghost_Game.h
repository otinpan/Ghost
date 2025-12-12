#pragma once
#include"Player.h"

class Ghost_Game :public Player{
public:
	Ghost_Game(Vec2 pos,float speed);
	~Ghost_Game();

	void InitializePlayer_Game(class Game* game)override;

	void UpdatePlayer_Game(float deltaTime)override;

	void UpdatePlayerPos_Game(float deltaTime)override;

	void SetIsInvincible(bool isInvincible) { mIsInvincible = isInvincible; }
	bool GetIsInvincible() { return mIsInvincible; }
	void SetCanCapture(bool canCapture) { mCanCapture = canCapture; }
	bool GetCanCapture() { return mCanCapture; }


	class GhostClone_Game* &GetGhostClone() { return mGhostClone; }

private:
	class InputComponent_Keyboard* ic;
	class GhostClone_Game* mGhostClone;

	InputGroup inputUp;
	InputGroup inputDown;
	InputGroup inputRight;
	InputGroup inputLeft;
	InputGroup inputMakeGhost;
	InputGroup inputDecision;
	InputGroup inputPause;
	InputGroup inputBack;

	// Pause
	void SetPauseInputGroup();

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
	void UpdateInvincible(float deltaTime);
	void SetInvincible();
	bool mIsInvincible; // 無敵かどうか
	float mInvincibleTime; // 無敵時間
	bool mCanCapture; // Escapeeを捉えられない状態
	float mCanCaptureTime; 
	float mStoppingTime; // 静止している時間*/

	// 描画
	void UpdateIsDraw(float deltaTime);
	float mDrawAccumulator;


	//pos
	Vec2 mPos;

	void UpdateClone_Game(float deltaTime);
};
