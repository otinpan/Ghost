#include"StageMenu.h"
#include"CreateStage.h"
#include"Stage.h"

StageMenu::StageMenu()
{

}

StageMenu::~StageMenu(){}

void StageMenu::Initialize_CreateStage(CreateStage* createStage) {
	mCreateStage = createStage;
	mMenuLeft = mCreateStage->GetStage()->GetLeft()
		+ mCreateStage->GetStage()->GetWidth() + 0.05;
	mMenuUp = mCreateStage->GetStage()->GetUp();

	mMenuWidth = 0.95 - mMenuLeft;
	mMenuHeight = mMenuUp - 1.0;

	mMenuPos = Vec2{ mMenuLeft + mMenuWidth / 2,mMenuUp - mMenuHeight / 2 };

	mMenuRect = RectF{ mMenuLeft,mMenuUp,mMenuWidth,mMenuHeight };
}

void StageMenu::Update_CreateStage(float deltaTime) {
	
}


void StageMenu::Draw_CreateStage() {
	DrawRectFrame(mMenuPos, mMenuWidth, mMenuHeight, 0.02, ColorF(1, 0, 0));
}
