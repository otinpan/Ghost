#include"Ghost_Game.h"
#include"InputComponent_Keyboard.h"
#include"GhostClone_Game.h"
#include"Stage.h"
#include"StageObject.h"

Ghost_Game::Ghost_Game(Vec2 pos,float speed)
	:Player(pos,speed)
	,ic(nullptr)
	,MakeCloneCoolTime(30.0f)
	,mMakeCloneTime(0.0f)
	,mCanMakeClone(true)
	,mIsClone(false)
	,mCloneTime(0.0f)
	,CloneLimitTime(7.0f)
	,StopLimitTime(1.0f)
	,mStopTime(5.0f)
{
	SetPosition(pos);
	SetSpeed(GetStandardSpeed() + speed / 100.0f * GetStandardSpeed());
	SetSpeed(0.3f);
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
	//Stop
	UpdateStop_Game(deltaTime);
	//Position
	if (mIsStop)ic->SetIsMove(false);
	else ic->SetIsMove(true);
	UpdatePos_Game(deltaTime);
	//Clone
	UpdateClone_Game(deltaTime);
}

void Ghost_Game::UpdateClone_Game(float deltaTime) {
	if (mCanMakeClone) {
		if (inputMakeGhost.down()) {
			mMakeCloneTime = 0.0f;
			mCanMakeClone = false;
			mIsClone = true;
			mCloneTime = 0.0f;
			mGhostClone = new GhostClone_Game(GetPosition(), GetSpeedMagnification());
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
			mGhostClone = 0;
		}
	}
}

void Ghost_Game::UpdateStop_Game(float deltaTime) {
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

void Ghost_Game::UpdatePlayerPos_Game(float deltaTime) {
	mPos = GetPosition();

	if (!GetAttribute() == Attribute::GhostClone) {
		for (auto& row : GetGame()->GetStage()->GetStageObjects()) {
			for (auto& stageObject : row) {
				if (stageObject == 0)continue;
				if (stageObject->GetAttribute() == StageObject::Attribute::Patrol) {
					if (!stageObject->GetIsTurn())continue;
				}
				if (!IsIntersect_SC(stageObject->GetSquareComponent(), GetCircleComponent()))continue;
				//Objectとの当たり判定
				if (GetCircleComponent()->GetCircle().intersects(stageObject->GetLineL()))
					mPos.x = stageObject->GetObjectLeft() - GetPlayerRadius() - 0.008; //Playerが左
				if (GetCircleComponent()->GetCircle().intersects(stageObject->GetLineR()))
					mPos.x = stageObject->GetObjectRight() + GetPlayerRadius() + 0.008; //Playerが右
				if (GetCircleComponent()->GetCircle().intersects(stageObject->GetLineD()))
					mPos.y = stageObject->GetObjectDown() - GetPlayerRadius() - 0.008; //Playerが下
				if (GetCircleComponent()->GetCircle().intersects(stageObject->GetLineU()))
					mPos.y = stageObject->GetObjectUp() + GetPlayerRadius() + 0.008; //Playerが上
			}

		}
	}

	SetPosition(mPos);
	GetCircleComponent()->SetCenter(mPos);
}
