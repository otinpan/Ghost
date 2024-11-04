#include"TreasureChest.h"
#include"StageMenu.h"
#include"Hand.h"

TreasureChest::TreasureChest(Vec2 pos, float width, float height)
	:StageObject(pos,width,height)
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
	mRectHeight = mEachHeight / 2.0f;
	mRectWidth = mRectHeight * GetScreenHeight() / GetScreenWidth();

	mNoneSC = new SquareComponent(this);
	mBatterySC = new SquareComponent(this);
	mKeySC = new SquareComponent(this);

	mMidPos = Vec2(
		(GetCreateStage()->GetStageMenu()->GetMenuLeft() + GetCreateStage()->GetStageMenu()->GetMenuRight()) / 2.0f,
		(GetCreateStage()->GetStageMenu()->GetMenuUp()+GetCreateStage()->GetStageMenu()->GetMenuDown())/2.0f
	);

	mNoneSC->Initialize_CreateStage(
		Vec2(mMidPos.x,mMidPos.y+mEachHeight+mRectHeight/2.0f),
		mRectWidth,mRectHeight
	);
	mKeySC->Initialize_CreateStage(
		mMidPos, mRectWidth, mRectHeight
	);
	mBatterySC->Initialize_CreateStage(
		Vec2(mMidPos.x, mMidPos.y - mEachHeight - mRectHeight / 2.0f),
		mRectWidth, mRectHeight
	);
	mNoneSC->SetColor(ColorF(0, 0, 0));
	mKeySC->SetColor(ColorF((float)76 / 255, (float)0, (float)153 / 255));
	mBatterySC->SetColor(ColorF(0, 1, 128.0f / 255.0f));

	mTreasure = Treasure::None;
}

void TreasureChest::UpdateStageMenu_CreateStage(float deltaTime) {

}

void TreasureChest::DrawStageMenu_CreateStage() {

}

void TreasureChest::ShutdownStageMenu_CreateStage() {

}
