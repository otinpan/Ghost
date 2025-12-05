#include"Ghost_CreateStage.h"
#include"StageMenu.h"
#include"Hand.h"

Ghost_CreateStage::Ghost_CreateStage(Vec2 pos, float width, float height)
	:StageObject(pos,width,height)
	,mIsBarGripen(false)
{
	SetAttribute(StageObject::Attribute::Ghost);
}

Ghost_CreateStage::~Ghost_CreateStage() {
}

void Ghost_CreateStage::InitializeStageObject_CreateStage(CreateStage* createStage) {
	InitializeActor_CreateStage(createStage);
}


void Ghost_CreateStage::UpdateStageObject_CreateStage(float deltaTime) {

}

void Ghost_CreateStage::InitializeStageMenu_CreateStage() {
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

	mBarSC_CreateStage = new SquareComponent(this,200, DrawingComponent::DrawState::UNAFFECTED);
	mBarSC_CreateStage->InitializeDrawing_CreateStage(mBarPos,
		GetCreateStage()->GetStageMenu()->GetMenuWidth() / 6.0f,
		mBarHeight / 25.0f);
	mBarSC_CreateStage->SetColor(ColorF(0, 0, 0));
}

void Ghost_CreateStage::UpdateStageMenu_CreateStage(float deltaTime) {
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
		SetSpeed(ConvertToSpeed(mBarMin,mBarHeight,mBarPos.y));
	}
	mBarSC_CreateStage->SetCenter(mBarPos);
}

void Ghost_CreateStage::DrawStageMenu_CreateStage() {
	DrawLine(Vec2(mBarCenter.x, mBarMin), Vec2(mBarCenter.x, mBarMax), 0.002, ColorF(0, 0, 0));
	mStageMenuFont(U"Speed").draw(Arg::center(ConvertToView(Vec2(mBarCenter.x, mBarMax + 0.08))), ColorF(0, 0, 0));
	mStageMenuFont(Format((int)GetSpeed())).draw(Arg::center(ConvertToView(Vec2(mBarPos.x + 0.08, mBarPos.y))), ColorF(0, 0, 0));
}

void Ghost_CreateStage::ShutdownStageMenu_CreateStage() {
	delete mBarSC_CreateStage;
}
