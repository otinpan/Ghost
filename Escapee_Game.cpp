#include"Escapee_Game.h"
#include"Flashlight.h"
#include"TriangleComponent.h"
#include"Game.h"
#include"Ghost_Game.h"
#include"GhostClone_Game.h"
#include"Stage.h"
#include"StageObject.h"
#include"InputComponent_Keyboard.h"
#include"InputComponent_JoyCon.h"

Escapee_Game::Escapee_Game(Vec2 pos, float speed, int num,Controller::ControllerType controller)
	:Player(pos, speed,controller)
	, mFlashlight(nullptr)
	, mBattery(100.0f)
	, mIsItemAvailable(true)
	, mItemInavailableTime(0.0f)
	, mItemInavailableLimitTime(0.0f)
	, mHeartLargeCC(nullptr)
	, mHeartMidCC(nullptr)
	, mHeartSmallCC(nullptr)
	, mHeartbeatTime(0.0f)
	, HeartbeatLimitTime(1.5f)
	, mHeartLastingTime(0.0f)
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



	float mRadius = GetRadius();
	mHeartLargeCC = new CircleComponent(this, 170, DrawingComponent::DrawingState::BACK);
	mHeartLargeCC->InitializeDrawing_Game();
	mHeartLargeCC->SetCenter(GetPosition());
	mHeartLargeCC->SetRadius(mRadius * 30.0f);
	mHeartLargeCC->SetIsDraw(false);
	mHeartMidCC = new CircleComponent(this, 170, DrawingComponent::DrawingState::BACK);
	mHeartMidCC->InitializeDrawing_Game();
	mHeartMidCC->SetCenter(GetPosition());
	mHeartMidCC->SetRadius(mRadius * 20.0f);
	mHeartMidCC->SetIsDraw(false);
	mHeartSmallCC = new CircleComponent(this, 170, DrawingComponent::DrawingState::BACK);
	mHeartSmallCC->InitializeDrawing_Game();
	mHeartSmallCC->SetCenter(GetPosition());
	mHeartSmallCC->SetRadius(mRadius * 10.0f);
	mHeartSmallCC->SetIsDraw(false);

	mHeartDrawCC = new CircleComponent(this, 100, DrawingComponent::DrawingState::UNAFFECTED);
	mHeartDrawCC->InitializeDrawing_Game();
	mHeartDrawCC->SetCenter(GetPosition());
	mHeartDrawCC->SetRadius(mRadius * 1.5f);
	mHeartDrawCC->SetIsDraw(false);
	mHeartDrawCC->SetColor(ColorF(1.0f, (float)102 / 255.0f, 1.0f));


}

void Escapee_Game::UpdatePlayer_Game(float deltaTime) {
	mFlashlight->Update_Game(deltaTime);

	// pause
	if (GetInputComponent_JoyCon() != nullptr && GetInputComponent_JoyCon()->GetInputPlus().down()) {
		if (!(GetGame()->GetIsPaused())) {
			GetGame()->SetIsPaused(true);
			SetPauseInputGroup();
		}
	}
	if (GetInputComponent_Keyboard() != nullptr && GetInputComponent_Keyboard()->GetInputPlus().down()) {
		if (!(GetGame()->GetIsPaused())) {
			GetGame()->SetIsPaused(true);
			SetPauseInputGroup();
		}
	}

	if (!GetIsAlive()) {
		mFlashlight->SetIsLightOn(false);
		UpdateUnAlive(deltaTime);
		return;
	}
	UpdateItemAvailable(deltaTime);
	//heartbeat
	UpdateHeartbeat(deltaTime);
	//Position
	UpdatePos_Game(deltaTime);
	//Flashlight Battery
	UpdateFlashlight_Game(deltaTime);
	//intersect
	UpdateIntersectGhost_Game(deltaTime);
	UpdateIntersectEscapee_Game(deltaTime);

	mHeartLargeCC->SetCenter(GetPosition());
	mHeartMidCC->SetCenter(GetPosition());
	mHeartSmallCC->SetCenter(GetPosition());
	mHeartDrawCC->SetCenter(GetPosition());

}

