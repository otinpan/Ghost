#include "StageSelect.h"
using namespace std;

StageSelect::StageSelect()
	:mSeqID(Parent::SEQ_NONE)
	, mIsRunning(true)
{
	Initialize();
}

StageSelect::~StageSelect() {

}

void StageSelect::Initialize() {
	Scene::SetBackground(ColorF(200.0f / 255.0f));

	inputUp = KeyW;
	inputDown = KeyS;
	inputRight = KeyD;
	inputLeft = KeyA;
	inputDecision = KeySpace;
	inputBack = KeyBackspace;

	mSideSize = 3;
	mVerticalSize = 20;

	mStageNames.resize(mVerticalSize);
	for (auto& row : mStageNames) {
		row.resize(mSideSize);
		for (auto& name : row) {
			name = "";
		}
	}

	mStagePoses.resize(mVerticalSize);
	for (auto& row : mStagePoses) {
		row.resize(mSideSize);
		for (auto& pos : row) {
			pos = Vec2(0, 0);
		}
	}

	mStageLeft = -0.9;
	mStageRight = 0.9;
	mStageUp = 0.9;
	mStageDown = -0.9;
	mDisplayVerticalSize = 3;
	mDisplaySideSize = mSideSize;
	mStageWidth = (float)(mStageRight - mStageLeft);
	mStageHeight = (float)(mStageUp - mStageDown);
	mStageEachWidth = (float)mStageWidth / mDisplaySideSize;
	mStageEachHeight = (float)mStageHeight / mDisplayVerticalSize;
	mStageRectWidth = mStageEachWidth * 2.0 / 3.0;
	mStageRectHeight = mStageEachHeight * 2.0 / 3.0;

	//初期位置の設定
	for (int i = 0; i < mVerticalSize; i++) {
		for (int j = 0; j < mSideSize; j++) {
			mStagePoses[i][j] = Vec2(mStageLeft+mStageEachWidth * j + mStageEachWidth / 2.0f,
				mStageUp-mStageEachHeight * i - mStageEachHeight / 2.0f);
		}
	}

	mIteration = pair(0, 0);
	mUpLine = 0;
	mDownLine = mDisplayVerticalSize-1;
}


void StageSelect::update(Parent* parent) {
	if (mIsRunning) {
		ClearPrint();
		Print << mIteration;
		Print << mUpLine;
		Print << mDownLine;
		if (mSeqID != Parent::SEQ_NONE) {
			moveTo(parent, mSeqID);
		}
		ProcessInput();
		UpdateStageSelect_Game();
		draw_Game();
	}
}

void StageSelect::ProcessInput() {

}

void StageSelect::UpdateStageSelect_Game() {
	float deltaTime = Scene::DeltaTime();
	if (inputUp.down()) {
		if (mIteration.first != mUpLine) { //表示の一番上以外の行
			mIteration.first--;
		}
		else {
			if (mUpLine > 0) {
				mIteration.first--;
				UpdateRectPos(-1);
			}
		}
	}
	if (inputDown.down()) {
		if (mIteration.first != mDownLine) {
			mIteration.first++;
		}
		else {
			if (mDownLine < mVerticalSize - 1) {
				mIteration.first++;
				UpdateRectPos(1);
			}
		}
	}
	if (inputRight.down()) {
		if (mIteration.second < mSideSize - 1) mIteration.second++;
	}
	if (inputLeft.down()) {
		if (mIteration.second > 0)mIteration.second--;
	}
}

void StageSelect::UpdateStageSelect_CreateStage() {
	float deltaTime = Scene::DeltaTime();
}

void StageSelect::UpdateRectPos(int plus) {
	for (int i = 0; i < mVerticalSize; i++) {
		for (int j = 0; j < mSideSize; j++) {
			mStagePoses[i][j].y += plus * mStageEachHeight;
		}
	}
	mUpLine+=plus;
	mDownLine+=plus;
	mUpLine = max(0, mUpLine);
	mUpLine = min(mVerticalSize - 1, mUpLine);
	mDownLine = max(0, mDownLine);
	mDownLine = min(mVerticalSize - 1, mDownLine);
}

void StageSelect::draw_Game() {
	for (int i = 0; i < mVerticalSize; i++) {
		for (int j = 0; j < mSideSize; j++) {
			DrawRect(mStagePoses[i][j], mStageRectWidth, mStageRectHeight, ColorF((float)i/mVerticalSize));
		}
	}

	DrawRectFrame(mStagePoses[mIteration.first][mIteration.second], mStageRectWidth, mStageRectHeight, 0, 0.005, ColorF(1, 1, 0));
}

void StageSelect::draw_CreateStage() {

}

void StageSelect::Shutdown() {

}

void StageSelect::moveTo(Parent* parent, Parent::SeqID id) {
	if (id == Parent::SEQ_MAINMENU)parent->moveTo(Parent::SEQ_MAINMENU, Parent::SEQ_STAGESELECT);
	if (id == Parent::SEQ_STAGESELECT)parent->moveTo(Parent::SEQ_STAGESELECT, Parent::SEQ_STAGESELECT);
	if (id == Parent::SEQ_CREATESTAGE)parent->moveTo(Parent::SEQ_CREATESTAGE, Parent::SEQ_STAGESELECT);
	if (id == Parent::SEQ_GAME)parent->moveTo(Parent::SEQ_GAME, Parent::SEQ_STAGESELECT);
}
