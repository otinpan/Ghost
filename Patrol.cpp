#include"Patrol.h"
#include"CreateStage.h"
#include"StageMenu.h"
#include"Hand.h"
#include"Stage.h"
#include"StageObjectLight.h"
#include"TriangleComponent.h"
#include"Ghost_Game.h"
#include"Escapee_Game.h"
#define _USE_MATH_DEFINES
#include<math.h>

Patrol::Patrol(Vec2 pos, float width, float height)
	:StageObject(pos, width, height)
	, mIsPlusLasting(false)
	, mIsMinusLasting(false)
	, mPlusTime(0.0)
	, mMinusTime(0.0)
	, mIsBarGripen(false)
	, mTurnTime(0.0f)
	, TurnLimitTime(2.0f)
{
	SetAttribute(Attribute::Patrol);
	SetIsTurn(false);
}

void Patrol::InitializeStageObject_CreateStage(class CreateStage* createStage) {
	InitializeActor_CreateStage(createStage);

	
}

void Patrol::UpdateStageObject_CreateStage(float deltaTime) {
	// 回転
	switch (GetClockwise()) {
	case 0:
		GetSpriteComponent()->SetRotation(0.0f);
		break;
	case 1:
		GetSpriteComponent()->SetRotation(-M_PI / 2.0f);
		break;
	case 2:
		GetSpriteComponent()->SetRotation(M_PI);
		break;
	case 3:
		GetSpriteComponent()->SetRotation(M_PI / 2.0f);
	}
}

Patrol::~Patrol() {

}

