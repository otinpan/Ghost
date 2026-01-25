#include"GameResult.h"

GameResult::GameResult(Parent::GameJudgement judge)
	:mSeqID(Parent::SEQ_NONE)
	, mIsRunning(true)
	, mGameJudgement(judge)
	, mResultSelect(ResultSelect::STAGE_SELECT)
{
	Initialize();
}

GameResult::~GameResult() {

}

void GameResult::Initialize() {
	Scene::SetBackground(ColorF(0.95));
	inputRight = KeyD;
	inputLeft = KeyA;
	inputR = KeyRight;
	inputL = KeyLeft;
	inputDecision = KeySpace;
}

void GameResult::update(Parent* parent) {
	if (mIsRunning) {
		if (mSeqID != Parent::SEQ_NONE) {
			moveTo(parent, mSeqID);
		}
	}
	ClearPrint();
	ProcessInput();
	UpdateGameResult();
	draw();
}

void GameResult::ProcessInput() {

}

void GameResult::UpdateGameResult() {
	float deltaTime = Scene::DeltaTime();

	ClearPrint();
	Print << mResultSelect;
	switch (mResultSelect) {
	case ResultSelect::STAGE_SELECT:
		if (inputRight.down() || inputR.down()) {
			mResultSelect = ResultSelect::CONTROLLER_SELECT;
		}
		if (inputDecision.down()) {
			SetSeqID(Parent::SeqID::SEQ_STAGESELECT);
			IsJumpToGame = true;
		}
		break;
	case ResultSelect::CONTROLLER_SELECT:
		if (inputLeft.down() || inputL.down()) {
			mResultSelect = ResultSelect::STAGE_SELECT;
		}
		if (inputRight.down() || inputR.down()) {
			mResultSelect = ResultSelect::MAIN_MENU;
		}
		if (inputDecision.down()) {
			SetSeqID(Parent::SeqID::SEQ_REGISTERCONTROLLER);
		}
		break;
	case ResultSelect::MAIN_MENU:
		if (inputLeft.down() || inputL.down()) {
			mResultSelect = ResultSelect::CONTROLLER_SELECT;
		}
		if (inputRight.down() || inputR.down()) {
			mResultSelect = ResultSelect::CREATE_STAGE;
		}
		if (inputDecision.down()) {
			SetSeqID(Parent::SeqID::SEQ_MAINMENU);
		}
		break;
	case ResultSelect::CREATE_STAGE:
		if (inputLeft.down() || inputL.down()) {
			mResultSelect = ResultSelect::MAIN_MENU;
		}
		if (inputDecision.down()) {
			SetSeqID(Parent::SeqID::SEQ_STAGESELECT);
			IsJumpToGame = false;
		}
	}
}

void GameResult::draw() {
	Print << mGameJudgement;
}

void GameResult::Shutdown() {

}

void GameResult::moveTo(Parent* parent, Parent::SeqID id) {
	if (id == Parent::SEQ_MAINMENU)parent->moveTo(Parent::SEQ_MAINMENU, Parent::SEQ_GAMERESULT);
	if (id == Parent::SEQ_STAGESELECT) {
		parent->setStageSelectGame(IsJumpToGame);
		parent->moveTo(Parent::SEQ_STAGESELECT, Parent::SEQ_GAMERESULT);
	}
	if (id == Parent::SEQ_REGISTERCONTROLLER)parent->moveTo(Parent::SEQ_REGISTERCONTROLLER, Parent::SEQ_GAMERESULT);
	if (id == Parent::SEQ_CREATESTAGE)parent->moveTo(Parent::SEQ_CREATESTAGE, Parent::SEQ_GAMERESULT);
	if (id == Parent::SEQ_GAME)parent->moveTo(Parent::SEQ_GAME, Parent::SEQ_GAMERESULT);
	if (id == Parent::SEQ_GAMERESULT)parent->moveTo(Parent::SEQ_GAMERESULT, Parent::SEQ_GAMERESULT);
	if (id == Parent::SEQ_CHANGEWINDOWSIZE)parent->moveTo(Parent::SEQ_CHANGEWINDOWSIZE, Parent::SEQ_GAMERESULT);
}
