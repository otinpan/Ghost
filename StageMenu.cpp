#include"StageMenu.h"
#include"CreateStage.h"
#include"Stage.h"
#include"Hand.h"

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
}

void StageMenu::Update_CreateStage(float deltaTime) {
	
}


void StageMenu::Draw_CreateStage() {
	DrawRectFrame(mMenuPos, mMenuWidth, mMenuHeight, 0.003, ColorF(0, 0, 0));
}
