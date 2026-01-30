#include"MainMenu.h"

MainMenu::MainMenu()
	:mSeqID(Parent::SEQ_NONE)
	,mIsRunning(true)
	,mSelect(MainSelect::SELECT_GAME)
{
	Initialize();
}

MainMenu::~MainMenu() {
	TextureAsset::Release(U"main_game");
	TextureAsset::Release(U"main_stage");
}

void MainMenu::Initialize() {
	Scene::SetBackground(ColorF(180.0 / 255.0));
	inputLeft = KeyA;
	inputUp = KeyW;
	inputDown = KeyS;
	inputRight = KeyD;
	inputDecision = KeySpace;
	inputBack = KeyBackspace;

	mCenterCirclePos = Vec2(0, 0);
	mCenterCircleRadius = 0.25f;
	mSelectHeight = 0.6f;
	mSelectWidth = 0.6f;
	mGameRectCenter = Vec2((float)mCenterCirclePos.x - mCenterCircleRadius - mSelectWidth / 1.8f, mCenterCircleRadius);
	mCreateStageRectCenter = Vec2((float)mCenterCirclePos.x + mCenterCircleRadius + mSelectWidth / 1.8f, mCenterCircleRadius);
	mSubMenuRectCenter = Vec2((float)mCenterCirclePos.x, mCenterCirclePos.y - mSelectHeight /1.4-mCenterCircleRadius);
	mRectRound = mSelectWidth / 30.0f;
	mGameRectColor = ColorF(204.0f / 255.0f, 0, 0);
	mCreateStageRectColor = ColorF(0, 102.0 / 255.0, 204.0 / 255.0);
	mSubMenuRectColor = ColorF(120.0 / 255.0);

	float fs = 0.12 * GetScreenHeight();
	int32 fontSize = (int32)fs;
	FontAsset::Register(U"SmallFont_MainMenu", fontSize, Typeface::Bold);
	fs *= (float)1.02;
	fontSize = (int32)fs;
	FontAsset::Register(U"LageFont_MainMenu", fontSize, Typeface::Bold);

	TextureAsset::Load(U"main_game");
	TextureAsset::Load(U"main_stage");
}

void MainMenu::update(Parent* parent) {
	if (mIsRunning) {
		ClearPrint();
		if (mSeqID != Parent::SEQ_NONE) {
			setMode(parent);
			moveTo(parent, mSeqID);
		}
		ProcessInput();
		UpdateMainMenu();
		draw();
	}
}

void MainMenu::ProcessInput() {

}

void MainMenu::UpdateMainMenu() {
	switch (mSelect) {
	case MainSelect::SELECT_GAME:
		if (inputRight.down()) {
			mSelect = MainSelect::SELECT_CREATESTAGE;
		}
		if (inputDown.down()) {
			mSelect = MainSelect::SELECT_SUBMENU;
		}
		break;
	case MainSelect::SELECT_CREATESTAGE:
		if (inputLeft.down()) {
			mSelect = MainSelect::SELECT_GAME;
		}
		if (inputDown.down()) {
			mSelect = MainSelect::SELECT_SUBMENU;
		}
		break;
	case MainSelect::SELECT_SUBMENU:
		if (inputUp.down() || inputLeft.down()) {
			mSelect = MainSelect::SELECT_GAME;
		}
		if (inputRight.down()) {
			mSelect = MainSelect::SELECT_CREATESTAGE;
		}
		break;
	}


	switch (mSelect) {
	case MainSelect::SELECT_GAME:
		if (inputDecision.down()) {
			mSeqID = Parent::SEQ_REGISTERCONTROLLER;
		}
		break;
	case MainSelect::SELECT_CREATESTAGE:
		if (inputDecision.down()) {
			mSeqID = Parent::SEQ_STAGESELECT;
		}
		break;
	case MainSelect::SELECT_SUBMENU:
		if (inputDecision.down()) {
			mSeqID = Parent::SEQ_SUBMENU;
		}
	}
}