void Patrol::InitializeStageMenu_CreateStage() {
	mBarCenter = Vec2(
		(GetCreateStage()->GetStageMenu()->GetMenuRight() + GetCreateStage()->GetStageMenu()->GetMenuLeft()) / 2.0f,
		(GetCreateStage()->GetStageMenu()->GetMenuUp() + GetCreateStage()->GetStageMenu()->GetMenuDown()) *4.0f / 5.0f
	);
	mBarWidth = GetCreateStage()->GetStageMenu()->GetMenuWidth() * 3.0f / 4.0f;
	mBarMin = mBarCenter.x - mBarWidth / 2.0f;
	mBarMax = mBarCenter.x + mBarWidth / 2.0f;
	mBarPos = Vec2(
		mBarMin + mBarWidth * GetSpeed() / 100.0f,
		mBarCenter.y
	);

	mBarSC_CreateStage = new SquareComponent(this,200, DrawingComponent::DrawingState::UNAFFECTED);
	mBarSC_CreateStage->InitializeDrawing_CreateStage(mBarPos,
		mBarWidth / 25.0f, GetCreateStage()->GetStageMenu()->GetMenuHeight() / 20.0f);
	mBarSC_CreateStage->SetColor(ColorF(0, 0, 0));

	mTriCenter = Vec2(
		(GetCreateStage()->GetStageMenu()->GetMenuRight() + GetCreateStage()->GetStageMenu()->GetMenuLeft()) / 2.0f,
		(GetCreateStage()->GetStageMenu()->GetMenuUp() + GetCreateStage()->GetStageMenu()->GetMenuDown())*2.0f / 4.0f
	);
	mTriLength = GetCreateStage()->GetStageMenu()->GetMenuWidth() / 5.0f;
	mTriLengthFromCenter = GetCreateStage()->GetStageMenu()->GetMenuWidth() / 4.0f;

	mUpTriPos = Vec2(
		mTriCenter.x,
		mTriCenter.y + mTriLengthFromCenter
	);
	mDownTriPos = Vec2(
		mTriCenter.x,
		mTriCenter.y - mTriLengthFromCenter
	);
	mRightTriPos = Vec2(
		mTriCenter.x + mTriLengthFromCenter,
		mTriCenter.y
	);
	mLeftTriPos = Vec2(
		mTriCenter.x - mTriLengthFromCenter,
		mTriCenter.y
	);


	mUpCC = new CircleComponent(this,10, DrawingComponent::DrawingState::UNAFFECTED);
	mUpCC->InitializeDrawing_CreateStage();
	mUpCC->SetCenter(mUpTriPos);
	mUpCC->SetRadius(mTriLength);
	mUpCC->SetColor(ColorF(1.0, 1.0, 0.0, 0));
	mUpCC->SetIsDraw(false);

	mDownCC = new CircleComponent(this,10, DrawingComponent::DrawingState::UNAFFECTED);
	mDownCC->InitializeDrawing_CreateStage();
	mDownCC->SetCenter(mDownTriPos);
	mDownCC->SetRadius(mTriLength);
	mDownCC->SetColor(ColorF(1.0, 1.0, 0.0, 0));
	mDownCC->SetIsDraw(false);

	mRightCC = new CircleComponent(this,10, DrawingComponent::DrawingState::UNAFFECTED);
	mRightCC->InitializeDrawing_CreateStage();
	mRightCC->SetCenter(mRightTriPos);
	mRightCC->SetRadius(mTriLength);
	mRightCC->SetColor(ColorF(1.0, 1.0, 0.0, 0));
	mRightCC->SetIsDraw(false);

	mLeftCC = new CircleComponent(this,10, DrawingComponent::DrawingState::UNAFFECTED);
	mLeftCC->InitializeDrawing_CreateStage();
	mLeftCC->SetCenter(mLeftTriPos);
	mLeftCC->SetRadius(mTriLength);
	mLeftCC->SetColor(ColorF(1.0, 1.0, 0.0, 0));
	mRightCC->SetIsDraw(false);

	mAddCenter= Vec2(
		(GetCreateStage()->GetStageMenu()->GetMenuRight() + GetCreateStage()->GetStageMenu()->GetMenuLeft()) / 2.0f,
		(GetCreateStage()->GetStageMenu()->GetMenuUp() + GetCreateStage()->GetStageMenu()->GetMenuDown()) * 1.0f / 5.0f
	);
	mAddLengthFromCenter= GetCreateStage()->GetStageMenu()->GetMenuWidth() / 4.0f;

	mPlusPos = Vec2(
		mAddCenter.x - mAddLengthFromCenter,
		mAddCenter.y
	);
	mMinusPos = Vec2(
		mAddCenter.x + mAddLengthFromCenter,
		mAddCenter.y
	);
	mPlusHeight= GetCreateStage()->GetStageMenu()->GetMenuWidth() / 5.0f;
	mPlusWidth = mPlusHeight / 3.0f;

	mMinusWidth= GetCreateStage()->GetStageMenu()->GetMenuWidth() / 4.0f;
	mMinusHeight = mMinusWidth / 3.0f;

	mPlusCC = new CircleComponent(this,10, DrawingComponent::DrawingState::UNAFFECTED);
	mPlusCC->InitializeDrawing_CreateStage();
	mPlusCC->SetCenter(mPlusPos);
	mPlusCC->SetRadius(mTriLength);
	mPlusCC->SetColor(ColorF(1, 1, 0, 0));
	mPlusCC->SetIsDraw(false);

	mMinusCC = new CircleComponent(this, 10, DrawingComponent::DrawingState::UNAFFECTED);
	mMinusCC->InitializeDrawing_CreateStage();
	mMinusCC->SetCenter(mMinusPos);
	mMinusCC->SetRadius(mTriLength);
	mMinusCC->SetColor(ColorF(1, 1, 0, 0));
	mMinusCC->SetIsDraw(false);

	mPlusLastTime = 0.03;
	mMinusLastTime = 0.03;

	GetSpriteComponent()->SetRotation(M_PI / 2.0f);

	
}

