#pragma once
#include"Player.h"

class Ghost_Game :public Player{
public:
	Ghost_Game(Vec2 pos,float speed);
	~Ghost_Game();

	void InitializePlayer_Game(class Game* game)override;

	void UpdatePlayer_Game(float deltaTime)override;


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
};
