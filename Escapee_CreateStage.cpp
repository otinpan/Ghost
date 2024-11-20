#include"Escapee_CreateStage.h"
#include"StageMenu.h"
#include"Hand.h"

Escapee_CreateStage::Escapee_CreateStage(Vec2 pos, float width, float height,int num)
	:StageObject(pos, width, height)
	,mEscapeeNum(num)
	,mIsBarGripen(false)
{
	switch(num) {
	case 1:
		SetAttribute(StageObject::Attribute::Escapee1);
		break;
	case 2:
		SetAttribute(StageObject::Attribute::Escapee2);
		break;
	case 3:
		SetAttribute(StageObject::Attribute::Escapee3);
		break;
	}
}

Escapee_CreateStage::~Escapee_CreateStage() {

}

void Escapee_CreateStage::InitializeStageObject_CreateStage(CreateStage* createStage) {
	InitializeActor_CreateStage(createStage);
}

void Escapee_CreateStage::UpdateStageObject_CreateStage(float deltaTime) {

}

void Escapee_CreateStage::InitializeStageMenu_CreateStage() {
	mBarCenter = Vec2(
		GetCreateStage()->GetStageMenu()->GetMenuLeft() + GetCreateStage()->GetStageMenu()->GetMenuWidth() / 2.0f,
		GetCreateStage()->GetStageMenu()->GetMenuPos().y
	);
	mBarHeight = GetCreateStage()->GetStageMenu()->GetMenuHeight() * 3.0f / 4.0f;
	mBarMax = mBarCenter.y + mBarHeight / 2.0f;
	mBarMin = mBarCenter.y - mBarHeight / 2.0f;
	mBarPos = Vec2(
		mBarCenter.x,
		mBarMin + mBarHeight * GetSpeed() / 100.0f
	);

	mBarSC_CreateStage = new SquareComponent(this);
	mBarSC_CreateStage->Initialize_CreateStage(mBarPos,
		GetCreateStage()->GetStageMenu()->GetMenuWidth() / 6.0f,
		mBarHeight / 25.0f);
	mBarSC_CreateStage->SetColor(ColorF(0, 0, 0));
}

void Escapee_CreateStage::UpdateStageMenu_CreateStage(float deltaTime) {
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
		mBarPos.y = GetCreateStage()->GetHand()->GetPosition().y;
		if (mBarPos.y < mBarMin)mBarPos.y = mBarMin;
		if (mBarPos.y > mBarMax)mBarPos.y = mBarMax;
		SetSpeed(ConvertToSpeed(mBarMin, mBarHeight, mBarPos.y));
	}
	mBarSC_CreateStage->SetCenter(mBarPos);
}

void Escapee_CreateStage::DrawStageMenu_CreateStage() {
	DrawLine(Vec2(mBarCenter.x, mBarMin), Vec2(mBarCenter.x, mBarMax), 0.002, ColorF(0, 0, 0));
	mStageMenuFont(U"Speed").draw(Arg::center(ConvertToView(Vec2(mBarCenter.x, mBarMax + 0.08))), ColorF(0, 0, 0));
	mStageMenuFont(Format((int)GetSpeed())).draw(Arg::center(ConvertToView(Vec2(mBarPos.x + 0.08, mBarPos.y))), ColorF(0, 0, 0));
}

void Escapee_CreateStage::ShutdownStageMenu_CreateStage() {
	delete mBarSC_CreateStage;
}


