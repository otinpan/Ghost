#include"RegisterController.h"

RegisterController::RegisterController()
	:mSeqID(Parent::SEQ_NONE)
	, mIsRunning(true)
{
	Initialize();
}


RegisterController::~RegisterController() {

}


void RegisterController::Initialize() {
	Scene::SetBackground(ColorF(0.9f));
}

void RegisterController::update(Parent* parent) {
	if (mIsRunning) {
		if (mSeqID != Parent::SEQ_NONE) {
			moveTo(parent, mSeqID);
		}
	}

	ClearPrint();
	ProcessInput();
	UpdateRegisterController();
	draw();
}

void RegisterController::ProcessInput() {

}

void RegisterController::UpdateRegisterController() {
	float deltaTime = Scene::DeltaTime();

	if (KeySpace.down()||KeyRight.down()) {
		mSeqID = Parent::SEQ_STAGESELECT;
		return;
	}


	if (KeyBackspace.down() || KeyLeft.down()) {
		mSeqID = Parent::SEQ_MAINMENU;
		return;
	}

	if (const auto joy = JoyConL(0)) {

	}

}


void RegisterController::draw() {

}


void RegisterController::Shutdown() {

}

void RegisterController::moveTo(Parent* parent, Parent::SeqID id) {
	if (id == Parent::SEQ_MAINMENU)parent->moveTo(Parent::SEQ_MAINMENU, Parent::SEQ_REGISTERCONTROLLER);
	if (id == Parent::SEQ_STAGESELECT) {
		parent->setStageSelectGame(true);
		parent->moveTo(Parent::SEQ_STAGESELECT, Parent::SEQ_REGISTERCONTROLLER);
	}
	if (id == Parent::SEQ_GAME)parent->moveTo(Parent::SEQ_GAME, Parent::SEQ_REGISTERCONTROLLER);
	if (id == Parent::SEQ_CREATESTAGE)parent->moveTo(Parent::SEQ_CREATESTAGE, Parent::SEQ_REGISTERCONTROLLER);
	if (id == Parent::SEQ_GAMERESULT)parent->moveTo(Parent::SEQ_GAMERESULT, Parent::SEQ_REGISTERCONTROLLER);
	if (id == Parent::SEQ_CHANGEWINDOWSIZE)parent->moveTo(Parent::SEQ_CHANGEWINDOWSIZE, Parent::SEQ_REGISTERCONTROLLER);
}
