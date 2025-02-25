#include "StageSelect.h"

StageSelect::StageSelect()
	:mSeqID(Parent::SEQ_NONE)
	, mIsRunning(true)
{
	Initialize();
}

StageSelect::~StageSelect() {

}

void StageSelect::Initialize() {

}


void StageSelect::update(Parent* parent) {
	if (mIsRunning) {
		if (mSeqID != Parent::SEQ_NONE) {
			moveTo(parent, mSeqID);
		}
		ProcessInput();
		UpdateStageSelect();
		draw();
	}
}

void StageSelect::ProcessInput() {

}

void StageSelect::UpdateStageSelect() {
	float deltaTime = Scene::DeltaTime();
}

void StageSelect::draw() {

}

void StageSelect::Shutdown() {

}

void StageSelect::moveTo(Parent* parent, Parent::SeqID id) {
	if (id == Parent::SEQ_MAINMENU)parent->moveTo(Parent::SEQ_MAINMENU, Parent::SEQ_STAGESELECT);
	if (id == Parent::SEQ_STAGESELECT)parent->moveTo(Parent::SEQ_STAGESELECT, Parent::SEQ_STAGESELECT);
	if (id == Parent::SEQ_CREATESTAGE)parent->moveTo(Parent::SEQ_CREATESTAGE, Parent::SEQ_STAGESELECT);
	if (id == Parent::SEQ_GAME)parent->moveTo(Parent::SEQ_GAME, Parent::SEQ_STAGESELECT);
}
