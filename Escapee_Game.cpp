#include"Escapee_Game.h"
#include"Flashlight.h"
#include"TriangleComponent.h"
#include"Game.h"
#include"Ghost_Game.h"
#include"GhostClone_Game.h"

Escapee_Game::Escapee_Game(Vec2 pos, float speed, int num)
	:Player(pos, speed)
	, mFlashlight(nullptr)
	,mBattery(100.0f)
	,mIsAlive(true)
{
	
	SetPosition(pos);
	SetSpeed(speed);
	switch (num) {
	case 1:
		SetAttribute(Attribute::Escapee1);
		break;
	case 2:
		SetAttribute(Attribute::Escapee2);
		break;
	case 3:
		SetAttribute(Attribute::Escapee3);
		break;
	}
	SetRotation(3.1415 / 2.0f);
}

Escapee_Game::~Escapee_Game() {

}

void Escapee_Game::InitializePlayer_Game(class Game* game) {
	InitializeActor_Game(game);
	mFlashlight = new Flashlight(this);
	mFlashlight->Initialize_Game();
	inputFlashlight = Key7;
}

void Escapee_Game::UpdatePlayer_Game(float deltaTime) {
	mFlashlight->Update_Game(deltaTime);
	//Position
	UpdatePos_Game(deltaTime);
	//Flashlight Battery
	UpdateFlashlight_Game(deltaTime);
	//intersect
	UpdateIntersectGhost_Game(deltaTime);
	

}

void Escapee_Game::UpdateFlashlight_Game(float deltaTime) {
	if (inputFlashlight.pressed()) {
		if (mBattery > 0.0) {
			mIsLightOn = true;
		}
		else {
			mIsLightOn = false;
		}
	}
	else {
		mIsLightOn = false;
	}


	if (mIsLightOn) {
		mBattery -= deltaTime * 60.0f / 5.0f;
	}

	mBattery =std:: max(0.0f, mBattery);

	mFlashlight->SetIsLightOn(mIsLightOn);
}

void Escapee_Game::UpdateIntersectGhost_Game(float deltaTime) {
	//Ghostが照らされているとき
	GetGame()->GetGhost()->SetIsLighted(false);
	if (GetGame()->GetGhost()->GetGhostClone()) {
		GetGame()->GetGhost()->GetGhostClone()->SetIsLighted(false);
	}
	if (mIsLightOn) {
		if (IsIntersect_TC(mFlashlight->GetTriagleComponent()
			, GetGame()->GetGhost()->GetCircleComponent())) {
			GetGame()->GetGhost()->SetIsLighted(true);
			GetGame()->GetGhost()->SetStopTime(0.0f);
		}
		
		if (GetGame()->GetGhost()->GetGhostClone() && IsIntersect_TC(mFlashlight->GetTriagleComponent()
			, GetGame()->GetGhost()->GetGhostClone()->GetCircleComponent())) {
			GetGame()->GetGhost()->GetGhostClone()->SetIsLighted(true);
			GetGame()->GetGhost()->GetGhostClone()->SetStopTime(0.0f);
		}
	}


	if (IsIntersect_CC(GetGame()->GetGhost()->GetCircleComponent(), GetCircleComponent())) {
		mIsAlive = false;
	}
	if (GetGame()->GetGhost()->GetGhostClone() 
		&& IsIntersect_CC( GetCircleComponent(), GetGame()->GetGhost()->GetGhostClone()->GetCircleComponent())) {
		mIsAlive = false;
	}
}


