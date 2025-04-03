#include"MainMenu.h"

MainMenu::MainMenu()
	:mSeqID(Parent::SEQ_NONE)
	,mIsRunning(true)
	,mSelect(MainMenu::SelectGame)
{
	Initialize();
}

MainMenu::~MainMenu() {

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
	mCenterCircleRadius = 0.2f;
	mSelectHeight = 0.7f;
	mSelectWidth = 0.7f;
	mGameRectCenter = Vec2((float)mCenterCirclePos.x - mCenterCircleRadius - mSelectWidth / 2.15f, 0.0);
	mCreateStageRectCenter = Vec2((float)mCenterCirclePos.x + mCenterCircleRadius + mSelectWidth / 2.15f, 0.0);
	mRectRound = mSelectWidth / 30.0f;
	mGameRectColor = ColorF(204.0f / 255.0f, 0, 0);
	mCreateStageRectColor = ColorF(0, 102.0 / 255.0, 204.0 / 255.0);

	float fs= 0.15*GetMagnification();
	int32 fontSize = (int32)fs;
	fontWhite=Font( fontSize,Typeface::Bold );
	fs *= (float)1.02;
	fontSize = (int32)fs;
	fontBlack = Font{ fontSize,Typeface::Bold };
}

void MainMenu::update(Parent* parent) {
	if (mIsRunning) {
		if (mSeqID != Parent::SEQ_NONE) {
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
	case MainSelect::SelectGame:
		if (inputRight.down()) {
			mSelect = MainSelect::SelectCreateStage;
		}
		break;
	case MainSelect::SelectCreateStage:
		if (inputLeft.down()) {
			mSelect = MainSelect::SelectGame;
		}
		break;
	}
}

void MainMenu::draw() {
	DrawCircle(mCenterCirclePos, mCenterCircleRadius, ColorF(1, 1, 1));
	DrawRoundRect(mGameRectCenter, mSelectWidth, mSelectHeight, mRectRound, mGameRectColor);
	DrawRoundRect(mCreateStageRectCenter, mSelectWidth, mSelectHeight, mRectRound, mCreateStageRectColor);

	switch (mSelect) {
	case MainSelect::SelectGame:
		DrawRoundRectFrame(mGameRectCenter, mSelectWidth, mSelectHeight, mRectRound, 0, mSelectHeight / 40.0f, ColorF(1));
		break;
	case MainSelect::SelectCreateStage:
		DrawRoundRectFrame(mCreateStageRectCenter, mSelectWidth, mSelectHeight, mRectRound, 0, mSelectHeight / 40.0f, ColorF(1));
		break;
	}

	fontBlack(U"あそぶ").draw(Arg::center(ConvertToView(mGameRectCenter)), ColorF(0));
	fontWhite(U"あそぶ").draw(Arg::center(ConvertToView(mGameRectCenter)), ColorF(1));
	fontBlack(U"ステージ").draw(Arg::center(ConvertToView(mCreateStageRectCenter)), ColorF(0));
	fontWhite(U"ステージ").draw(Arg::center(ConvertToView(mCreateStageRectCenter)), ColorF(1));
	
}


void MainMenu::Shutdown() {

}


void MainMenu::moveTo(Parent* parent, Parent::SeqID id) {
	if (id == Parent::SEQ_MAINMENU)parent->moveTo(Parent::SEQ_MAINMENU, Parent::SEQ_MAINMENU);
	if (id == Parent::SEQ_STAGESELECT)parent->moveTo(Parent::SEQ_STAGESELECT, Parent::SEQ_MAINMENU);
	if (id == Parent::SEQ_GAME)parent->moveTo(Parent::SEQ_GAME,Parent::SEQ_MAINMENU);
	if (id == Parent::SEQ_CREATESTAGE)parent->moveTo(Parent::SEQ_CREATESTAGE,Parent::SEQ_MAINMENU);
	if (id == Parent::SEQ_GAMERESULT)parent->moveTo(Parent::SEQ_GAMERESULT, Parent::SEQ_MAINMENU);
}