void Patrol::UpdateStageMenu_CreateStage(float deltaTime) {
	if (!mIsBarGripen) {
		if (IsIntersect_SC(mBarSC_CreateStage, GetCreateStage()->GetHand()->GetCircleComponent())) {
			if (GetCreateStage()->GetHand()->GetInputChoose().pressed()) {
				mIsBarGripen = true;
			}
		}
	}
	else {
		if (!GetCreateStage()->GetHand()->GetInputChoose().pressed()) {
			mIsBarGripen = false;
		}
		mBarPos.x = GetCreateStage()->GetHand()->GetPosition().x;
		if (mBarPos.x < mBarMin)mBarPos.x = mBarMin;
		if (mBarPos.x > mBarMax)mBarPos.x = mBarMax;
		SetSpeed(ConvertToSpeed(mBarMin, mBarWidth, mBarPos.x));
	}
	mBarSC_CreateStage->SetCenter(mBarPos);

	if (GetCreateStage()->GetHand()->GetInputU().down()) {
		SetClockwise(0);
	}
	if (GetCreateStage()->GetHand()->GetInputR().down()) {
		SetClockwise(1);
	}
	if (GetCreateStage()->GetHand()->GetInputD().down()) {
		SetClockwise(2);
	}
	if (GetCreateStage()->GetHand()->GetInputL().down()) {
		SetClockwise(3);
	}

	if (GetCreateStage()->GetHand()->GetInputChoose().down()) {
		if (IsIntersect_CC(GetCreateStage()->GetHand()->GetCircleComponent(), mUpCC)) {
			SetClockwise(0);
		}
		if (IsIntersect_CC(GetCreateStage()->GetHand()->GetCircleComponent(), mRightCC)) {
			SetClockwise(1);
		}
		if (IsIntersect_CC(GetCreateStage()->GetHand()->GetCircleComponent(), mDownCC)) {
			SetClockwise(2);
		}
		if (IsIntersect_CC(GetCreateStage()->GetHand()->GetCircleComponent(), mLeftCC)) {
			SetClockwise(3);
		}
	}

	if (mIsPlusLasting) {
		AddDeltaTime(mIsPlusLasting, mPlusTime, mPlusLastTime, deltaTime);
	}
	else {
		if (GetCreateStage()->GetHand()->GetInputPlus().down() ||
			(IsIntersect_CC(mPlusCC, GetCreateStage()->GetHand()->GetCircleComponent()) &&
				GetCreateStage()->GetHand()->GetInputChoose().down())) {
			AddPatrolRange(true);
			mIsPlusLasting = true;
		}
	}
	if (mIsMinusLasting) {
		AddDeltaTime(mIsMinusLasting, mMinusTime, mMinusLastTime, deltaTime);
	}
	else {
		if (GetCreateStage()->GetHand()->GetInputMinus().down() ||
			(IsIntersect_CC(mMinusCC, GetCreateStage()->GetHand()->GetCircleComponent()) &&
				GetCreateStage()->GetHand()->GetInputChoose().down())) {
			AddPatrolRange(false);
			mIsMinusLasting = true;
		}
	}
	AdjustPatrolRange();


}

void Patrol::DrawStageMenu_CreateStage() {
	if (GetClockwise() != 0) {
		DrawTriangle(mUpTriPos, mTriLength, 0, ColorF(0, 0, 0));
	}
	else {
		DrawTriangle(mUpTriPos, mTriLength, 0, ColorF(1, 1, (float)102 / 255));
	}
	if (GetClockwise() != 1) {
		DrawTriangle(mRightTriPos, mTriLength, 90_deg, ColorF(0, 0, 0));
	}
	else {
		DrawTriangle(mRightTriPos, mTriLength, 90_deg, ColorF(1, 1, (float)102 / 255));
	}
	if (GetClockwise() != 2) {
		DrawTriangle(mDownTriPos, mTriLength, 180_deg, ColorF(0, 0, 0));
	}
	else {
		DrawTriangle(mDownTriPos, mTriLength, 180_deg, ColorF(1, 1, (float)102 / 255));
	}
	if (GetClockwise() != 3) {
		DrawTriangle(mLeftTriPos, mTriLength, 270_deg, ColorF(0, 0, 0));
	}
	else {
		DrawTriangle(mLeftTriPos, mTriLength, 270_deg, ColorF(1, 1, (float)102 / 255));
	}

	if (mIsPlusLasting) {
		DrawPlus(mPlusHeight, mPlusWidth, mPlusPos, 0.0, ColorF(1, 1, (float)102 / 255));
	}
	else {
		DrawPlus(mPlusHeight, mPlusWidth, mPlusPos, 0.0, ColorF(0, 0, 0));
	}

	if (mIsMinusLasting) {
		DrawRect(mMinusPos, mMinusWidth, mMinusHeight, ColorF(1, 1, (float)102 / 255));
	}
	else {
		DrawRect(mMinusPos, mMinusWidth, mMinusHeight, ColorF(0,0,0));
	}
	DrawLine(Vec2(mBarMin, mBarCenter.y), Vec2(mBarMax, mBarCenter.y), 0.002, ColorF(0, 0, 0));

	mStageMenuFont(U"Speed").draw(Arg::center(ConvertToView(Vec2(mBarCenter.x, mBarCenter.y + 0.08))), ColorF(0, 0, 0));
	mSpeedFont(Format((int)GetSpeed())).draw(Arg::center(ConvertToView(Vec2(mBarMax, mBarCenter.y + 0.08))), ColorF(0, 0, 0));
	mStageMenuFont(U"Way").draw(Arg::center(ConvertToView(Vec2(mTriCenter.x, mTriCenter.y + 0.13f))), ColorF(0, 0, 0));
	mStageMenuFont(U"Range").draw(Arg::center(ConvertToView(Vec2(mAddCenter.x, mAddCenter.y + 0.09))), ColorF(0, 0, 0));
	mStageMenuFont(Format(GetPatrolRange())).draw(Arg::center(ConvertToView(Vec2(mMinusPos.x+0.03, mAddCenter.y + 0.09))), ColorF(0, 0, 0));
}

