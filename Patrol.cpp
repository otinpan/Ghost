#include"Patrol.h"
#include"CreateStage.h"
#include"StageMenu.h"
#include"Hand.h"
#include"Stage.h"

Patrol::Patrol(Vec2 pos, float width, float height)
	:StageObject(pos, width, height)
	,mIsPlusLasting(false)
	,mIsMinusLasting(false)
	,mPlusTime(0.0)
	,mMinusTime(0.0)
	,mIsBarGripen(false)
{
	SetAttribute(Attribute::Patrol);
}

void Patrol::InitializeStageObject_CreateStage(class CreateStage* createStage) {
	InitializeActor_CreateStage(createStage);
}

void Patrol::UpdateStageObject_CreateStage(float deltaTime) {
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

	mBarSC_CreateStage = new SquareComponent(this);
	mBarSC_CreateStage->Initialize_CreateStage(mBarPos,
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


	mUpCC = new CircleComponent(this);
	mUpCC->Initialize_CreateStage();
	mUpCC->SetCenter(mUpTriPos);
	mUpCC->SetRadius(mTriLength);
	mUpCC->SetColor(ColorF(1.0, 1.0, 0.0, 0));

	mDownCC = new CircleComponent(this);
	mDownCC->Initialize_CreateStage();
	mDownCC->SetCenter(mDownTriPos);
	mDownCC->SetRadius(mTriLength);
	mDownCC->SetColor(ColorF(1.0, 1.0, 0.0, 0));

	mRightCC = new CircleComponent(this);
	mRightCC->Initialize_CreateStage();
	mRightCC->SetCenter(mRightTriPos);
	mRightCC->SetRadius(mTriLength);
	mRightCC->SetColor(ColorF(1.0, 1.0, 0.0, 0));

	mLeftCC = new CircleComponent(this);
	mLeftCC->Initialize_CreateStage();
	mLeftCC->SetCenter(mLeftTriPos);
	mLeftCC->SetRadius(mTriLength);
	mLeftCC->SetColor(ColorF(1.0, 1.0, 0.0, 0));

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

	mPlusCC = new CircleComponent(this);
	mPlusCC->Initialize_CreateStage();
	mPlusCC->SetCenter(mPlusPos);
	mPlusCC->SetRadius(mTriLength);
	mPlusCC->SetColor(ColorF(1, 1, 0, 0));

	mMinusCC = new CircleComponent(this);
	mMinusCC->Initialize_CreateStage();
	mMinusCC->SetCenter(mMinusPos);
	mMinusCC->SetRadius(mTriLength);
	mMinusCC->SetColor(ColorF(1, 1, 0, 0));


	mPlusLastTime = 0.03;
	mMinusLastTime = 0.03;

	
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
	delete mUpCC;
	delete mDownCC;
	delete mRightCC;
	delete mLeftCC;
	delete mPlusCC;
	delete mMinusCC;
	delete mBarSC_CreateStage;
}

void Patrol::InitializeStageObject_Game(class Game* game) {
	InitializeActor_Game(game);

}

void Patrol::InitializeStage_Game() {
	SetPatrolRange(GetPatrolRange() - 1);
	SetSpeed(GetStandardSpeed() + GetSpeed() / 100.0f * GetStandardSpeed());
	switch (GetClockwise()) {
	case 0:
		FromLine = GetLineD();
		ToPos = Vec2({ (float)GetGame()->GetStage()->GetLeft() + GetIteration().second * GetGame()->GetStage()->GetRectWidth() + GetGame()->GetStage()->GetRectWidth() / 2,
		(float)GetGame()->GetStage()->GetUp() - (GetIteration().first + 1 - GetPatrolRange()) * GetGame()->GetStage()->GetRectHeight() + GetGame()->GetStage()->GetRectHeight() / 2 });
		ToLeft = ToPos.x - GetWidth() / 2.0f;
		ToRight = ToPos.x + GetWidth() / 2.0f;
		ToUp = ToPos.y + GetHeight() / 2.0f;
		ToDown = GetPosition().y - GetHeight() / 2.0f;
		ToLine = { {ToLeft,ToUp},{ToRight,ToUp} };
		//velocity
		mVelocity = Vec2(0, GetSpeed());
		break;
	case 1:
		FromLine = GetLineL();
		ToPos = Vec2({ (float)GetGame()->GetStage()->GetLeft() + (GetIteration().second + GetPatrolRange()) * GetGame()->GetStage()->GetRectWidth() + GetGame()->GetStage()->GetRectWidth() / 2,
		(float)GetGame()->GetStage()->GetUp() - (GetIteration().first + 1) * GetGame()->GetStage()->GetRectHeight() + GetGame()->GetStage()->GetRectHeight() / 2 });
		ToLeft = ToPos.x - GetWidth() / 2.0f;
		ToRight = ToPos.x + GetWidth() / 2.0f;
		ToUp = ToPos.y + GetHeight() / 2.0f;
		ToDown = GetPosition().y - GetHeight() / 2.0f;
		ToLine = { {ToRight,ToUp},{ToRight,ToDown} };
		//velocity
		mVelocity = Vec2( GetSpeed(),0);
		break;
	case 2:
		FromLine = GetLineU();
		ToPos = Vec2({ (float)GetGame()->GetStage()->GetLeft() + GetIteration().second * GetGame()->GetStage()->GetRectWidth() + GetGame()->GetStage()->GetRectWidth() / 2,
		(float)GetGame()->GetStage()->GetUp() - (GetIteration().first + 1 + GetPatrolRange()) * GetGame()->GetStage()->GetRectHeight() + GetGame()->GetStage()->GetRectHeight() / 2 });
		ToLeft = ToPos.x - GetWidth() / 2.0f;
		ToRight = ToPos.x + GetWidth() / 2.0f;
		ToUp = ToPos.y + GetHeight() / 2.0f;
		ToDown = GetPosition().y - GetHeight() / 2.0f;
		ToLine = { {ToLeft,ToDown},{ToRight,ToDown} };
		//velocity
		mVelocity = Vec2(0,-GetSpeed());
		break;
	case 3:
		FromLine = GetLineR();
		ToPos = Vec2({ (float)GetGame()->GetStage()->GetLeft() + (GetIteration().second - GetPatrolRange()) * GetGame()->GetStage()->GetRectWidth() + GetGame()->GetStage()->GetRectWidth() / 2,
		(float)GetGame()->GetStage()->GetUp() - (GetIteration().first + 1) * GetGame()->GetStage()->GetRectHeight() + GetGame()->GetStage()->GetRectHeight() / 2 });
		ToLeft = ToPos.x - GetWidth() / 2.0f;
		ToRight = ToPos.x + GetWidth() / 2.0f;
		ToUp = ToPos.y + GetHeight() / 2.0f;
		ToDown = GetPosition().y - GetHeight() / 2.0f;
		ToLine = { {ToLeft,ToUp},{ToLeft,ToDown} };
		//velocity
		mVelocity = Vec2(-GetSpeed(),0);
		break;
	}
	mMoveC = new MoveComponent(this);
	mMoveC->SetXSpeed(mVelocity.x);
	mMoveC->SetYSpeed(mVelocity.y);
}

void Patrol::UpdateStageObject_Game(float deltaTime) {
	Vec2 mPos = GetPosition();
	for (auto& row : GetGame()->GetStage()->GetStageObjects()) {
		for (auto& stageObject : row) {
			if (stageObject == 0)continue;
			if (!IsIntersect_SS(GetSquareComponent(), stageObject->GetSquareComponent())) continue;
			if (stageObject == this)continue;
			switch (GetClockwise()) {
			case 0:
				mPos.y = stageObject->GetObjectDown() - GetHeight() - 0.008; //Playerが下
				mVelocity.y *= -1.0f;
				SetClockwise(2);
				break;
			case 1:
				mPos.x = stageObject->GetObjectLeft() - GetWidth() - 0.008; //Playerが左
				mVelocity.x *= -1.0f;
				SetClockwise(3);
				break;
			case 2:
				mPos.y = stageObject->GetObjectUp() + GetHeight() + 0.008; //Playerが上
				mVelocity.y *= -1.0f;
				SetClockwise(0);
				break;
			case 3:
				mPos.x = stageObject->GetObjectRight() + GetWidth() + 0.008; //Playerが右
				mVelocity.x *= -1.0f;
				SetClockwise(1);
				break;
			}
		}
	}
	/*if (GetSquareComponent()->GetRect().intersects(FromLine) ||
		GetSquareComponent()->GetRect().intersects(ToLine)) {
		switch (GetClockwise()) {
		case 0:
			mVelocity.y *= -1.0f;
			break;
		case 1:
			mVelocity.x *= -1.0f;
			break;
		case 2:
			mVelocity.y *= -1.0f;
			break;
		case 3:
			mVelocity.x *= -1.0f;
			break;
		}
	}*/

	SetPosition(mPos);

	SetObjectLeft( GetPosition().x - GetWidth() / 2.0f);
	SetObjectRight( GetPosition().x + GetWidth() / 2.0f);
	SetObjectUp(GetPosition().y + GetHeight() / 2.0f);
	SetObjectDown( GetPosition().y - GetHeight() / 2.0f);

	SetLineL({ {GetObjectLeft(),GetObjectUp()}, {GetObjectLeft(),GetObjectDown()} });
	SetLineR({ {GetObjectRight(),GetObjectUp()}, {GetObjectRight(),GetObjectDown()} });
	SetLineU({ {GetObjectLeft(),GetObjectUp()}, {GetObjectRight(),GetObjectUp()} });
	SetLineD({ {GetObjectLeft(),GetObjectDown()}, {GetObjectRight(),GetObjectDown()} });


	mMoveC->SetXSpeed(mVelocity.x);
	mMoveC->SetYSpeed(mVelocity.y);
	GetSquareComponent()->SetCenter(GetPosition());
}