void Escapee_Game::UpdateFlashlight_Game(float deltaTime) {
	if (GetInputComponent_Keyboard() != nullptr) {
		if (GetInputComponent_Keyboard()->GetInputR().pressed()) {
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
	}
	if (GetInputComponent_JoyCon() != nullptr) {
		if (GetInputComponent_JoyCon()->GetInputR().pressed()) {
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
	}


	if (mIsLightOn) {
		//mBattery -= deltaTime * 60.0f / 6.0f;
	}

	mBattery =std:: max(0.0f, mBattery);
	mBattery = std::min(100.0f, mBattery);

	if (mBattery < 100.0f / 3.0f)mFlashlight->SetLightSize(Flashlight::LightSize::LightSmall);
	else if (mBattery < 100.0f * 2.0f / 3.0f)mFlashlight->SetLightSize(Flashlight::LightSize::LightMid);
	else mFlashlight->SetLightSize(Flashlight::LightSize::LightLarge);

	mFlashlight->SetIsLightOn(mIsLightOn);
}

void Escapee_Game::UpdateIntersectGhost_Game(float deltaTime) {

	//Ghostが照らされているとき
	if (mIsLightOn) {
		// Ghostが無敵状態でなく、ライトがGhostと交差しているとき
		// Ghostで初期化
		if (IsIntersect_TC(mFlashlight->GetTriangleComponent()
			, GetGame()->GetGhost()->GetCircleComponent())) {
			GetGame()->GetGhost()->SetIsLighted(true);
		}
		
		if (GetGame()->GetGhost()->GetGhostClone() && IsIntersect_TC(mFlashlight->GetTriangleComponent()
			, GetGame()->GetGhost()->GetGhostClone()->GetCircleComponent())) {
			GetGame()->GetGhost()->GetGhostClone()->SetIsLighted(true);
			GetGame()->GetGhost()->GetGhostClone()->SetStopTime(0.0f);
		}
	}

	
	if (IsIntersect_CC(GetGame()->GetGhost()->GetCircleComponent(), GetCircleComponent())
		&&GetGame()->GetGhost()->GetCanCapture()) {
		SetIsAlive_Game(false,GetGame());
		GetGame()->SetHitstop(1.0f);
	}
	if (GetGame()->GetGhost()->GetGhostClone()
		&& IsIntersect_CC(GetCircleComponent(), GetGame()->GetGhost()->GetGhostClone()->GetCircleComponent())) {
		SetIsAlive_Game(false,GetGame());
		GetGame()->SetHitstop(1.0f);
	}
	
	
}

// UnAiveなEscapeeを照らす
void Escapee_Game::UpdateIntersectEscapee_Game(float deltaTime) {
	if (!mIsLightOn)return;
	for (auto& player : GetGame()->GetPlayers()) {
		if (player == this || player->GetAttribute() == Player::Attribute::Ghost
			|| player->GetAttribute() == Player::Attribute::GhostClone) {
			continue;
		}
		if (player->GetIsAlive())continue;
		if (IsIntersect_TC(mFlashlight->GetTriangleComponent(), player->GetCircleComponent())) {
			player->SetIsLighted(true); //player側で最後にfalseにする
		}
	}
	
}

void Escapee_Game::SetPauseInputGroup() {
	GetGame()->SetInputUp(KeyW);
	GetGame()->SetInputDown(KeyS);
	GetGame()->SetInputBack(KeyBackspace);
	if (GetInputComponent_JoyCon() != nullptr) {
		GetGame()->SetInputPause(GetInputComponent_JoyCon()->GetInputPlus());
	}
	else if (GetInputComponent_Keyboard() != nullptr) {
		GetGame()->SetInputPause(GetInputComponent_Keyboard()->GetInputPlus());
	}
	GetGame()->SetInputDecision(KeySpace);
}

// 鼓動の更新
void Escapee_Game::UpdateHeartbeat(float deltaTime) {
	if (IsIntersect_CC(mHeartSmallCC, GetGame()->GetGhost()->GetCircleComponent())) {
		HeartbeatLimitTime = 0.4f;
	}
	else if (IsIntersect_CC(mHeartMidCC, GetGame()->GetGhost()->GetCircleComponent())) {
		HeartbeatLimitTime = 0.7f;
		
	}
	else if (IsIntersect_CC(mHeartLargeCC, GetGame()->GetGhost()->GetCircleComponent())) {
		
		HeartbeatLimitTime = 1.3f;
	}
	else {
		HeartbeatLimitTime = 2.0f;
	}

	if (mIsHeartLasting) {
		if (mHeartLastingTime < 0.2f) {
			mHeartLastingTime += deltaTime;
		}
		else {
			mHeartLastingTime = 0.0f;
			mIsHeartLasting = false;
		}
	}
	else {
		if (mHeartbeatTime > HeartbeatLimitTime) {
			mHeartbeatTime = 0.0f;
			mIsHeartLasting = true;
			mHeartDrawCC->SetIsDraw(true);
		}
		else {
			mHeartbeatTime += deltaTime;
			mHeartDrawCC->SetIsDraw(false);
		}
	}

}

void Escapee_Game::UpdateUnAlive(float deltaTime) {
	if (GetIsAlive())return;

	// 生還
	if (GetLightedTime() > 5.0f) {
		SetIsAlive_Game(true,GetGame());
		SetLightedTime(0.0f);
		return;
	}
	else {
		if (GetIsLighted()) {
			SetLightedTime(GetLightedTime() + deltaTime);
		}
	}
	//1度照らされただけでも照らされ続ける、といったことをなくす
	SetIsLighted(false);
}


void Escapee_Game::UpdatePlayerPos_Game(float deltaTime) {
	mPos = GetPosition();
	
	for (auto& row : GetGame()->GetStage()->GetStageObjects()) {
		for (auto& stageObject : row) {
			if (stageObject == 0)continue;
			if (!IsIntersect_SC(stageObject->GetSquareComponent(), GetCircleComponent()))continue;
			switch (stageObject->GetAttribute()) {
			case StageObject::Attribute::Door:
				// 鍵を持っているならドアを開く
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
				if (!mIsItemAvailable) break;
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
				mBattery = std::max(100.0f, mBattery);
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
				// 鍵を持っているなら宝箱を開く
				if (mIsKey) {
					mIsKey = false;
					mTreasure = stageObject->GetTreasure();
					mBatterySize = stageObject->GetBatterySize();
					mIteration = stageObject->GetIteration();
					GetGame()->GetStage()->DeleteStageObject(mIteration.first,
				    mIteration.second);
					mIsItemAvailable=false;
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

void Escapee_Game::SetIsAlive_Game(bool isAlive,Game* game) {
	if (isAlive) {
		mHeartDrawCC->SetIsDraw(true);
	}
	else {
		mHeartDrawCC->SetIsDraw(false);
	}
	Player::SetIsAlive_Game(isAlive,game);
}
