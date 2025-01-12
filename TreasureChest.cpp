#include"TreasureChest.h"
#include"StageMenu.h"
#include"Hand.h"

TreasureChest::TreasureChest(Vec2 pos, float width, float height)
	:StageObject(pos, width, height)
	, mBatterySize(StageObject::BatterySize::Mid)
	, mTreasure(StageObject::Treasure::Empty)
{
	SetAttribute(Attribute::TreasureChest);
}

TreasureChest::~TreasureChest() {

}

void TreasureChest::InitializeStageObject_CreateStage(class CreateStage* createStage) {
	InitializeActor_CreateStage(createStage);
	mNoneSC = 0;
	mBatterySC = 0;
	mKeySC = 0;
}

void TreasureChest::UpdateStageObject_CreateStage(float deltaTime) {

}

void TreasureChest::InitializeStageMenu_CreateStage() {
	mEachHeight = GetCreateStage()->GetStageMenu()->GetMenuHeight() / 3.0f;
	mRectHeight = mEachHeight / 3.0f;
	mRectWidth = mRectHeight * GetScreenHeight() / GetScreenWidth();

	mNoneSC = new SquareComponent(this,200,true);
	mBatterySC = new SquareComponent(this,200,true);
	mKeySC = new SquareComponent(this,200,true);

	mMidPos = Vec2(
		(GetCreateStage()->GetStageMenu()->GetMenuLeft() + GetCreateStage()->GetStageMenu()->GetMenuRight()) / 2.0f,
		(GetCreateStage()->GetStageMenu()->GetMenuUp()+GetCreateStage()->GetStageMenu()->GetMenuDown())/2.0f
	);

	mNoneSC->InitializeDrawing_CreateStage(
		Vec2(mMidPos.x,mMidPos.y+mEachHeight*2.0f/3.0f+mRectHeight/2.0f),
		mRectWidth,mRectHeight
	);
	mKeySC->InitializeDrawing_CreateStage(
		mMidPos, mRectWidth, mRectHeight
	);
	mBatterySC->InitializeDrawing_CreateStage(
		Vec2(mMidPos.x, mMidPos.y - mEachHeight*2.0f/3.0f - mRectHeight / 2.0f),
		mRectWidth, mRectHeight
	);

	mBatteryPos = Vec2(mMidPos.x, mMidPos.y - mEachHeight *2.0f/ 3.0f - mRectHeight / 2.0f);
	mNoneSC->SetColor(ColorF(0, 0, 0));
	mKeySC->SetColor(ColorF((float)76 / 255, (float)0, (float)153 / 255));
	mBatterySC->SetColor(ColorF(0, 1, 128.0f / 255.0f));

	mMidBatteryRad = mRectWidth / 4.0f;
	mSmallCC = new CircleComponent(this,200,true);
	mSmallCC->InitializeDrawing_CreateStage();
	mSmallCC->SetCenter(Vec2(
		mBatteryPos.x + mRectWidth,
		mBatteryPos.y - mRectHeight/2.0f)
	);
	mSmallCC->SetRadius(mMidBatteryRad / 1.5f);
	mSmallCC->SetColor(ColorF(0, 0, 0));

	mMidCC = new CircleComponent(this,200,true);
	mMidCC->InitializeDrawing_CreateStage();
	mMidCC->SetCenter(Vec2(
		mBatteryPos.x + mRectWidth,
		mBatteryPos.y)
	);
	mMidCC->SetRadius(mMidBatteryRad);
	mMidCC->SetColor(ColorF(0, 0, 0));

	mBigCC = new CircleComponent(this,200,true);
	mBigCC->InitializeDrawing_CreateStage();
	mBigCC->SetCenter(Vec2(
		mBatteryPos.x + mRectWidth,
		mBatteryPos.y+mRectHeight*5.0f/9.0f)
	);
	mBigCC->SetRadius(mMidBatteryRad*1.2f);
	mBigCC->SetColor(ColorF(0, 0, 0));

}

