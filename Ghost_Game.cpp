#include"Ghost_Game.h"
#include"InputComponent_Keyboard.h"
#include"GhostClone_Game.h"
#include"Stage.h"
#include"StageObject.h"

Ghost_Game::Ghost_Game(Vec2 pos, float speed)
	:Player(pos, speed)
	, ic(nullptr)
	, MakeCloneCoolTime(30.0f)
	, mMakeCloneTime(0.0f)
	, mCanMakeClone(true)
	, mIsClone(false)
	, mCloneTime(0.0f)
	, CloneLimitTime(7.0f)
	, mIsInvincible(false)
	, mInvincibleTime(0.0f)
	, mCanCapture(true)
	, mCanCaptureTime(0.0f)
	, mDrawAccumulator(0.0f)
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
	inputMakeGhost = KeyQ;
	inputDecision = KeyEnter;
	inputPause = KeyO;
	inputBack = KeyDelete;

	ic = new InputComponent_Keyboard(this);
	ic->SetUpKey(inputUp);
	ic->SetDownKey(inputDown);
	ic->SetRightKey(inputRight);
	ic->SetLeftKey(inputLeft);
	ic->SetMaxXSpeed(GetSpeed());
	ic->SetMaxYSpeed(GetSpeed());
}


void Ghost_Game::UpdatePlayer_Game(float deltaTime) {
	// pause
	if (inputPause.pressed()) {
		if (!(GetGame()->GetIsPaused())) {
			GetGame()->SetIsPaused(true);
			SetPauseInputGroup();
		}
	}
	//Stop
	UpdateStop_Game(deltaTime);
	// 無敵
	UpdateInvincible(deltaTime);
	// 描画
	UpdateIsDraw(deltaTime);
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



// 照らされているとき
void Ghost_Game::UpdateStop_Game(float deltaTime) {

	if (mIsInvincible) {
		mIsStop = false;
		return;
	}

	// 照らされたらスタン
	if (GetIsLighted()) {
		// 一定時間照らされると無敵状態
		if (mStoppingTime >= 2.0f) {
			SetInvincible();
		}
		else {
			mStoppingTime += deltaTime;
			mIsStop = true;
		}
	}
	else {
		if (mIsStop) {
			SetInvincible();
		}
	}

	// 一度照らされただけでも照らされ続ける、といったことをなくす
	SetIsLighted(false);

}

void Ghost_Game::SetPauseInputGroup() {
	GetGame()->SetInputUp(inputUp);
	GetGame()->SetInputDown(inputDown);
	GetGame()->SetInputBack(inputBack);
	GetGame()->SetInputPause(inputPause);
	GetGame()->SetInputDecision(inputDecision);
}

void Ghost_Game::SetInvincible() {
	mIsInvincible = true;
	mInvincibleTime = 0.0f;
	mIsStop = false;
	SetIsLighted(false);
	mStoppingTime = 0.0f;
}

// 一定時間連続して止まる → 無敵状態になる
// 無限に止められてしまうことを防ぐ
void Ghost_Game::UpdateInvincible(float deltaTime) {
	// 無敵状態の時間カウント
	if (mIsInvincible) {
		mCanCapture = false;
		if (mInvincibleTime < 2.0f) {
			mInvincibleTime += deltaTime;
		}
		else {
			mIsInvincible = false;
			mInvincibleTime = 0.0f;
		}
	}
	// escapeeを捉えられない時間のカウント
	if (!mCanCapture) {
		if (mCanCaptureTime < 2.5f) {
			mCanCaptureTime += deltaTime;
		}
		else {
			mCanCaptureTime = 0.0f;
			mCanCapture = true;
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


// 無敵状態の時点滅して描画
void Ghost_Game::UpdateIsDraw(float deltaTime) {
	if (mIsInvincible) {
		if (mDrawAccumulator < 0.2f) {
			GetCircleComponent()->SetIsDraw(true);
			mDrawAccumulator += deltaTime;
		}
		else if (mDrawAccumulator < 0.4f) {
			GetCircleComponent()->SetIsDraw(false);
			mDrawAccumulator += deltaTime;
		}
		else {
			mDrawAccumulator = 0.0f;
		}
	}
	else {
		GetCircleComponent()->SetIsDraw(true);
	}
}
