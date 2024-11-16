#include"StageMenu.h"
#include"CreateStage.h"
#include"Stage.h"
#include"Hand.h"
#include"Brock.h"
#include"Door.h"
#include"Patrol.h"
#include"Battery.h"
#include"Key.h"
#include"TreasureChest.h"
#include"Candle.h"
#include"Ghost_CreateStage.h"
#include"Escapee_CreateStage.h"


StageMenu::StageMenu()
    :mIsEndOver(false)
{

}

StageMenu::~StageMenu(){}

void StageMenu::Initialize_CreateStage(CreateStage* createStage) {
	mCreateStage = createStage;
	mMenuLeft = mCreateStage->GetStage()->GetLeft()
		+ mCreateStage->GetStage()->GetWidth() + 0.05;
	mMenuUp = mCreateStage->GetStage()->GetUp();
	mMenuRight = 0.95;
	mMenuDown = 0.0;

	mMenuWidth = mMenuRight - mMenuLeft;
	mMenuHeight = mMenuUp - mMenuDown;

	mMenuPos = Vec2{ mMenuLeft + mMenuWidth / 2,mMenuUp - mMenuHeight / 2 };
	mMenuRect = RectF{ mMenuLeft,mMenuUp,mMenuWidth,mMenuHeight };

	//ObjectMenu
	mObjectMenuLeft = mCreateStage->GetStage()->GetLeft();
	mObjectMenuUp = mCreateStage->GetStage()->GetDown() - 0.1f;
	mObjectMenuRight = mCreateStage->GetStage()->GetRight();
	mObjectMenuDown = -0.95f;
	mObjectMenuPos = Vec2((mObjectMenuLeft + mObjectMenuRight) / 2.0f,
		(mObjectMenuUp + mObjectMenuDown) / 2.0f);
	mObjectMenuWidth = mObjectMenuRight - mObjectMenuLeft;
	mObjectMenuHeight = mObjectMenuUp - mObjectMenuDown;

	mObjectNum = 7;
	mObjectEachWidth = mObjectMenuWidth / mObjectNum;
	int i = 0;
	mBrock = new Brock(Vec2(mObjectMenuLeft+mObjectEachWidth * i + mObjectEachWidth / 2.0f,
		(mObjectMenuUp + mObjectMenuDown) / 2.0f),
		mCreateStage->GetStage()->GetRectWidth(),
		mCreateStage->GetStage()->GetRectHeight());
	mBrock->InitializeStageObject_CreateStage(mCreateStage);
	mBrock->SetIsInObjectMenu(true);
	i++;
	mDoor = new Door(Vec2(mObjectMenuLeft+mObjectEachWidth * i + mObjectEachWidth / 2.0f,
		(mObjectMenuUp + mObjectMenuDown) / 2.0f),
		mCreateStage->GetStage()->GetRectWidth(),
		mCreateStage->GetStage()->GetRectHeight());
	mDoor->InitializeStageObject_CreateStage(mCreateStage);
	mDoor->SetIsInObjectMenu(true);
	i++;
	mPatrol = new Patrol(Vec2(mObjectMenuLeft+mObjectEachWidth * i + mObjectEachWidth / 2.0f,
		(mObjectMenuUp + mObjectMenuDown) / 2.0f),
		mCreateStage->GetStage()->GetRectWidth(),
		mCreateStage->GetStage()->GetRectHeight());
	mPatrol->InitializeStageObject_CreateStage(mCreateStage);
	mPatrol->SetIsInObjectMenu(true);
	i++;
	mKey = new Key(Vec2(mObjectMenuLeft+mObjectEachWidth * i + mObjectEachWidth / 2.0f,
		(mObjectMenuUp + mObjectMenuDown) / 2.0f),
		mCreateStage->GetStage()->GetRectWidth(),
		mCreateStage->GetStage()->GetRectHeight());
	mKey->InitializeStageObject_CreateStage(mCreateStage);
	mKey->SetIsInObjectMenu(true);
	i++;
	mBattery = new Battery(Vec2(mObjectMenuLeft+mObjectEachWidth * i + mObjectEachWidth / 2.0f,
		(mObjectMenuUp + mObjectMenuDown) / 2.0f),
		mCreateStage->GetStage()->GetRectWidth(),
		mCreateStage->GetStage()->GetRectHeight());
	mBattery->InitializeStageObject_CreateStage(mCreateStage);
	mBattery->SetIsInObjectMenu(true);
	i++;
	mTreasureChest = new TreasureChest(Vec2{mObjectMenuLeft+ mObjectEachWidth * i + mObjectEachWidth / 2.0f,
		(mObjectMenuUp + mObjectMenuDown) / 2.0f },
		mCreateStage->GetStage()->GetRectWidth(),
		mCreateStage->GetStage()->GetRectHeight());
	mTreasureChest->InitializeStageObject_CreateStage(mCreateStage);
	mTreasureChest->SetIsInObjectMenu(true);
	i++;
	mCandle = new Candle(Vec2(mObjectMenuLeft+mObjectEachWidth * i + mObjectEachWidth / 2.0f,
		(mObjectMenuUp + mObjectMenuDown) / 2.0f),
		 mCreateStage->GetStage()->GetRectWidth() / 3,
	     mCreateStage->GetStage()->GetRectHeight() / 3,
		 mCreateStage->GetStage()->GetRectHeight() / 6);
	mCandle->InitializeStageObject_CreateStage(mCreateStage);
	mCandle->SetIsInObjectMenu(true);

	mPlayerPos = Vec2(
		mMenuPos.x,
		(mMenuDown - 1.0) / 2.0f
	);
	mPlayerRectWidth = mCreateStage->GetStage()->GetRectWidth() / 3.0f;
	mPlayerRectHeight = mCreateStage->GetStage()->GetRectHeight();
	mGhost = new Ghost_CreateStage(Vec2(mPlayerPos.x,
		mPlayerPos.y+2*mPlayerRectHeight),mPlayerRectWidth,mPlayerRectHeight
	);
	mGhost->InitializeStageObject_CreateStage(mCreateStage);
	mGhost->SetIsInObjectMenu(true);
	mEscapee1 = new Escapee_CreateStage(Vec2(mPlayerPos.x - mPlayerRectWidth * 5.0f,
		mPlayerPos.y), mPlayerRectWidth, mPlayerRectHeight,1);
	mEscapee1->InitializeStageObject_CreateStage(mCreateStage);
	mEscapee1->SetIsInObjectMenu(true);
	mEscapee2 = new Escapee_CreateStage(Vec2(mPlayerPos.x,
		mPlayerPos.y), mPlayerRectWidth, mPlayerRectHeight,2);
	mEscapee2->InitializeStageObject_CreateStage(mCreateStage);
	mEscapee2->SetIsInObjectMenu(true);
	mEscapee3 = new Escapee_CreateStage(Vec2(mPlayerPos.x + mPlayerRectWidth * 5.0f,
		mPlayerPos.y), mPlayerRectWidth, mPlayerRectHeight,3);
	mEscapee3->InitializeStageObject_CreateStage(mCreateStage);
	mEscapee3->SetIsInObjectMenu(true);

	mEndPos = Vec2(
		mPlayerPos.x,
		mPlayerPos.y - mPlayerRectHeight * 3
	);
	mEndRectWidth = mMenuWidth * 3.0f / 4.0f;
	mEndRectHeight = (mPlayerPos.y + 1.0f) / 3.0f;
	mEndRect = RectF(Arg::center(mEndPos), mEndRectWidth, mEndRectHeight);
}

