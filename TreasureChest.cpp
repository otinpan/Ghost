#include"TreasureChest.h"
#include"StageMenu.h"
#include"Hand.h"

TreasureChest::TreasureChest(Vec2 pos, float width, float height)
	:StageObject(pos, width, height)
	,scKey(nullptr)
	,scBattery(nullptr)
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
	SetBatterySize(StageObject::BatterySize::Small);
}

void TreasureChest::UpdateStageObject_CreateStage(float deltaTime) {

}

void TreasureChest::InitializeStageMenu_CreateStage() {
	mEachHeight = GetCreateStage()->GetStageMenu()->GetMenuHeight() / 3.0f;
	mRectHeight = mEachHeight / 3.0f;
	mRectWidth = mRectHeight * GetScreenHeight() / GetScreenWidth();

	mNoneSC = new SquareComponent(this,200, DrawingComponent::DrawingState::UNAFFECTED);
	mBatterySC = new SquareComponent(this,200, DrawingComponent::DrawingState::UNAFFECTED);
	mKeySC = new SquareComponent(this,200,DrawingComponent::DrawingState::UNAFFECTED);
	mBatterySC->SetIsDraw(false);
	mKeySC->SetIsDraw(false);

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
	mSmallCC = new CircleComponent(this,200, DrawingComponent::DrawingState::UNAFFECTED);
	mSmallCC->InitializeDrawing_CreateStage();
	mSmallCC->SetCenter(Vec2(
		mBatteryPos.x + mRectWidth,
		mBatteryPos.y - mRectHeight/2.0f)
	);
	mSmallCC->SetRadius(mMidBatteryRad / 1.5f);
	mSmallCC->SetColor(ColorF(0, 0, 0));

	mMidCC = new CircleComponent(this,200, DrawingComponent::DrawingState::UNAFFECTED);
	mMidCC->InitializeDrawing_CreateStage();
	mMidCC->SetCenter(Vec2(
		mBatteryPos.x + mRectWidth,
		mBatteryPos.y)
	);
	mMidCC->SetRadius(mMidBatteryRad);
	mMidCC->SetColor(ColorF(0, 0, 0));

	mBigCC = new CircleComponent(this,200, DrawingComponent::DrawingState::UNAFFECTED);
	mBigCC->InitializeDrawing_CreateStage();
	mBigCC->SetCenter(Vec2(
		mBatteryPos.x + mRectWidth,
		mBatteryPos.y+mRectHeight*5.0f/9.0f)
	);
	mBigCC->SetRadius(mMidBatteryRad*1.2f);
	mBigCC->SetColor(ColorF(0, 0, 0));

	scKey = new SpriteComponent(this, 200, DrawingComponent::DrawingState::UNAFFECTED);
	scKey->InitializeDrawing_CreateStage(mMidPos, mRectWidth, mRectHeight);
	scKey->SetTexture(TextureAsset(U"key"));
	scBattery = new SpriteComponent(this, 200, DrawingComponent::DrawingState::UNAFFECTED);
	scBattery ->InitializeDrawing_CreateStage(Vec2(mMidPos.x, mMidPos.y - mEachHeight * 2.0f / 3.0f - mRectHeight / 2.0f),
		mRectWidth, mRectHeight);
	scBattery->SetTexture(TextureAsset(U"battery"));


}

void TreasureChest::InitializeStage_CreateStage() {
}

void TreasureChest::UpdateStageMenu_CreateStage(float deltaTime) {
	if (GetCreateStage()->GetHand()->GetInputChoose().down()||MouseL.down()) {
		if (IsIntersect_SC(mNoneSC, GetCreateStage()->GetHand()->GetCircleComponent())) {
			SetTreasure(StageObject::Treasure::Empty);
		}
		if (IsIntersect_SC(mKeySC, GetCreateStage()->GetHand()->GetCircleComponent())) {
			SetTreasure(StageObject::Treasure::TreasureKey);
		}
		if (IsIntersect_SC(mBatterySC, GetCreateStage()->GetHand()->GetCircleComponent())) {
			SetTreasure(StageObject::Treasure::TreasureBattery);
		}
	}

	if (GetTreasure() == StageObject::Treasure::Empty) {
		if (GetCreateStage()->GetHand()->GetInputD().down()) {
			SetTreasure(StageObject::Treasure::TreasureKey);
		}
	}else if(GetTreasure() == StageObject::Treasure::TreasureKey) {
		if (GetCreateStage()->GetHand()->GetInputD().down()) {
			SetTreasure(StageObject::Treasure::TreasureBattery);
		}
		if (GetCreateStage()->GetHand()->GetInputU().down()) {
			SetTreasure(StageObject::Treasure::Empty);
		}
	}
	else if (GetTreasure() == StageObject::Treasure::TreasureBattery) {
		if (GetCreateStage()->GetHand()->GetInputU().down()) {
			SetTreasure(StageObject::Treasure::TreasureKey);
		}
		//BatterySize
		if (GetBatterySize() == StageObject::BatterySize::Small) {
			if (GetCreateStage()->GetHand()->GetInputPlus().down()) {
				SetBatterySize(StageObject::BatterySize::Mid);
			}
		}
		else if (GetBatterySize() == StageObject::BatterySize::Mid) {
			if (GetCreateStage()->GetHand()->GetInputMinus().down()) {
				SetBatterySize(StageObject::BatterySize::Small);
			}
			if (GetCreateStage()->GetHand()->GetInputPlus().down()) {
				SetBatterySize(StageObject::BatterySize::Big);
			}
		}
		else if (GetBatterySize() == StageObject::BatterySize::Big) {
			if (GetCreateStage()->GetHand()->GetInputMinus().down()) {
				SetBatterySize(StageObject::BatterySize::Mid);
			}
		}
		
	}

	if (GetBatterySize() == StageObject::BatterySize::Small) {
		mSmallCC->SetColor(ColorF(0, 1, 128.0f / 255.0f));
	}
	else {
		mSmallCC->SetColor(ColorF(0, 0, 0));
	}
	if (GetBatterySize() == StageObject::BatterySize::Mid) {
		mMidCC->SetColor(ColorF(0, 1, 128.0f / 255.0f));
	}
	else {
		mMidCC->SetColor(ColorF(0, 0, 0));
	}
	if (GetBatterySize() == StageObject::BatterySize::Big) {
		mBigCC->SetColor(ColorF(0, 1, 128.0f / 255.0f));
	}
	else {
		mBigCC->SetColor(ColorF(0, 0, 0));
	}


}

void TreasureChest::DrawStageMenu_CreateStage() {
	switch (GetTreasure()) {
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
	delete scKey;
	delete scBattery;
}

void TreasureChest::InitializeStageObject_Game(class Game* game) {
	InitializeActor_Game(game);
}

void TreasureChest::UpdateStageObject_Game(float deltaTime) {

}