void Patrol::ShutdownStageMenu_CreateStage() {
	if(mUpCC)delete mUpCC;
	if(mDownCC)delete mDownCC;
	if(mRightCC)delete mRightCC;
	if(mLeftCC)delete mLeftCC;
	if(mPlusCC)delete mPlusCC;
	if(mMinusCC)delete mMinusCC;
	if(mBarSC_CreateStage)delete mBarSC_CreateStage;
}

////////////////////////////////////////////////////////////////////////////////////////////////

void Patrol::InitializeStageObject_Game(class Game* game) {
	InitializeActor_Game(game);

}

void Patrol::InitializeStage_Game() {
	SetPatrolRange(GetPatrolRange() - 1);
	SetSpeed(GetStandardSpeed() + GetSpeed() / 100.0f * GetStandardSpeed());
	switch (GetClockwise()) {
	// 上方向
	case 0:
		FromPos = Vec2({ (float)GetGame()->GetStage()->GetLeft() + GetIteration().second * GetGame()->GetStage()->GetRectWidth() + GetGame()->GetStage()->GetRectWidth() / 2,
		(float)GetGame()->GetStage()->GetUp() - (GetIteration().first + 1) * GetGame()->GetStage()->GetRectHeight() + GetGame()->GetStage()->GetRectHeight() / 2 - GetHeight() / 2.0f });
		ToPos = Vec2({ (float)GetGame()->GetStage()->GetLeft() + GetIteration().second * GetGame()->GetStage()->GetRectWidth() + GetGame()->GetStage()->GetRectWidth() / 2,
		(float)GetGame()->GetStage()->GetUp() - (GetIteration().first + 1 - GetPatrolRange()) * GetGame()->GetStage()->GetRectHeight() + GetGame()->GetStage()->GetRectHeight() / 2 + GetHeight() / 2.0f });
		//Rotation
		SetRotation(M_PI / 2.0f);
		//velocity
		mVelocity = Vec2(0, GetSpeed());
		break;
	// 右方向
	case 1:
		FromPos = Vec2({ (float)GetGame()->GetStage()->GetLeft() + GetIteration().second * GetGame()->GetStage()->GetRectWidth() + GetGame()->GetStage()->GetRectWidth() / 2-GetWidth()/2.0f,
		(float)GetGame()->GetStage()->GetUp() - (GetIteration().first + 1) * GetGame()->GetStage()->GetRectHeight() + GetGame()->GetStage()->GetRectHeight() / 2  });
		ToPos = Vec2({ (float)GetGame()->GetStage()->GetLeft() + (GetIteration().second + GetPatrolRange()) * GetGame()->GetStage()->GetRectWidth() + GetGame()->GetStage()->GetRectWidth() / 2+GetWidth()/2.0f,
		(float)GetGame()->GetStage()->GetUp() - (GetIteration().first + 1) * GetGame()->GetStage()->GetRectHeight() + GetGame()->GetStage()->GetRectHeight() / 2 });
		//Rotation
		SetRotation(0.0f);
		//velocity
		mVelocity = Vec2( GetSpeed(),0);
		break;
	// 下方向
	case 2:
		FromPos = Vec2({ (float)GetGame()->GetStage()->GetLeft() + GetIteration().second * GetGame()->GetStage()->GetRectWidth() + GetGame()->GetStage()->GetRectWidth() / 2,
		(float)GetGame()->GetStage()->GetUp() - (GetIteration().first + 1) * GetGame()->GetStage()->GetRectHeight() + GetGame()->GetStage()->GetRectHeight() / 2 + GetHeight()/2.0f});
		ToPos = Vec2({ (float)GetGame()->GetStage()->GetLeft() + GetIteration().second * GetGame()->GetStage()->GetRectWidth() + GetGame()->GetStage()->GetRectWidth() / 2,
		(float)GetGame()->GetStage()->GetUp() - (GetIteration().first + 1 + GetPatrolRange()) * GetGame()->GetStage()->GetRectHeight() + GetGame()->GetStage()->GetRectHeight() / 2 -GetHeight()/2.0f});
		//Rotation
		SetRotation(M_PI*3.0f/2.0f);
		//velocity
		mVelocity = Vec2(0,-GetSpeed());
		break;
	// 左方向
	case 3:
		FromPos = Vec2({ (float)GetGame()->GetStage()->GetLeft() + GetIteration().second * GetGame()->GetStage()->GetRectWidth() + GetGame()->GetStage()->GetRectWidth() / 2+GetWidth()/2.0f,
		(float)GetGame()->GetStage()->GetUp() - (GetIteration().first + 1) * GetGame()->GetStage()->GetRectHeight() + GetGame()->GetStage()->GetRectHeight() / 2 });
		ToPos = Vec2({ (float)GetGame()->GetStage()->GetLeft() + (GetIteration().second - GetPatrolRange()) * GetGame()->GetStage()->GetRectWidth() + GetGame()->GetStage()->GetRectWidth() / 2 - GetWidth()/2.0f,
		(float)GetGame()->GetStage()->GetUp() - (GetIteration().first + 1) * GetGame()->GetStage()->GetRectHeight() + GetGame()->GetStage()->GetRectHeight() / 2 });
		//Rotation
		SetRotation(M_PI);
		//velocity
		mVelocity = Vec2(-GetSpeed(),0);
		break;
	}
	GetSpriteComponent()->SetRotation(-M_PI / 2.0f + GetRotation());
	mMoveC = new MoveComponent(this);
	mMoveC->SetXSpeed(mVelocity.x);
	mMoveC->SetYSpeed(mVelocity.y);

	mStageObjectLight = new StageObjectLight(this);
	mStageObjectLight->Initialize_Game();


	MicroRad = (float)M_PI / TurnLimitTime;



}

