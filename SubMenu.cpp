#include"SubMenu.h"

SubMenu::SubMenu()
	:mSeqID(Parent::SEQ_NONE)
	, mIsRunning(true)
	, mSelect(SubMenu::SelectChangeWindowSize)
{
	Initialize();
}

SubMenu::~SubMenu() {
	Shutdown();
}

void SubMenu::Initialize() {
	Scene::SetBackground(ColorF(180.0 / 255.0));
	inputLeft = KeyA;
	inputUp = KeyW;
	inputDown = KeyS;
	inputRight = KeyD;
	inputDecision = KeySpace;
	inputBack = KeyBackspace;

	mUp = mSelectUp = 0.95;
	mLeft = mSelectLeft = -0.95;
	mWidth = mHeight=mSelectHeight=0.95 * 2.0;
	mSelectWidth = 0.6;

	mSelectRectWidth = mSelectWidth * 0.80;
	mSelectRectHeight = mSelectHeight / 12.0;
	mChangeWindowSizeRectCenter = Vec2(mSelectLeft + mSelectRectWidth / 2.0, mSelectUp - mSelectRectWidth / 2.0);
	mSelectRectRound = mSelectWidth / 35.0f;
	mSelectRectColor = ColorF(1.0);

	float fs = mSelectRectHeight * GetScreenHeight() * 0.25;
	int32 fontSize = (int32)fs;
	Print << fontSize;
	FontAsset::Register(U"Font_SubMenu", fontSize, Typeface::Medium);
}

void SubMenu::update(Parent* parent) {
	if (mIsRunning) {
		if (mSeqID != Parent::SEQ_NONE) {
			moveTo(parent, mSeqID);
		}
		ProcessInput();
		UpdateSubMenu();
		draw();
	}
}

void SubMenu::ProcessInput() {

}

void SubMenu::UpdateSubMenu() {
	if (inputDecision.down()) {
		mSeqID=Parent::SEQ_CHANGEWINDOWSIZE;
	}
	if (inputBack.down()) {
		mSeqID = Parent::SEQ_MAINMENU;
	}

}


void SubMenu::draw() {
	DrawRoundRect(mChangeWindowSizeRectCenter, mSelectRectWidth, mSelectRectHeight, mSelectRectRound, mSelectRectColor);
	switch (mSelect) {
	case SubSelect::SelectChangeWindowSize:
		DrawRoundRectFrame(mChangeWindowSizeRectCenter, mSelectRectWidth, mSelectRectHeight
			, mSelectRectRound, 0, mSelectRectHeight / 40.0f, ColorF(0));
		break;
	}
	FontAsset(U"Font_SubMenu")(U"windowサイズの変更").draw(Arg::center(ConvertToView(mChangeWindowSizeRectCenter)), ColorF(0));
}

void SubMenu::Shutdown() {

}

void SubMenu::moveTo(Parent* parent, Parent::SeqID id) {
	if (id == Parent::SEQ_MAINMENU)parent->moveTo(Parent::SEQ_MAINMENU, Parent::SEQ_SUBMENU);
	if (id == Parent::SEQ_STAGESELECT)parent->moveTo(Parent::SEQ_STAGESELECT, Parent::SEQ_SUBMENU);
	if (id == Parent::SEQ_SUBMENU)parent->moveTo(Parent::SEQ_SUBMENU, Parent::SEQ_SUBMENU);
	if (id == Parent::SEQ_GAME)parent->moveTo(Parent::SEQ_GAME, Parent::SEQ_SUBMENU);
	if (id == Parent::SEQ_CREATESTAGE)parent->moveTo(Parent::SEQ_CREATESTAGE, Parent::SEQ_SUBMENU);
	if (id == Parent::SEQ_GAMERESULT)parent->moveTo(Parent::SEQ_GAMERESULT, Parent::SEQ_SUBMENU);
	if (id == Parent::SEQ_CHANGEWINDOWSIZE)parent->moveTo(Parent::SEQ_CHANGEWINDOWSIZE, Parent::SEQ_SUBMENU);
}