void StageMenu::Update_CreateStage(float deltaTime) {
}


void StageMenu::Draw_CreateStage() {
	DrawRectFrame(mObjectMenuPos, mObjectMenuWidth, mObjectMenuHeight, 0.003,0, ColorF(1, 1, 1));
	DrawRectFrame(mMenuPos, mMenuWidth, mMenuHeight, 0.003,0, ColorF(1, 1, 1));
	if (mCreateStage->GetHand()->GetIsChoose()) {
		mCreateStage->GetHand()->GetChoosing()->DrawStageMenu_CreateStage();
	}

	DrawRectFrame(mEndPos, mEndRectWidth, mEndRectHeight, 0, 0.003, ColorF(0, 0, 0));
	if (mIsEndOver) {
		DrawRect(mEndPos, mEndRectWidth, mEndRectHeight, ColorF(160.0f / 255.0f, 160.0f / 255.0f, 160.0f / 255.0f));
	}
	else {
		DrawRect(mEndPos, mEndRectWidth, mEndRectHeight, ColorF(1, 1, 1));
	}
}

RectF StageMenu::GetViewStageMenuRect() {
	return RectF(ConvertToView(
		Vec2{ mMenuLeft,mMenuUp }),
		GetScreenWidth() * mMenuWidth / 2.0f,
		GetScreenHeight() * mMenuHeight / 2.0f);
}

