#include"Ghost_Game.h"
#include"InputComponent_Keyboard.h"
#include"GhostClone_Game.h"

Ghost_Game::Ghost_Game(Vec2 pos,float speed)
	:Player(pos,speed)
	,ic(nullptr)
	,StandardSpeed(0.3f)
	,MakeCloneCoolTime(30.0f)
	,mMakeCloneTime(0.0f)
	,mCanMakeClone(true)
	,mIsClone(false)
	,mCloneTime(0.0f)
	,CloneLimitTime(7.0f)
{
	SetPosition(pos);
	SetSpeed(StandardSpeed+speed/100.0f*StandardSpeed);
	SetAttribute(Player::Attribute::Ghost);
}

Ghost_Game::~Ghost_Game() {

}


void Ghost_Game::InitializePlayer_Game(class Game* game) {
	InitializeActor_Game(game);

	inputUp = KeyW;
	inputDown = KeyS;
	inputLeft = KeyA;
	inputRight = KeyD;
	inputMakeGhost = KeySpace;

	ic = new InputComponent_Keyboard(this);
	ic->SetUpKey(inputUp);
	ic->SetDownKey(inputDown);
	ic->SetRightKey(inputRight);
	ic->SetLeftKey(inputLeft);
	ic->SetMaxXSpeed(GetSpeed());
	ic->SetMaxYSpeed(GetSpeed());
}


void Ghost_Game::UpdatePlayer_Game(float deltaTime) {
	UpdatePos_Game(deltaTime);
	if (mCanMakeClone) {
		if (inputMakeGhost.down()) {
			mMakeCloneTime = 0.0f;
			mCanMakeClone = false;
			mIsClone = true;
			mCloneTime = 0.0f;
			mGhostClone = new GhostClone_Game(GetPosition(),GetSpeedMagnification());
			mGhostClone->InitializePlayer_Game(GetGame());
		}
	}
	else {
		mMakeCloneTime += deltaTime;
		if (mMakeCloneTime > MakeCloneCoolTime) {
			mCanMakeClone = true;
		}
	}

	if (mIsClone) {
		mCloneTime += deltaTime;
		if (mCloneTime > CloneLimitTime) {
			mIsClone = false;
			delete mGhostClone;
		}
	}
}