void TreasureChest::UpdateStageMenu_CreateStage(float deltaTime) {
	if (GetCreateStage()->GetHand()->GetInputChoose().down()) {
		if (IsIntersect_SC(mNoneSC, GetCreateStage()->GetHand()->GetCircleComponent())) {
			mTreasure = StageObject::Treasure::Empty;
		}
		if (IsIntersect_SC(mKeySC, GetCreateStage()->GetHand()->GetCircleComponent())) {
			mTreasure = StageObject::Treasure::TreasureKey;
		}
		if (IsIntersect_SC(mBatterySC, GetCreateStage()->GetHand()->GetCircleComponent())) {
			mTreasure = StageObject::Treasure::TreasureBattery;
		}
	}

	if (mTreasure == StageObject::Treasure::Empty) {
		if (GetCreateStage()->GetHand()->GetInputD().down()) {
			mTreasure = StageObject::Treasure::TreasureKey;
		}
	}else if(mTreasure==StageObject::Treasure::TreasureKey){
		if (GetCreateStage()->GetHand()->GetInputD().down()) {
			mTreasure = StageObject::Treasure::TreasureBattery;
		}
		if (GetCreateStage()->GetHand()->GetInputU().down()) {
			mTreasure = StageObject::Treasure::Empty;
		}
	}
	else if (mTreasure == StageObject::Treasure::TreasureBattery) {
		if (GetCreateStage()->GetHand()->GetInputU().down()) {
			mTreasure = StageObject::Treasure::TreasureKey;
		}
		//BatterySize
		if (mBatterySize == StageObject::BatterySize::Small) {
			if (GetCreateStage()->GetHand()->GetInputPlus().down()) {
				mBatterySize = StageObject::BatterySize::Mid;
			}
		}
		if (mBatterySize == StageObject::BatterySize::Mid) {
			if (GetCreateStage()->GetHand()->GetInputMinus().down()) {
				mBatterySize = StageObject::BatterySize::Small;
			}
			if (GetCreateStage()->GetHand()->GetInputPlus().down()) {
				mBatterySize = StageObject::BatterySize::Big;
			}
		}
		if (mBatterySize == StageObject::BatterySize::Big) {
			if (GetCreateStage()->GetHand()->GetInputMinus().down()) {
				mBatterySize = StageObject::BatterySize::Mid;
			}
		}
	}

	if (mBatterySize == StageObject::BatterySize::Small) {
		mSmallCC->SetColor(ColorF(0, 1, 128.0f / 255.0f));
	}
	else {
		mSmallCC->SetColor(ColorF(0, 0, 0));
	}
	if (mBatterySize == StageObject::BatterySize::Mid) {
		mMidCC->SetColor(ColorF(0, 1, 128.0f / 255.0f));
	}
	else {
		mMidCC->SetColor(ColorF(0, 0, 0));
	}
	if (mBatterySize == StageObject::BatterySize::Big) {
		mBigCC->SetColor(ColorF(0, 1, 128.0f / 255.0f));
	}
	else {
		mBigCC->SetColor(ColorF(0, 0, 0));
	}

	SetTreasure(mTreasure);
	SetBatterySize(mBatterySize);

}

void TreasureChest::DrawStageMenu_CreateStage() {
	switch (mTreasure) {
	case StageObject::Empty:
		DrawRectFrame(Vec2(mMidPos.x, mMidPos.y + mEachHeight*2.0f/3.0f + mRectHeight / 2.0f),
		mRectWidth, mRectHeight, 0, 0.002, ColorF(1, 1, 0));
		break;
	case StageObject::TreasureKey:
		DrawRectFrame(mMidPos, mRectWidth, mRectHeight,0,0.002,ColorF(1,1,0));
		break;
	case StageObject::TreasureBattery:
		DrawRectFrame(Vec2(mMidPos.x, mMidPos.y - mEachHeight*2.0f/3.0f - mRectHeight / 2.0f),
		mRectWidth, mRectHeight,0,0.002,ColorF(1,1,0));
	}
}

void TreasureChest::ShutdownStageMenu_CreateStage() {
	delete mNoneSC;
	delete mKeySC;
	delete mBatterySC;
	delete mSmallCC;
	delete mMidCC;
	delete mBigCC;
}

void TreasureChest::InitializeStageObject_Game(class Game* game) {
	InitializeActor_Game(game);
}

void TreasureChest::UpdateStageObject_Game(float deltaTime) {

}