void StageMenu::RemakeStageObject(class StageObject* stageObject) {
	switch (stageObject->GetAttribute()) {
	case StageObject::Attribute::Brock:
		mBrock = new Brock(Vec2(mObjectMenuLeft + mObjectEachWidth * 0 + mObjectEachWidth / 2.0f,
			(mObjectMenuUp + mObjectMenuDown) / 2.0f),
		mCreateStage->GetStage()->GetRectWidth(),
		mCreateStage->GetStage()->GetRectHeight());
		mBrock->InitializeStageObject_CreateStage(mCreateStage);
		mBrock->SetIsInObjectMenu(true);
		break;
	case StageObject::Attribute::Door:
		mDoor = new Door(Vec2(mObjectMenuLeft + mObjectEachWidth * 1 + mObjectEachWidth / 2.0f,
			(mObjectMenuUp + mObjectMenuDown) / 2.0f),
		mCreateStage->GetStage()->GetRectWidth(),
		mCreateStage->GetStage()->GetRectHeight());
		mDoor->InitializeStageObject_CreateStage(mCreateStage);
		mDoor->SetIsInObjectMenu(true);
		break;
	case StageObject::Attribute::Key:
		mKey = new Key(Vec2(mObjectMenuLeft + mObjectEachWidth * 3 + mObjectEachWidth / 2.0f,
			(mObjectMenuUp + mObjectMenuDown) / 2.0f),
		mCreateStage->GetStage()->GetRectWidth(),
		mCreateStage->GetStage()->GetRectHeight());
		mKey->InitializeStageObject_CreateStage(mCreateStage);
		mKey->SetIsInObjectMenu(true);
		break;
	case StageObject::Attribute::Patrol:
		mPatrol = new Patrol(Vec2(mObjectMenuLeft + mObjectEachWidth * 2 + mObjectEachWidth / 2.0f,
			(mObjectMenuUp + mObjectMenuDown) / 2.0f),
		mCreateStage->GetStage()->GetRectWidth(),
		mCreateStage->GetStage()->GetRectHeight());
		mPatrol->InitializeStageObject_CreateStage(mCreateStage);
		mPatrol->SetIsInObjectMenu(true);
		break;
	case StageObject::Attribute::TreasureChest:
		mTreasureChest = new TreasureChest(Vec2{ mObjectMenuLeft + mObjectEachWidth * 5 + mObjectEachWidth / 2.0f,
		(mObjectMenuUp + mObjectMenuDown) / 2.0f },
		mCreateStage->GetStage()->GetRectWidth(),
		mCreateStage->GetStage()->GetRectHeight());
		mTreasureChest->InitializeStageObject_CreateStage(mCreateStage);
		mTreasureChest->SetIsInObjectMenu(true);
		break;
	case StageObject::Attribute::Battery:
		mBattery = new Battery(Vec2(mObjectMenuLeft + mObjectEachWidth * 4 + mObjectEachWidth / 2.0f,
			(mObjectMenuUp + mObjectMenuDown) / 2.0f),
		mCreateStage->GetStage()->GetRectWidth(),
		mCreateStage->GetStage()->GetRectHeight());
		mBattery->InitializeStageObject_CreateStage(mCreateStage);
		mBattery->SetIsInObjectMenu(true);
		break;
	case StageObject::Attribute::Candle:
		mCandle = new Candle(Vec2(mObjectMenuLeft + mObjectEachWidth * 6 + mObjectEachWidth / 2.0f,
			(mObjectMenuUp + mObjectMenuDown) / 2.0f),
		 mCreateStage->GetStage()->GetRectWidth() / 3,
		 mCreateStage->GetStage()->GetRectHeight() / 3,
		 mCreateStage->GetStage()->GetRectHeight() / 6);
		mCandle->InitializeStageObject_CreateStage(mCreateStage);
		mCandle->SetIsInObjectMenu(true);
		break;
	}
}

void StageMenu::RemakePlayer(class StageObject* stageObject){
	switch (stageObject->GetAttribute()) {
	case StageObject::Attribute::Ghost:
		mGhost = new Ghost_CreateStage(Vec2(mPlayerPos.x,
			mPlayerPos.y + 2*mPlayerRectHeight), mPlayerRectWidth, mPlayerRectHeight
		);
		mGhost->InitializeStageObject_CreateStage(mCreateStage);
		mGhost->SetIsInObjectMenu(true);
		break;
	case StageObject::Attribute::Escapee1:
		mEscapee1 = new Escapee_CreateStage(Vec2(mPlayerPos.x - mPlayerRectWidth * 5.0f,
			mPlayerPos.y), mPlayerRectWidth, mPlayerRectHeight, 1);
		mEscapee1->InitializeStageObject_CreateStage(mCreateStage);
		mEscapee1->SetIsInObjectMenu(true);
		break;
	case StageObject::Attribute::Escapee2:
		mEscapee2 = new Escapee_CreateStage(Vec2(mPlayerPos.x,
			mPlayerPos.y), mPlayerRectWidth, mPlayerRectHeight, 2);
		mEscapee2->InitializeStageObject_CreateStage(mCreateStage);
		mEscapee2->SetIsInObjectMenu(true);
		break;
	case StageObject::Attribute::Escapee3:
		mEscapee3 = new Escapee_CreateStage(Vec2(mPlayerPos.x + mPlayerRectWidth * 5.0f,
			mPlayerPos.y), mPlayerRectWidth, mPlayerRectHeight, 3);
		mEscapee3->InitializeStageObject_CreateStage(mCreateStage);
		mEscapee3->SetIsInObjectMenu(true);
		break;
	}
}