void Patrol::UpdateStageObject_Game(float deltaTime) {
	mStageObjectLight->Update_Game(deltaTime);
	UpdateIntersectGhost_Game(deltaTime);
	if (GetIsTurn()) {
		UpdateTurn_Game(deltaTime);
		return;
	}
	UpdatePos_Game(deltaTime);
}


void Patrol::UpdatePos_Game(float deltaTime) {
	Vec2 mPos = GetPosition();
	// stageobjectとの衝突
	for (auto& row : GetGame()->GetStage()->GetStageObjects()) {
		for (auto& stageObject : row) {
			if (stageObject == 0)continue;
			if (!IsIntersect_SS(GetSquareComponent(), stageObject->GetSquareComponent())) continue;
			if (stageObject == this)continue;
			switch (GetClockwise()) {
			case 0:
				mPos.y = stageObject->GetObjectDown() - GetHeight()/2.0f - 0.005; //Patrolが下
				mVelocity.y *= -1.0f;
				SetClockwise(2);
				std::swap(ToPos, FromPos);
				break;
			case 1:
				mPos.x = stageObject->GetObjectLeft() - GetWidth()/2.0f - 0.005; //Patrolが左
				mVelocity.x *= -1.0f;
				SetClockwise(3);
				std::swap(ToPos, FromPos);
				break;
			case 2:
				mPos.y = stageObject->GetObjectUp() + GetHeight()/2.0f + 0.005; //Patrolが上
				mVelocity.y *= -1.0f;
				SetClockwise(0);
				std::swap(ToPos, FromPos);
				break;
			case 3:
				mPos.x = stageObject->GetObjectRight() + GetWidth()/2.0f + 0.005; //Patrolが右
				mVelocity.x *= -1.0f;
				SetClockwise(1);
				std::swap(ToPos, FromPos);
				break;
			}
			SetIsTurn(true);
		}
	}


	// playerとの衝突
	for (auto& player : GetGame()->GetPlayers()) {
		if (player && IsIntersect_SC(GetSquareComponent(),player->GetCircleComponent())) {
			switch (GetClockwise()) {
			case 0:
				mVelocity.y *= -1.0f;
				SetClockwise(2);
				std::swap(ToPos, FromPos);
				break;
			case 1:
				mVelocity.x *= -1.0f;
				SetClockwise(3);
				std::swap(ToPos, FromPos);
				break;
			case 2:
				mVelocity.y *= -1.0f;
				SetClockwise(0);
				std::swap(ToPos, FromPos);
				break;
			case 3:
				mVelocity.x *= -1.0f;
				SetClockwise(1);
				std::swap(ToPos, FromPos);
				break;
			}
			SetIsTurn(true);

			Vec2 mPlayerPos = player->GetPosition();

			if (player->GetCircleComponent()->GetCircle().intersects(GetLineL()))
				mPlayerPos.x = GetObjectLeft() - player->GetPlayerRadius() - 0.008; //Playerが左
			if (player->GetCircleComponent()->GetCircle().intersects(GetLineR()))
				mPlayerPos.x = GetObjectRight() + player->GetPlayerRadius() + 0.008; //Playerが右
			if (player->GetCircleComponent()->GetCircle().intersects(GetLineD()))
				mPlayerPos.y = GetObjectDown() - player->GetPlayerRadius() - 0.008; //Playerが下
			if (player->GetCircleComponent()->GetCircle().intersects(GetLineU()))
				mPlayerPos.y = GetObjectUp() + player->GetPlayerRadius() + 0.008; //Playerが上
			player->SetPosition(mPlayerPos);
			player->GetCircleComponent()->SetCenter(mPlayerPos);
		}

	}

	// 回転
	if (GetSquareComponent()->GetRect().intersects(ToPos)) {
		switch (GetClockwise()) {
		case 0://Down to Up
			mPos.y = ToPos.y - GetHeight()/2.0f - 0.005;
			mVelocity.y *= -1.0f;
			SetClockwise(2);
			std::swap(ToPos, FromPos);
			break;
		case 1://Left to Right
			mPos.x = ToPos.x - GetWidth()/2.0f - 0.005;
			mVelocity.x *= -1.0f;
			SetClockwise(3);
			std::swap(ToPos, FromPos);
			break;
		case 2://Up to Down
			mPos.y = ToPos.y + GetHeight()/2.0f + 0.005;
			mVelocity.y *= -1.0f;
			SetClockwise(0);
			std::swap(ToPos, FromPos);
			break;
		case 3://Right to Left
			mPos.x = ToPos.x + GetWidth()/2.0f + 0.005;
			SetClockwise(1);
			mVelocity.x *= -1.0f;
			std::swap(ToPos, FromPos);
			break;
		}
		SetIsTurn(true);

	}

	SetPosition(mPos);

	SetObjectLeft(GetPosition().x - GetWidth() / 2.0f);
	SetObjectRight(GetPosition().x + GetWidth() / 2.0f);
	SetObjectUp(GetPosition().y + GetHeight() / 2.0f);
	SetObjectDown(GetPosition().y - GetHeight() / 2.0f);

	SetLineL({ {GetObjectLeft(),GetObjectUp()}, {GetObjectLeft(),GetObjectDown()} });
	SetLineR({ {GetObjectRight(),GetObjectUp()}, {GetObjectRight(),GetObjectDown()} });
	SetLineU({ {GetObjectLeft(),GetObjectUp()}, {GetObjectRight(),GetObjectUp()} });
	SetLineD({ {GetObjectLeft(),GetObjectDown()}, {GetObjectRight(),GetObjectDown()} });

	mMoveC->SetXSpeed(mVelocity.x);
	mMoveC->SetYSpeed(mVelocity.y);
	GetSquareComponent()->SetCenter(GetPosition());
	GetSpriteComponent()->SetCenter(GetPosition());
}


void Patrol::UpdateTurn_Game(float deltaTime) {
	if (mTurnTime < TurnLimitTime) {
		mMoveC->SetIsMove(false);
		mTurnTime += deltaTime;
		SetRotation(GetRotation() + MicroRad * deltaTime);
	}
	else {
		mMoveC->SetIsMove(true);
		switch (GetClockwise()) {
		case 0:
			SetRotation(M_PI / 2.0f);
			break;
		case 1:
			SetRotation(0.0f);
			break;
		case 2:
			SetRotation(M_PI * 3.0f / 2.0f);
			break;
		case 3:
			SetRotation(M_PI);
		}
		mTurnTime = 0.0f;
		SetIsTurn(false);
	}
	GetSpriteComponent()->SetRotation(-M_PI / 2.0f + GetRotation());
}

void Patrol::UpdateIntersectGhost_Game(float deltaTime) {


	// Lightが照らされているとき
	if (IsIntersect_TC(mStageObjectLight->GetLightTri(),GetGame()->GetGhost()->GetCircleComponent())
		&&!(GetGame()->GetGhost()->GetIsInvincible())) {
		GetGame()->GetGhost()->SetIsLighted(true);
	}
}
