#include"GhostClone_Game.h"
#include"InputComponent_Keyboard.h"

GhostClone_Game::GhostClone_Game(Vec2 pos, float speed,Controller::ControllerType controller)
	:Player(pos, speed,controller)
	, ic(nullptr)
	, StandardSpeed(0.3f)
	, StopLimitTime(1.0f)
	, mStopTime(5.0f)
{
	SetAttribute(Player::Attribute::GhostClone);
	SetPosition(pos);
	SetSpeed(StandardSpeed+speed/100.0f*StandardSpeed);
}

GhostClone_Game::~GhostClone_Game() {

}

void GhostClone_Game::InitializePlayer_Game(class Game* game) {
	InitializeActor_Game(game);

}

void GhostClone_Game::UpdatePlayer_Game(float deltaTime) {
	//Stop
	UpdateStop_Game(deltaTime);
	//Position
	if (mIsStop)ic->SetIsMove(false);
	else ic->SetIsMove(true);
	UpdatePos_Game(deltaTime);
}

void GhostClone_Game::UpdateStop_Game(float deltaTime) {
	if (mIsLighted) {
		mIsStop = true;
	}
	else {
		if (mStopTime < StopLimitTime) {
			mStopTime += deltaTime;
			mIsStop = true;
		}
		else {
			mIsStop = false;
		}
	}
}

void GhostClone_Game::UpdatePlayerPos_Game(float deltaTime) {

}
