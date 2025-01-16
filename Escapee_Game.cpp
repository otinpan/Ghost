#include"Escapee_Game.h"
#include"Flashlight.h"
#include"TriangleComponent.h"
#include"Game.h"
#include"Ghost_Game.h"
#include"GhostClone_Game.h"
#include"Stage.h"
#include"StageObject.h"
#include"InputComponent_Keyboard.h"

Escapee_Game::Escapee_Game(Vec2 pos, float speed, int num)
	:Player(pos, speed)
	, mFlashlight(nullptr)
	,mBattery(100.0f)
	,mIsAlive(true)
	,mIsItemAvailable(true)
	,mItemInavailableTime(0.0f)
	,mItemInavailableLimitTime(0.5f)
{
	
	SetPosition(pos);
	SetSpeed(GetStandardSpeed() + speed / 100.0f * GetStandardSpeed());
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
	inputUp = KeyW;
	inputDown = KeyS;
	inputLeft = KeyA;
	inputRight = KeyD;

	if (GetAttribute() == Attribute::Escapee1) {
		ic = new InputComponent_Keyboard(this);
		ic->SetUpKey(inputUp);
		ic->SetDownKey(inputDown);
		ic->SetRightKey(inputRight);
		ic->SetLeftKey(inputLeft);
		ic->SetMaxXSpeed(GetSpeed());
		ic->SetMaxYSpeed(GetSpeed());
	}
}

void Escapee_Game::UpdatePlayer_Game(float deltaTime) {
	mFlashlight->Update_Game(deltaTime);
	UpdateItemAvailable(deltaTime);
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


void Escapee_Game::UpdatePlayerPos_Game(float deltaTime) {
	mPos = GetPosition();
	for (auto& row : GetGame()->GetStage()->GetStageObjects()) {
		for (auto& stageObject : row) {
			if (stageObject == 0)continue;
			if (!IsIntersect_SC(stageObject->GetSquareComponent(), GetCircleComponent()))continue;
			switch (stageObject->GetAttribute()) {
			case StageObject::Attribute::Door:
				if (mIsKey) {
					mIsKey = false;
					GetGame()->GetStage()->DeleteStageObject(stageObject->GetIteration().first,
					stageObject->GetIteration().second);
					return;
				}
				break;
			case StageObject::Attribute::Patrol :
				if (!stageObject->GetIsTurn())continue;
				break;
			case StageObject::Attribute::Battery:
				if (!mIsItemAvailable)break;
				switch (stageObject->GetBatterySize()) {
				case StageObject::BatterySize::Zero:
					break;
				case StageObject::BatterySize::Small:
					mBattery += 100.0f / 3.0f;
					break;
				case StageObject::BatterySize::Mid:
					mBattery += 100.0f / 3.0f * 2.0f;
					break;
				case StageObject::BatterySize::Big:
					mBattery += 100.0f;
					break;
				}
				mBattery = max(100.0f, mBattery);
				GetGame()->GetStage()->DeleteStageObject(stageObject->GetIteration().first,
				stageObject->GetIteration().second);
				return;
				break;
			case StageObject::Attribute::Key:
				if (!mIsItemAvailable)break;
				mIsKey = true;
				GetGame()->GetStage()->DeleteStageObject(stageObject->GetIteration().first,
				stageObject->GetIteration().second);
				return;
				break;
			case StageObject::Attribute::TreasureChest:
				if (!mIsItemAvailable)break;
				if (mIsKey) {
					mIsKey = false;
					mTreasure = stageObject->GetTreasure();
					mBatterySize = stageObject->GetBatterySize();
					mIteration = stageObject->GetIteration();
					GetGame()->GetStage()->DeleteStageObject(mIteration.first,
				    mIteration.second);
					SetIsItemAvailable(false);
					switch (mTreasure) {
					case StageObject::Treasure::TreasureKey:
						GetGame()->GetStage()->SetNewStageObject_Attribute
						(mIteration.first, mIteration.second,StageObject::Attribute::Key);
						break;
					case StageObject::Treasure::TreasureBattery:
						GetGame()->GetStage()->SetNewStageObject_Attribute
						(mIteration.first, mIteration.second, StageObject::Attribute::Battery);
						GetGame()->GetStage()->GetStageObjects()[mIteration.first][mIteration.second]
							->SetBatterySize(mBatterySize);
						break;
					}
					return;
				}
				break;
			case StageObject::Attribute::Brock:
				break;
			}

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
	

	SetPosition(mPos);
	GetCircleComponent()->SetCenter(mPos);
}


void Escapee_Game::UpdateItemAvailable(float deltaTime){
	if (mIsItemAvailable)return;
	else {
		if (mItemInavailableTime < mItemInavailableLimitTime) {
			mItemInavailableTime += deltaTime;
		}
		else {
			mItemInavailableTime = 0.0f;
			mIsItemAvailable = true;
		}
	}
	return;
}