void MainMenu::draw() {
	
	

	DrawCircle(mCenterCirclePos, mCenterCircleRadius, ColorF(1, 1, 1));
	DrawRoundRect(mGameRectCenter, mSelectWidth, mSelectHeight, mRectRound, mGameRectColor);
	DrawRoundRect(mCreateStageRectCenter, mSelectWidth, mSelectHeight, mRectRound, mCreateStageRectColor);
	DrawRoundRect(mSubMenuRectCenter, mSelectWidth, mSelectHeight, mRectRound, mSubMenuRectColor);

	if (mSelect == MainSelect::SELECT_GAME) {
		DrawTexture(TextureAsset(U"main_game"), Vec2(0.0f, 0.0f),
			mCenterCircleRadius*0.9f, mCenterCircleRadius*0.9f, 0.0f);
	}
	else if (mSelect == MainSelect::SELECT_CREATESTAGE) {
		DrawTexture(TextureAsset(U"main_stage"),Vec2(0.0f,0.0f),
			mCenterCircleRadius*0.9f , mCenterCircleRadius*0.9f , 0.0f);
	}

	switch (mSelect) {
	case MainSelect::SELECT_GAME:
		DrawRoundRectFrame(mGameRectCenter, mSelectWidth, mSelectHeight, mRectRound, 0, mSelectHeight / 40.0f, ColorF(1));
		break;
	case MainSelect::SELECT_CREATESTAGE:
		DrawRoundRectFrame(mCreateStageRectCenter, mSelectWidth, mSelectHeight, mRectRound, 0, mSelectHeight / 40.0f, ColorF(1));
		break;
	case MainSelect::SELECT_SUBMENU:
		DrawRoundRectFrame(mSubMenuRectCenter, mSelectWidth, mSelectHeight, mRectRound, 0, mSelectHeight / 40.0f, ColorF(1));
		break;
	}

	FontAsset(U"LargeFont_MainMenu")(U"Play").draw(Arg::center(ConvertToView(mGameRectCenter)), ColorF(0));
	FontAsset(U"SmallFont_MainMenu")(U"Play").draw(Arg::center(ConvertToView(mGameRectCenter)), ColorF(1));
	FontAsset(U"LargeFont_MainMenu")(U"Stage").draw(Arg::center(ConvertToView(mCreateStageRectCenter)), ColorF(0));
	FontAsset(U"SmallFont_MainMenu")(U"Stage").draw(Arg::center(ConvertToView(mCreateStageRectCenter)), ColorF(1));
	FontAsset(U"LargeFont_MainMenu")(U"Rule").draw(Arg::center(ConvertToView(mSubMenuRectCenter)), ColorF(0));
	FontAsset(U"SmallFont_MainMenu")(U"Rule").draw(Arg::center(ConvertToView(mSubMenuRectCenter)), ColorF(1));

}


void MainMenu::Shutdown() {

}


void MainMenu::moveTo(Parent* parent, Parent::SeqID id) {
	if (id == Parent::SEQ_MAINMENU)parent->moveTo(Parent::SEQ_MAINMENU, Parent::SEQ_MAINMENU);
	if (id == Parent::SEQ_STAGESELECT)parent->moveTo(Parent::SEQ_STAGESELECT, Parent::SEQ_MAINMENU);
	if (id == Parent::SEQ_REGISTERCONTROLLER)parent->moveTo(Parent::SEQ_REGISTERCONTROLLER, Parent::SEQ_MAINMENU);
	if (id == Parent::SEQ_GAME)parent->moveTo(Parent::SEQ_GAME,Parent::SEQ_MAINMENU);
	if (id == Parent::SEQ_CREATESTAGE)parent->moveTo(Parent::SEQ_CREATESTAGE,Parent::SEQ_MAINMENU);
	if (id == Parent::SEQ_GAMERESULT)parent->moveTo(Parent::SEQ_GAMERESULT, Parent::SEQ_MAINMENU);
	if (id == Parent::SEQ_CHANGEWINDOWSIZE)parent->moveTo(Parent::SEQ_CHANGEWINDOWSIZE, Parent::SEQ_MAINMENU);
	if (id == Parent::SEQ_SUBMENU)parent->moveTo(Parent::SEQ_SUBMENU, Parent::SEQ_MAINMENU);
}

void MainMenu::setMode(Parent* parent) {
	switch (mSelect){
	case SELECT_GAME:
		parent->setStageSelectGame(true);
		break;
	case SELECT_CREATESTAGE:
		parent->setStageSelectGame(false);
		break;
	default:
		parent->setStageSelectGame(true);
		break;
	}
}
