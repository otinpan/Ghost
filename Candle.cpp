#include"Candle.h"
#include"Stage.h"
#include"StageMenu.h"
#include"Hand.h"

Candle::Candle(Vec2 pos,float width,float height,float rad)
	:StageObject(pos,width,height)
	,mCenter(pos)
	,cc(0)
{
	SetAttribute(Attribute::Candle);
	SetRadius(rad);
	SetLightRad(rad *3.0);

}

Candle::~Candle() {
}

void Candle::InitializeStageObject_CreateStage(class CreateStage* createStage) {
	InitializeActor_CreateStage(createStage);
	SetMaxLightRad(GetCreateStage()->GetStage()->GetHeight() / 2);
	SetMinLightRad(0.0f);
	mLightRadRange = mMaxLightRadius - mMinLightRadius;

	cc = new CircleComponent(this);
	cc->Initialize_CreateStage();
	cc->SetCenter(GetPosition());
	cc->SetRadius(GetLightRad());
	cc->SetColor(ColorF(1, 1, float(202 / 255),0.5));
}

void Candle::UpdateStageObject_CreateStage(float deltaTime) {
	cc->SetCenter(GetPosition());
	cc->SetRadius(GetLightRad());
}

void Candle::InitializeStageMenu_CreateStage() {
	mBarCenter = Vec2(
		GetCreateStage()->GetStageMenu()->GetMenuLeft() + GetCreateStage()->GetStageMenu()->GetMenuWidth() / 3.0f,
		GetCreateStage()->GetStageMenu()->GetMenuPos().y
	);

	mBarHeight = GetCreateStage()->GetStageMenu()->GetMenuHeight() * 3.0f / 4.0f;
	mBarMax = mBarPos.y + mBarHeight / 2.0f;
	mBarMin = mBarPos.y - mBarHeight / 2.0f;

	mBarPos = Vec2(
		mBarCenter.x,
		ConvertToBar(GetLightRad())
	);

	mBarSC_CreateStage = new SquareComponent(this);
	mBarSC_CreateStage->Initialize_CreateStage(mBarPos,
		GetCreateStage()->GetStageMenu()->GetMenuWidth() / 6.0f,
		mBarHeight/10.f);
	mBarSC_CreateStage->SetColor(ColorF(0, 0, 0));

	Print << mBarPos;
}

void Candle::UpdateStageMenu_CreateStage(float deltaTime) {
	if (GetCreateStage()->GetHand()->GetInputPlus().pressed()) {
		SpreadLightRad(true);
	}
	if (GetCreateStage()->GetHand()->GetInputMinus().pressed()) {
		SpreadLightRad(false);
	}
	mBarPos.y = ConvertToBar(GetLightRad());

	if (!mIsBarGripen) {
		if (IsIntersect_SC(mBarSC_CreateStage, GetCreateStage()->GetHand()->GetCircleComponent())) {
			if (GetCreateStage()->GetHand()->GetInputChoose().pressed()) {
				mIsBarGripen = true;
			}
		}
	}
	else {
		if (!GetCreateStage()->GetHand()->GetInputChoose().pressed()) {
			mIsBarGripen = true;
		}
		mBarPos = Vec2(
			mBarCenter.x,
			GetCreateStage()->GetHand()->GetPosition().y
		);
		SetLightRad(ConvertToLightRad(mBarPos.y));
	}
	mBarSC_CreateStage->SetCenter(mBarPos);
	
}

void Candle::DrawStageMenu_CreateStage() {

}

void Candle::ShutdownStageMenu_CreateStage() {

}


float Candle::ConvertToBar(float lightRad) {
	return mBarMin + lightRad / mLightRadRange * mBarHeight;
}
float Candle::ConvertToLightRad(float bar) {
	return mMinLightRadius+(bar - mBarMin) / mBarHeight * mLightRadRange;
}
