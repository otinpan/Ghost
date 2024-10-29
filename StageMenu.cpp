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

StageMenu::StageMenu()
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
	i++;
	mDoor = new Door(Vec2(mObjectMenuLeft+mObjectEachWidth * i + mObjectEachWidth / 2.0f,
		(mObjectMenuUp + mObjectMenuDown) / 2.0f),
		mCreateStage->GetStage()->GetRectWidth(),
		mCreateStage->GetStage()->GetRectHeight());
	mDoor->InitializeStageObject_CreateStage(mCreateStage);
	i++;
	mPatrol = new Patrol(Vec2(mObjectMenuLeft+mObjectEachWidth * i + mObjectEachWidth / 2.0f,
		(mObjectMenuUp + mObjectMenuDown) / 2.0f),
		mCreateStage->GetStage()->GetRectWidth(),
		mCreateStage->GetStage()->GetRectHeight());
	mPatrol->InitializeStageObject_CreateStage(mCreateStage);
	i++;
	mKey = new Key(Vec2(mObjectMenuLeft+mObjectEachWidth * i + mObjectEachWidth / 2.0f,
		(mObjectMenuUp + mObjectMenuDown) / 2.0f),
		mCreateStage->GetStage()->GetRectWidth(),
		mCreateStage->GetStage()->GetRectHeight());
	mKey->InitializeStageObject_CreateStage(mCreateStage);
	i++;
	mBattery = new Battery(Vec2(mObjectMenuLeft+mObjectEachWidth * i + mObjectEachWidth / 2.0f,
		(mObjectMenuUp + mObjectMenuDown) / 2.0f),
		mCreateStage->GetStage()->GetRectWidth(),
		mCreateStage->GetStage()->GetRectHeight());
	mBattery->InitializeStageObject_CreateStage(mCreateStage);
	i++;
	mTreasureChest = new TreasureChest(Vec2{mObjectMenuLeft+ mObjectEachWidth * i + mObjectEachWidth / 2.0f,
		(mObjectMenuUp + mObjectMenuDown) / 2.0f },
		mCreateStage->GetStage()->GetRectWidth(),
		mCreateStage->GetStage()->GetRectHeight());
	mTreasureChest->InitializeStageObject_CreateStage(mCreateStage);
	i++;
	mCandle = new Candle(Vec2(mObjectMenuLeft+mObjectEachWidth * i + mObjectEachWidth / 2.0f,
		(mObjectMenuUp + mObjectMenuDown) / 2.0f),
		 mCreateStage->GetStage()->GetRectWidth() / 3,
	     mCreateStage->GetStage()->GetRectHeight() / 3,
		 mCreateStage->GetStage()->GetRectHeight() / 6);
	mCandle->InitializeStageObject_CreateStage(mCreateStage);
	

}

void StageMenu::Update_CreateStage(float deltaTime) {
	
}


void StageMenu::Draw_CreateStage() {
	DrawRectFrame(mObjectMenuPos, mObjectMenuWidth, mObjectMenuHeight, 0.003,0, ColorF(1, 1, 1));
	DrawRectFrame(mMenuPos, mMenuWidth, mMenuHeight, 0.003,0, ColorF(1, 1, 1));
	if (mCreateStage->GetHand()->GetIsChoose()) {
		mCreateStage->GetHand()->GetChoosing()->DrawStageMenu_CreateStage();
	}
}

RectF StageMenu::GetViewStageMenuRect() {
	return RectF(ConvertToView(
		Vec2{ mMenuLeft,mMenuUp }),
		GetScreenWidth() * mMenuWidth / 2.0f,
		GetScreenHeight() * mMenuHeight / 2.0f);
}
