#include"GameResult.h"

GameResult::GameResult(Parent::GameJudgement judge)
	:mSeqID(Parent::SEQ_NONE)
	, mIsRunning(true)
	, mGameJudgement(judge)
{
	Initialize();
}

GameResult::~GameResult() {

}

void GameResult::Initialize() {
	Scene::SetBackground(ColorF(0.95));
	mTextMenu = std::make_unique<TextMenu>(U"text");
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
	if (mTextMenu)mTextMenu->Update(deltaTime);
}

void GameResult::draw() {
	Print << mGameJudgement;
}

void GameResult::Shutdown() {

}

void GameResult::moveTo(Parent* parent, Parent::SeqID id) {
	if (id == Parent::SEQ_MAINMENU)parent->moveTo(Parent::SEQ_MAINMENU, Parent::SEQ_GAMERESULT);
	if (id == Parent::SEQ_STAGESELECT)parent->moveTo(Parent::SEQ_STAGESELECT, Parent::SEQ_GAMERESULT);
	if (id == Parent::SEQ_CREATESTAGE)parent->moveTo(Parent::SEQ_CREATESTAGE, Parent::SEQ_GAMERESULT);
	if (id == Parent::SEQ_GAME)parent->moveTo(Parent::SEQ_GAME, Parent::SEQ_GAMERESULT);
	if (id == Parent::SEQ_GAMERESULT)parent->moveTo(Parent::SEQ_GAMERESULT, Parent::SEQ_GAMERESULT);
	if (id == Parent::SEQ_CHANGEWINDOWSIZE)parent->moveTo(Parent::SEQ_CHANGEWINDOWSIZE, Parent::SEQ_GAMERESULT);
}
