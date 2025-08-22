#include "StageSelect.h"
#include "Parent.h"
using namespace std;

StageSelect::StageSelect()
	:mSeqID(Parent::SEQ_NONE)
	, mIsRunning(true)
{
	Initialize_CreateStage();
}

StageSelect::~StageSelect() {

}

void StageSelect::Initialize_CreateStage() {
	Scene::SetBackground(ColorF(200.0f / 255.0f));

	inputUp = KeyW;
	inputDown = KeyS;
	inputRight = KeyD;
	inputLeft = KeyA;
	inputDecision = KeySpace;
	inputBack = KeyBackspace;

	mIsinputUp = true;
	mIsinputDown = true;
	mIsinputRight = true;
	mIsinputLeft = true;

	mSideSize = 3;
	mVerticalSize = 20;

	mStageNames.resize(mVerticalSize);
	for (auto& row : mStageNames) {
		row.resize(mSideSize);
		for (auto& name : row) {
			name = U"";
		}
	}

	mStageTextures.resize(mVerticalSize);
	for (auto& row : mStageTextures) {
		row.resize(mSideSize);
		for (auto& texture : row) {
			texture = Texture(U"Stage/NoImage.png");
		}
	}

	mStagePoses.resize(mVerticalSize);
	for (auto& row : mStagePoses) {
		row.resize(mSideSize);
		for (auto& pos : row) {
			pos = Vec2(0, 0);
		}
	}

	mIsInStage.resize(mVerticalSize);
	for (auto& row : mIsInStage) {
		row.resize(mSideSize);
	}



	mStageLeft = -0.9;
	mStageRight = 0.9;
	mStageUp = 0.5;
	mStageDown = -0.9;
	mDisplayVerticalSize = 2;
	mDisplaySideSize = mSideSize;
	mStageWidth = (float)(mStageRight - mStageLeft);
	mStageHeight = (float)(mStageUp - mStageDown);
	mStageEachWidth = (float)mStageWidth / mDisplaySideSize;
	mStageEachHeight = (float)mStageHeight / mDisplayVerticalSize;
	mStageRectWidth = mStageEachWidth * 3.0 / 4.0;
	mStageRectHeight = mStageEachHeight * 3.0 / 4.0;

	mTopPos = 0.0f;
	MaxTopPos = mStageEachHeight * (mVerticalSize-3);
	MaxDownPos = MaxTopPos + 2.0f;

	minputUpTime = minputDownTime = minputRightTime = minputLeftTime = 0.0f;
	mIsinputUp = mIsinputDown = mIsinputRight = mIsinputLeft = true;

	//SideBar
	SideBarUp = 0.9f;
	SideBarDown = -0.9;
	mSideBarHeight = 2.0f / MaxDownPos * (SideBarUp - SideBarDown);
	mSideBarWidth = 0.03f;

	//ステージ作成の位置
	CreateStageRectPos = Vec2(mStageRight - mStageRectWidth*3/4 , mStageUp + mStageRectHeight/2);
	CreateStageRectSize = Vec2(mStageRectWidth/1.3f, mStageRectHeight/1.3f);

	RemakeStageVector();
}

bool StageSelect::InitializeStages() {
	return true;
}

void StageSelect::update(Parent* parent) {
	if (mIsRunning) {
		ClearPrint();
		Print << MaxDownPos;
		if (mSeqID != Parent::SEQ_NONE) {
			moveTo(parent, mSeqID);
		}
		ProcessInput();
		UpdateStageSelect_CreateStage();
		draw_CreateStage();
	}
}

void StageSelect::ProcessInput() {

}

