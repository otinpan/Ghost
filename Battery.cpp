#include"Battery.h"
#include"Hand.h"
#include"StageMenu.h"

Battery::Battery(Vec2 pos, float width, float height)
	:StageObject(pos, width, height)
	, mBatterySize(StageObject:: BatterySize::Mid)
{
	SetAttribute(StageObject::Attribute::Battery);
}

Battery::~Battery() {

}

void Battery::InitializeStageObject_CreateStage(class CreateStage* createStage) {
	InitializeActor_CreateStage(createStage);
	

}

void Battery::UpdateStageObject_CreateStage(float deltaTime) {

}

void Battery::InitializeStageMenu_CreateStage() {
	mSmallPos = Vec2(
		(GetCreateStage()->GetStageMenu()->GetMenuRight() + GetCreateStage()->GetStageMenu()->GetMenuLeft()) / 2.0f,
		(GetCreateStage()->GetStageMenu()->GetMenuUp() + GetCreateStage()->GetStageMenu()->GetMenuDown()) * 1.0f / 5.0f
	);
	mMidPos = Vec2(
		(GetCreateStage()->GetStageMenu()->GetMenuRight() + GetCreateStage()->GetStageMenu()->GetMenuLeft()) / 2.0f,
		(GetCreateStage()->GetStageMenu()->GetMenuUp() + GetCreateStage()->GetStageMenu()->GetMenuDown()) * 4.0f / 9.0f
	);
	mBigPos = Vec2(
		(GetCreateStage()->GetStageMenu()->GetMenuRight() + GetCreateStage()->GetStageMenu()->GetMenuLeft()) / 2.0f,
		(GetCreateStage()->GetStageMenu()->GetMenuUp() + GetCreateStage()->GetStageMenu()->GetMenuDown()) * 3.0f / 4.0f
	);
	mMidRad = GetCreateStage()->GetStageMenu()->GetMenuWidth() / 4.0f;
	mSmallRad = mMidRad / 1.5f;
	mBigRad = mMidRad * 1.5f;
	mSmallCC = new CircleComponent(this,200,true);
	mSmallCC->InitializeDrawing_CreateStage();
	mSmallCC->SetCenter(mSmallPos);
	mSmallCC->SetRadius(mSmallRad);
	mSmallCC->SetColor(ColorF(0, 1, 128.0f / 255.0f));
	mMidCC = new CircleComponent(this,200,true);
	mMidCC->InitializeDrawing_CreateStage();
	mMidCC->SetCenter(mMidPos);
	mMidCC->SetRadius(mMidRad);
	mMidCC->SetColor(ColorF(0, 1, 128.0f / 255.0f));
	mBigCC = new CircleComponent(this,200,true);
	mBigCC->InitializeDrawing_CreateStage();
	mBigCC->SetCenter(mBigPos);
	mBigCC->SetRadius(mBigRad);
	mBigCC->SetColor(ColorF(0, 1, 128.0f / 255.0f));
}

void Battery::UpdateStageMenu_CreateStage(float deltaTime) {
	if (mBatterySize == BatterySize::Big) {
		if (GetCreateStage()->GetHand()->GetInputMinus().down()||
			GetCreateStage()->GetHand()->GetInputD().down()) {
			mBatterySize = BatterySize::Mid;
		}
	}
	else if (mBatterySize == BatterySize::Mid) {
		if (GetCreateStage()->GetHand()->GetInputPlus().down()||
			GetCreateStage()->GetHand()->GetInputU().down()) {
			mBatterySize = BatterySize::Big;
		}
		if (GetCreateStage()->GetHand()->GetInputMinus().down()||
			GetCreateStage()->GetHand()->GetInputD().down()) {
			mBatterySize = BatterySize::Small;
		}
	}
	else if (mBatterySize == BatterySize::Small) {
		if (GetCreateStage()->GetHand()->GetInputPlus().down()||
			GetCreateStage()->GetHand()->GetInputU().down()) {
			mBatterySize = BatterySize::Mid;
		}
	}

	if (GetCreateStage()->GetHand()->GetInputChoose().down()) {
		if (IsIntersect_CC(mBigCC, GetCreateStage()->GetHand()->GetCircleComponent())) {
			mBatterySize = BatterySize::Big;
		}
		if (IsIntersect_CC(mMidCC, GetCreateStage()->GetHand()->GetCircleComponent())) {
			mBatterySize = BatterySize::Mid;
		}
		if (IsIntersect_CC(mSmallCC, GetCreateStage()->GetHand()->GetCircleComponent())) {
			mBatterySize = BatterySize::Small;
		}
	}

	SetBatterySize(mBatterySize);

	if (mBatterySize == BatterySize::Big) {
		mBigCC->SetColor(ColorF(0, 1, 128.0f / 255.0f));
	}
	else {
		mBigCC->SetColor(ColorF(0, 0, 0));
	}
	if (mBatterySize == BatterySize::Mid) {
		mMidCC->SetColor(ColorF(0, 1, 128.0f / 255.0f));
	}
	else {
		mMidCC->SetColor(ColorF(0, 0, 0));
	}
	if (mBatterySize == BatterySize::Small) {
		mSmallCC->SetColor(ColorF(0, 1, 128.0f / 255.0f));
	}
	else {
		mSmallCC->SetColor(ColorF(0, 0, 0));
	}
}

void Battery::DrawStageMenu_CreateStage() {

}

void Battery::ShutdownStageMenu_CreateStage() {
	delete mBigCC;
	delete mMidCC;
	delete mSmallCC;
}

void Battery::InitializeStageObject_Game(class Game* game) {
	InitializeActor_Game(game);
}

void Battery::UpdateStageObject_Game(float deltaTime) {

}
