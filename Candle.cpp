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
	SetLightRadRange(GetMaxLightRad() - GetMinLightRad());

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
	mGradiationPos = Vec2(
		GetCreateStage()->GetStageMenu()->GetMenuLeft() + GetCreateStage()->GetStageMenu()->GetMenuWidth() * 2.0f / 3.0f,
		mBarCenter.y
	);

	mGradiationWidth = GetCreateStage()->GetStageMenu()->GetMenuWidth() / 5.0f;
	mGradiationHeight= GetCreateStage()->GetStageMenu()->GetMenuHeight() * 3.0f / 4.0f;

	mBarHeight = mGradiationHeight;
	mBarMax = mBarCenter.y + mBarHeight / 2.0f;
	mBarMin = mBarCenter.y - mBarHeight / 2.0f;

	mBarPos = Vec2(
		mBarCenter.x,
		ConvertToBar(GetLightRad())
		
	);

	mBarSC_CreateStage = new SquareComponent(this);
	mBarSC_CreateStage->Initialize_CreateStage(mBarPos,
		GetCreateStage()->GetStageMenu()->GetMenuWidth() / 6.0f,
		mBarHeight/25.0f);
	mBarSC_CreateStage->SetColor(ColorF(0, 0, 0));


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
			mIsBarGripen = false;
		}
		mBarPos.y = GetCreateStage()->GetHand()->GetPosition().y;
		if (mBarPos.y > mBarMax) mBarPos.y = mBarMax;
		if (mBarPos.y < mBarMin)mBarPos.y = mBarMin;
		SetLightRad(ConvertToLightRad(mBarPos.y));
	}
	mBarSC_CreateStage->SetCenter(mBarPos);
	
}

void Candle::DrawStageMenu_CreateStage() {
	DrawGradiationRect(mGradiationPos, mGradiationWidth, mGradiationHeight, ColorF(1, 1, 0), ColorF(0, 0, 0));
	DrawLine(Vec2(mBarCenter.x, mBarMin), Vec2(mBarCenter.x, mBarMax), 0.002, ColorF(0, 0, 0));
}

void Candle::ShutdownStageMenu_CreateStage() {
	delete mBarSC_CreateStage;
}


float Candle::ConvertToBar(float lightRad) {
	return mBarMin + lightRad / GetLightRadRange() * mBarHeight;
}
float Candle::ConvertToLightRad(float bar) {
	return GetMinLightRad() + (bar - mBarMin) / mBarHeight * GetLightRadRange();
}