void StageSelect::UpdateStageSelect_CreateStage() {
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
		mIsinputUp = true;
		minputUpTime = 0.0f;
	}
	if (inputUp.pressed()) {
		if (!mIsinputUp) {
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
		UpdateinputCooltime(mIsinputUp, minputUpTime, deltaTime);
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
		mIsinputDown = true;
		minputDownTime = 0.0f;
		
	}
	if (inputDown.pressed()) {
		if (!mIsinputDown) {
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
		UpdateinputCooltime(mIsinputDown, minputDownTime, deltaTime);

	}
	if (inputRight.down()) {
		if (mIteration.second < mSideSize - 1) mIteration.second++;
		mIsinputRight = true;
		minputRightTime = 0.0f;
	}
	if (inputRight.pressed()) {
		if (!mIsinputRight) {
			if (mIteration.second < mSideSize - 1) mIteration.second++;
		}
		UpdateinputCooltime(mIsinputRight, minputRightTime, deltaTime);
	}

	if (inputLeft.down()) {
		if (mIteration.second > 0)mIteration.second--;
		mIsinputLeft = true;
		minputLeftTime = 0.0f;
	}
	if (inputLeft.pressed()) {
		if (!mIsinputLeft) {
			if (mIteration.second > 0)mIteration.second--;
		}
		UpdateinputCooltime(mIsinputLeft, minputLeftTime, deltaTime);
	}

	//SideBar
	mSideBarUp = SideBarUp-(float)mTopPos / MaxDownPos * (SideBarUp-SideBarDown);
	mSideBarPos = Vec2(0.9, mSideBarUp - mSideBarHeight / 2.0f);
}


void StageSelect::UpdateRectPos(int plus) {
	for (int i = 0; i < mVerticalSize; i++) {
		for (int j = 0; j < mSideSize; j++) {
			mStagePoses[i][j].y += plus * mStageEachHeight;
		}
	}
	mTopPos += plus * mStageEachHeight;

	mUpLine+=plus;
	mDownLine+=plus;
	mUpLine = max(0, mUpLine);
	mUpLine = min(mVerticalSize - 1, mUpLine);
	mDownLine = max(0, mDownLine);
	mDownLine = min(mVerticalSize - 1, mDownLine);
}


void StageSelect::UpdateinputCooltime(bool &mIsinput, float &minputTime, float deltaTime) {
	if (mIsinput) {
		if (minputTime > 0.3f) {
			mIsinput = false;
			minputTime = 0.0f;
			return;
		}
		else {
			minputTime += deltaTime;
			return;
		}
	}
	else {
		mIsinput = true;
		return;
	}
}

void StageSelect::draw_CreateStage() {
	for (int i = 0; i < mVerticalSize; i++) {
		for (int j = 0; j < mSideSize; j++) {
			DrawRect(mStagePoses[i][j], mStageRectWidth, mStageRectHeight, ColorF((float)i/mVerticalSize));
			if (mIsInStage[i][j]) {
				RectF(
					Arg::center(ConvertToView(mStagePoses[i][j]))
					, GetScreenWidth() * mStageRectWidth / 2.0f
					, GetScreenHeight() * mStageRectHeight / 2.0f
				)(mStageTextures[i][j]).draw();
			
			}

		}
	}
	DrawRoundRect(mSideBarPos, mSideBarWidth, mSideBarHeight,mSideBarWidth/4.0f, ColorF(1, 1, 1));
	DrawRectFrame(mStagePoses[mIteration.first][mIteration.second], mStageRectWidth, mStageRectHeight, 0, 0.005, ColorF(1, 1, 0));

	// ステージ作成の選択
	DrawRect(CreateStageRectPos, CreateStageRectSize.x, CreateStageRectSize.y, ColorF(0.5f, 0.5f, 0.5f));


}

void StageSelect::UpdateStageSelect_Game() {

}

void StageSelect::draw_Game() {

}

void StageSelect::Shutdown() {

}

void StageSelect::moveTo(Parent* parent, Parent::SeqID id) {
	if (id == Parent::SEQ_MAINMENU)parent->moveTo(Parent::SEQ_MAINMENU, Parent::SEQ_STAGESELECT);
	if (id == Parent::SEQ_STAGESELECT)parent->moveTo(Parent::SEQ_STAGESELECT, Parent::SEQ_STAGESELECT);
	if (id == Parent::SEQ_CREATESTAGE)parent->moveTo(Parent::SEQ_CREATESTAGE, Parent::SEQ_STAGESELECT);
	if (id == Parent::SEQ_GAME)parent->moveTo(Parent::SEQ_GAME, Parent::SEQ_STAGESELECT);
	if (id == Parent::SEQ_GAMERESULT)parent->moveTo(Parent::SEQ_GAMERESULT, Parent::SEQ_STAGESELECT);
	if (id == Parent::SEQ_CHANGEWINDOWSIZE)parent->moveTo(Parent::SEQ_CHANGEWINDOWSIZE, Parent::SEQ_STAGESELECT);
}

void StageSelect::RemakeStageVector() {
	std::vector<String> stageNames;
	{
		Deserializer<BinaryReader> reader{ U"Stage/StageNames.bin" };
		if (reader) {
			reader(stageNames);
		}
		else {
			stageNames.clear();

		}
	}

	const Texture noImage{ U"Stage/NoImage.png" };

	for (int i = 0; i < mVerticalSize; i++) {
		for (int j = 0; j < mSideSize; j++) {
			mStagePoses[i][j] = Vec2(mStageLeft + mStageEachWidth * j + mStageRectWidth / 2.0f,
				mStageUp - mStageEachHeight * i - mStageRectHeight / 2.0f);
			int idx = i * mSideSize + j;
			if (stageNames.size() > idx) {
				const auto& name = stageNames[idx];
				mStageNames[i][j] = name;
				const FilePath path = U"Stage/" + name + U"/Image.png";
				if (FileSystem::Exists(path)) {
					mStageTextures[i][j] = Texture(path);
					mIsInStage[i][j] = true;
				}
				else {
					mStageTextures[i][j] = noImage;
					mIsInStage[i][j] = false;
				}
			}
			else {
				mStageNames[i][j] = U"";
				mIsInStage[i][j] = false;
				mStageTextures[i][j] = noImage;
			}

		}
	}

	// 初期化
	mIteration = pair(0, 0); 
	mUpLine = 0;
	mDownLine = mDisplayVerticalSize - 1;
}
