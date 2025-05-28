#include"CreateStage.h"
#include"Stage.h"
#include"StageObject.h"
#include"Brock.h"
#include"Wall.h"
#include"Hand.h"
#include"Door.h"
#include"Patrol.h"
#include"Key.h"
#include"Battery.h"
#include"Candle.h"
#include"TreasureChest.h"
#include"Ghost_CreateStage.h"
#include"Escapee_CreateStage.h"
#include"StageMenu.h"
#include<cmath>
#include"Player.h"
using namespace std;


Stage::Stage(float width, float height)
	:mVerticalSize(15)
	, mSideSize(22)
	, mWidth(width)
	, mHeight(height)
	, mLeft(-0.96f)
	, mUp(0.96f)
	, mExpandFulcrumPos{ Vec2{2.0,2.0} }
	, mExpandAttribute{ StageObject::Attribute::Wall }
	,mExpandRectCenter({0,0})
	,mExpandRectWidth(0.0f)
	,mExpandRectHeight(0.0f)
	,mDeleteRectCenter({0,0})
	,mDeleteRectWidth(0.0f)
	,mDeleteRectHeight(0.0f)
	,mIsSaveError(false)
	,mGameTime(0.0f)
	,GameLimitTime(180.0f)
	,GoalTime(1.0f)
	,mIsGoal(false)
{
	mRectWidth = mWidth / mSideSize;
	mRectHeight = mHeight / mVerticalSize;

}

Stage::~Stage() {
	for (int i = 0; i < mVerticalSize; i++) {
		for (int j = 0; j < mSideSize; j++) {
			if (mStageObjects[i][j] == 0)continue;
			delete mStageObjects[i][j];
			mStageObjects[i][j] = 0;
		}
	}
	for (int i = 0; i < mCandles.size(); i++) {
		if (mCandles[i] == 0)continue;
		delete mCandles[i];
		mCandles[i] = 0;
	}
	delete mCreateStage;
	mCreateStage = 0;
}

void Stage::Initialize_CreateStage(CreateStage* createStage) {
	mStageObjects.resize(mVerticalSize);
	for (auto& row : mStageObjects) {
		row.resize(mSideSize);
		for (auto& so : row) {
			so = 0;
		}
	}

	mCandles.assign(30,0);


	mRects.resize(mVerticalSize);
	for (auto& row : mRects) {
		row.resize(mSideSize);
	}

	mCanBeGone.resize(mVerticalSize);
	for (auto& row : mCanBeGone) {
		row.resize(mSideSize);
	}

	mGhostCanBeGone.resize(mVerticalSize);
	for (auto& row : mGhostCanBeGone) {
		row.resize(mSideSize);
	}

	mEscapee1CanBeGone.resize(mVerticalSize);
	for (auto& row : mEscapee1CanBeGone) {
		row.resize(mSideSize);
	}

	mEscapee2CanBeGone.resize(mVerticalSize);
	for (auto& row : mEscapee2CanBeGone) {
		row.resize(mSideSize);
	}

	mEscapee3CanBeGone.resize(mVerticalSize);
	for (auto& row : mEscapee3CanBeGone) {
		row.resize(mSideSize);
	}

	

	//mRectsの初期設定
	for (int i = 0; i < mVerticalSize; i++) {
		for (int j = 0; j < mSideSize; j++) {
			mRects[i][j] = RectF({ mLeft + mRectWidth * j,mUp - mRectHeight * (i+1)},
				mRectWidth, mRectHeight);
		}
	}

	mCreateStage = createStage;
	mStageRect = RectF({ mLeft,mUp }, mWidth, mHeight);

	//SaveError
	mSaveErrorRectWidth = 1.0;
	mSaveErrorRectHeight = 0.5;
	mSaveErrorPos = Vec2(0.0, 0.0);

}

void Stage::SetNewStageObject(int i, int j, StageObject* stageObject) {
	if (stageObject->GetAttribute() == StageObject::Attribute::Brock) {
		mStageObjects[i][j] = new Brock(Vec2({ (float)mLeft + j * mRectWidth + mRectWidth / 2,
		(float)mUp - (i+1) * mRectHeight + mRectHeight / 2 }), mRectWidth, mRectHeight);
	}
	else if (stageObject->GetAttribute() == StageObject::Attribute::Door) {
		mStageObjects[i][j]=new Door(Vec2({ (float)mLeft + j * mRectWidth + mRectWidth / 2,
		(float)mUp - (i+1) * mRectHeight + mRectHeight / 2 }),mRectWidth, mRectHeight);
	}
	else if (stageObject->GetAttribute() == StageObject::Attribute::Patrol) {
		mStageObjects[i][j]=new Patrol(Vec2({ (float)mLeft + j * mRectWidth + mRectWidth / 2,
		(float)mUp - (i+1) * mRectHeight + mRectHeight / 2 }), mRectWidth, mRectHeight);
	}
	else if (stageObject->GetAttribute() == StageObject::Attribute::Key) {
		mStageObjects[i][j] = new Key(Vec2({ (float)mLeft + j * mRectWidth + mRectWidth / 2,
		(float)mUp - (i+1) * mRectHeight + mRectHeight / 2 }), mRectWidth, mRectHeight);
	}
	else if (stageObject->GetAttribute() == StageObject::Attribute::Battery) {
		mStageObjects[i][j] = new Battery(Vec2({ (float)mLeft + j * mRectWidth + mRectWidth / 2,
		(float)mUp - (i+1) * mRectHeight + mRectHeight / 2 }), mRectWidth, mRectHeight);
	}
	else if (stageObject->GetAttribute() == StageObject::TreasureChest) {
		mStageObjects[i][j]=new TreasureChest(Vec2({ (float)mLeft + j * mRectWidth + mRectWidth / 2,
		(float)mUp - (i+1) * mRectHeight + mRectHeight / 2 }), mRectWidth, mRectHeight);
	}
	else if (stageObject->GetAttribute() == StageObject::Ghost) {
		mStageObjects[i][j] = new Ghost_CreateStage(Vec2({ (float)mLeft + j * mRectWidth + mRectWidth / 2,
		(float)mUp - (i + 1) * mRectHeight + mRectHeight / 2 }), mRectWidth/3.0f, mRectHeight);
	}
	else if (stageObject->GetAttribute() == StageObject::Escapee1) {
		mStageObjects[i][j] = new Escapee_CreateStage(Vec2({ (float)mLeft + j * mRectWidth + mRectWidth / 2,
		(float)mUp - (i + 1) * mRectHeight + mRectHeight / 2 }), mRectWidth / 3.0f, mRectHeight,1);
	}
	else if (stageObject->GetAttribute() == StageObject::Escapee2) {
		mStageObjects[i][j] = new Escapee_CreateStage(Vec2({ (float)mLeft + j * mRectWidth + mRectWidth / 2,
		(float)mUp - (i + 1) * mRectHeight + mRectHeight / 2 }), mRectWidth / 3.0f, mRectHeight,2);
	}
	else if (stageObject->GetAttribute() == StageObject::Escapee3) {
		mStageObjects[i][j] = new Escapee_CreateStage(Vec2({ (float)mLeft + j * mRectWidth + mRectWidth / 2,
		(float)mUp - (i + 1) * mRectHeight + mRectHeight / 2 }), mRectWidth / 3.0f, mRectHeight,3);
	}
	mStageObjects[i][j]->SetSpeed(stageObject->GetSpeed());
	mStageObjects[i][j]->SetClockwise(stageObject->GetClockwise());
	mStageObjects[i][j]->SetPatrolRange(stageObject->GetPatrolRange());
	mStageObjects[i][j]->SetIsInStage(true);
	mStageObjects[i][j]->SetIteration(std::pair{ i,j });
	if (mGame)mStageObjects[i][j]->InitializeStageObject_Game(mGame);
	if(mCreateStage)mStageObjects[i][j]->InitializeStageObject_CreateStage(mCreateStage);

}

void Stage::SetNewStageObject_Attribute(int i, int j, StageObject::Attribute attribute) {
	if (attribute == StageObject::Attribute::Brock) {
		mStageObjects[i][j] = new Brock(Vec2({ (float)mLeft + j * mRectWidth + mRectWidth / 2,
		(float)mUp - (i+1) * mRectHeight + mRectHeight / 2 }), mRectWidth, mRectHeight);
	}
	else if (attribute == StageObject::Attribute::Door) {
		mStageObjects[i][j] = new Door(Vec2({ (float)mLeft + j * mRectWidth + mRectWidth / 2,
		(float)mUp - (i+1) *mRectHeight + mRectHeight / 2 }), mRectWidth, mRectHeight);
	}
	else if (attribute == StageObject::Attribute::Patrol) {
		mStageObjects[i][j] = new Patrol(Vec2({ (float)mLeft + j * mRectWidth + mRectWidth / 2,
		(float)mUp - (i+1) * mRectHeight + mRectHeight / 2 }), mRectWidth, mRectHeight);
	}
	else if (attribute == StageObject::Attribute::Key) {
		mStageObjects[i][j] = new Key(Vec2({ (float)mLeft + j * mRectWidth + mRectWidth / 2,
		(float)mUp - (i+1) * mRectHeight + mRectHeight / 2 }), mRectWidth, mRectHeight);
	}
	else if (attribute == StageObject::Attribute::Battery) {
		mStageObjects[i][j] = new Battery(Vec2({ (float)mLeft + j * mRectWidth + mRectWidth / 2,
		(float)mUp - (i+1) * mRectHeight + mRectHeight / 2 }), mRectWidth, mRectHeight);
	}
	else if (attribute == StageObject::TreasureChest) {
		mStageObjects[i][j] = new TreasureChest(Vec2({ (float)mLeft + j * mRectWidth + mRectWidth / 2,
		(float)mUp - (i+1) * mRectHeight + mRectHeight / 2 }), mRectWidth, mRectHeight);
	}
	else if (attribute == StageObject::Ghost) {
		mStageObjects[i][j] = new Ghost_CreateStage(Vec2({ (float)mLeft + j * mRectWidth + mRectWidth / 2,
		(float)mUp - (i + 1) * mRectHeight + mRectHeight / 2 }), mRectWidth / 3.0f, mRectHeight);
	}
	else if (attribute == StageObject::Escapee1) {
		mStageObjects[i][j] = new Escapee_CreateStage(Vec2({ (float)mLeft + j * mRectWidth + mRectWidth / 2,
		(float)mUp - (i + 1) * mRectHeight + mRectHeight / 2 }), mRectWidth / 3.0f, mRectHeight, 1);
	}
	else if (attribute == StageObject::Escapee2) {
		mStageObjects[i][j] = new Escapee_CreateStage(Vec2({ (float)mLeft + j * mRectWidth + mRectWidth / 2,
		(float)mUp - (i + 1) * mRectHeight + mRectHeight / 2 }), mRectWidth / 3.0f, mRectHeight, 2);
	}
	else if (attribute == StageObject::Escapee3) {
		mStageObjects[i][j] = new Escapee_CreateStage(Vec2({ (float)mLeft + j * mRectWidth + mRectWidth / 2,
		(float)mUp - (i + 1) * mRectHeight + mRectHeight / 2 }), mRectWidth / 3.0f, mRectHeight, 3);
	}
	mStageObjects[i][j]->SetIsInStage(true);
	mStageObjects[i][j]->SetIteration(std::pair{ i,j });
	if (mGame)mStageObjects[i][j]->InitializeStageObject_Game(mGame);
	if (mCreateStage)mStageObjects[i][j]->InitializeStageObject_CreateStage(mCreateStage);
}

bool Stage::SetNewCandle(class StageObject* candle) {
	for (int i = 0; i < mCandles.size(); i++) {
		if (mCandles[i] == 0) {
			mCandles[i] =
				new Candle(candle->GetPosition(), candle->GetWidth(), candle->GetHeight(), candle->GetRadius());
			mCandles[i]->SetIsInStage(true);
			mCandles[i]->SetLightRad(candle->GetLightRad());
			mCandles[i]->SetCandleIteration(i);
			if (mGame)mCandles[i]->InitializeStageObject_Game(mGame);
			if (mCreateStage)mCandles[i]->InitializeStageObject_CreateStage(mCreateStage);
			return true;
		}
	}
	return false;
}

void Stage::DeleteCandle(class StageObject* candle) {
	mCandles[candle->GetCandleIteration()] = 0;
	delete mCandles[candle->GetCandleIteration()];
	return;
}

void Stage::RemakeStageObjects() {
	for (int i = 0; i < mVerticalSize; i++) {
		for (int j = 0; j < mSideSize; j++) {
			if (mExpandRect.contains(mRects[i][j])) {
				if (mStageObjects[i][j] != 0)DeleteStageObject(i, j);
				SetNewStageObject_Attribute(i, j, mExpandAttribute);
			}
		}
	}
}

void Stage::DeleteStageObject(int i,int j) {
	if (mStageObjects[i][j] == 0)return;
	if (mStageObjects[i][j]->GetAttribute() == StageObject::Ghost||
		mStageObjects[i][j]->GetAttribute()==StageObject::Escapee1||
		mStageObjects[i][j]->GetAttribute()==StageObject::Escapee2||
		mStageObjects[i][j]->GetAttribute()==StageObject::Escapee3) {
		mCreateStage->GetStageMenu()->RemakePlayer(mStageObjects[i][j]);
	}
	delete mStageObjects[i][j];
	mStageObjects[i][j] = 0;
	return;
}

void Stage::DeleteStageObjects() {
	for (int i = 0; i < mCandles.size(); i++) {
		if (mCandles[i] == 0)continue;
		if (mCandles[i]->GetCircleComponent()->GetCircle().intersects(mDeleteRect)) {
			delete mCandles[i];
			mCandles[i] = 0;
		}
	}
	for (int i = 0; i < mVerticalSize; i++) {
		for (int j = 0; j < mSideSize; j++) {
			if (mRects[i][j].intersects(mDeleteRect)) {
				DeleteStageObject(i, j);
			}
		}
	}
}

void Stage::Update_CreateStage(float delteTime) {
	if (mCreateStage->GetHand()->GetIsExpand()) {
		if (GetRevHandToFul(mExpandFulcrumIter.first, mExpandFulcrumIter.second) == 1) {
			mExpandFulcrumPos =
				mStageObjects[mExpandFulcrumIter.first][mExpandFulcrumIter.second]->GetRightBottom();
		}
		else if (GetRevHandToFul(mExpandFulcrumIter.first, mExpandFulcrumIter.second) == 2) {
			mExpandFulcrumPos =
				mStageObjects[mExpandFulcrumIter.first][mExpandFulcrumIter.second]->GetLeftBottom();
		}
		else if (GetRevHandToFul(mExpandFulcrumIter.first, mExpandFulcrumIter.second) == 3) {
			mExpandFulcrumPos =
				mStageObjects[mExpandFulcrumIter.first][mExpandFulcrumIter.second]->GetLeftTop();
		}
		else if (GetRevHandToFul(mExpandFulcrumIter.first, mExpandFulcrumIter.second) == 4) {
			mExpandFulcrumPos =
				mStageObjects[mExpandFulcrumIter.first][mExpandFulcrumIter.second]->GetRightTop();
		}
		mExpandRectCenter = Vec2{ (mExpandFulcrumPos.x + mCreateStage->GetHand()->GetPosition().x) / 2
			,(mExpandFulcrumPos.y + mCreateStage->GetHand()->GetPosition().y) / 2 };
		mExpandRectWidth = abs(mExpandFulcrumPos.x - mCreateStage->GetHand()->GetPosition().x);
		mExpandRectHeight = abs(mExpandFulcrumPos.y - mCreateStage->GetHand()->GetPosition().y);
		mExpandRect = RectF{ Arg::center(mExpandRectCenter),mExpandRectWidth,mExpandRectHeight };
	}
	if (mCreateStage->GetHand()->GetIsDelete()) {
		mDeleteRectCenter = Vec2{
			(mDeleteFulcrumPos.x + mCreateStage->GetHand()->GetPosition().x) / 2
		,(mDeleteFulcrumPos.y + mCreateStage->GetHand()->GetPosition().y) / 2 };
		mDeleteRectWidth = abs(mDeleteFulcrumPos.x - mCreateStage->GetHand()->GetPosition().x);
		mDeleteRectHeight = abs(mDeleteFulcrumPos.y - mCreateStage->GetHand()->GetPosition().y);
		mDeleteRect = RectF{ Arg::center(mDeleteRectCenter),mDeleteRectWidth,mDeleteRectHeight };
	}


	if (mIsSaveError) {
		if (mCreateStage->GetHand()->GetInputBack().down()) {
			mIsSaveError = false;
		}
	}
}

int Stage::GetRevHandToFul(int i, int j) {
	//左上
	if (mCreateStage->GetHand()->GetPosition().x<mStageObjects[i][j]->GetPosition().x &&
		mCreateStage->GetHand()->GetPosition().y>mStageObjects[i][j]->GetPosition().y) {
		return 1;
	}
	//右上
	else if (mCreateStage->GetHand()->GetPosition().x > mStageObjects[i][j]->GetPosition().x &&
	   mCreateStage->GetHand()->GetPosition().y > mStageObjects[i][j]->GetPosition().y) {
		return 2;
	}
	//右下
	else if (mCreateStage->GetHand()->GetPosition().x > mStageObjects[i][j]->GetPosition().x &&
	   mCreateStage->GetHand()->GetPosition().y < mStageObjects[i][j]->GetPosition().y) {
		return 3;
	}
	//左下
	else {
		return 4;
	}

}

void Stage::Draw_CreateStage() {
	DrawRect(Vec2{ mLeft + mWidth / 2,mUp - mHeight / 2 }, mWidth, mHeight, ColorF(0, 0, 0));
	DrawRectFrame(Vec2{ mLeft + mWidth / 2,mUp - mHeight / 2 },
		mWidth, mHeight, 0.003, 0,ColorF(1, 1, 1));
	

	for (int i = 0; i < mVerticalSize; i++) {
		DrawSquareDotLine({ mLeft,mUp - i * mRectHeight },
			{ mLeft + mWidth,mUp - i * mRectHeight }, 0.005, ColorF(1, 1, 1));
	}
	for (int j = 0; j < mSideSize; j++) {
		DrawSquareDotLine({ mLeft + j * mRectWidth,mUp },
			{ mLeft + j * mRectWidth,mUp - mHeight }, 0.005, ColorF(1, 1, 1));
	};


	/*if (mCreateStage->GetHand()->GetIsExpand()) {
		DrawRect(mExpandRectCenter, mExpandRectWidth, mExpandRectHeight, ColorF(0, 1.0, 1.0));
	}
	if (mCreateStage->GetHand()->GetIsDelete()) {
		DrawRect(mDeleteRectCenter, mDeleteRectWidth, mDeleteRectHeight, ColorF(1, 0, 0));
	}*/

	for (int i = 0; i < mVerticalSize; i++) {
		for (int j = 0; j < mSideSize; j++) {
			//Expand
			if (mCreateStage->GetHand()->GetIsExpand()) {
				if (mExpandRect.contains(mRects[i][j])) {
					DrawRectFrame(Vec2{ mLeft + mRectWidth * j + mRectWidth / 2,
						mUp - mRectHeight * (i+1) + mRectHeight / 2 },
						mRectWidth, mRectHeight,0.003,0, ColorF(0, 1, 1));
				}
			}
			//Delete
			if (mCreateStage->GetHand()->GetIsDelete()) {
				if (mDeleteRect.intersects(mRects[i][j])) {
					DrawRectFrame(Vec2{ mLeft + mRectWidth * j + mRectWidth / 2,
						mUp - mRectHeight * (i+1) + mRectHeight / 2 },
						mRectWidth, mRectHeight, 0.003,0, ColorF(1,0,0));
				}
			}
			//Patrol
			if (mStageObjects[i][j] != 0 &&
				mStageObjects[i][j]->GetAttribute() == StageObject::Attribute::Patrol) {
				switch (mStageObjects[i][j]->GetClockwise()) {
				case 0:
					for (int di = 0; di < mStageObjects[i][j]->GetPatrolRange(); di++) {
						DrawRectFrame(Vec2{ mLeft + mRectWidth * j + mRectWidth / 2,
						mUp - mRectHeight * (i+1-di) + mRectHeight / 2},
						mRectWidth, mRectHeight, 0.003,0, ColorF(0, (float)102/255, 0));
					}
					break;
				case 1:
					for (int dj = 0; dj < mStageObjects[i][j]->GetPatrolRange(); dj++) {
						DrawRectFrame(Vec2{ mLeft + mRectWidth * (j+dj) + mRectWidth / 2,
						mUp - mRectHeight * (i+1) + mRectHeight / 2 },
						mRectWidth, mRectHeight, 0.003,0, ColorF(0, (float)102 / 255, 0));
					}
					break;
				case 2:
					for (int di = 0; di < mStageObjects[i][j]->GetPatrolRange(); di++) {
						DrawRectFrame(Vec2{ mLeft + mRectWidth * j + mRectWidth / 2,
						mUp - mRectHeight * (i+1 + di) + mRectHeight / 2 },
						mRectWidth, mRectHeight, 0.003,0, ColorF(0, (float)102 / 255, 0));
					}
					break;
				case 3:
					for (int dj = 0; dj < mStageObjects[i][j]->GetPatrolRange(); dj++) {
						DrawRectFrame(Vec2{ mLeft + mRectWidth * (j - dj) + mRectWidth / 2,
						mUp - mRectHeight * (i+1) + mRectHeight / 2 },
				    	mRectWidth, mRectHeight, 0.003,0, ColorF(0, (float)102 / 255, 0));
					}
					break;

				}
			}
		}
	}

	
}

void Stage::DrawForward_CreateStage() {
	if (mIsSaveError) {
		DrawRect(mSaveErrorPos, mSaveErrorRectWidth, mSaveErrorRectHeight, ColorF(1, 1, 1));
		mSaveErrorFont(U"You don't arrange any players").draw(Arg::center(ConvertToView(mSaveErrorPos)), ColorF(0, 0, 0));
	}
}



RectF Stage::GetViewStageRect() {
	return RectF(ConvertToView(Vec2{ mLeft,mUp }), GetScreenWidth() * mWidth/2.0f, GetScreenHeight() * mHeight/2.0f);
}

bool Stage::EndCreateStage() {
	std::pair<int,int>
		initGhost=std::pair(-1,-1),
		initEscapee1 = std::pair(-1, -1),
		initEscapee2 = std::pair(-1, -1),
		initEscapee3 = std::pair(-1, -1);
	for (auto& row : mStageObjects) {
		for (auto& stageObject : row) {
			if (stageObject == 0)continue;
			switch (stageObject->GetAttribute()) {
			case StageObject::Attribute::Ghost:
				initGhost = stageObject->GetIteration();
				break;
			case StageObject::Attribute::Escapee1:
				initEscapee1 = stageObject->GetIteration();
				break;
			case StageObject::Attribute::Escapee2:
				initEscapee2 = stageObject->GetIteration();
				break;
			case StageObject::Attribute::Escapee3:
				initEscapee3 = stageObject->GetIteration();
				break;
			}
		}
	}

	
	if (initGhost == pair(-1, -1) || initEscapee1 == pair(-1, -1) || initEscapee2 == pair(-1, -1) || initEscapee3 == pair(-1, -1)) {
		mIsSaveError = true;
		return false;
	}
	


	for (int i = 0; i < mVerticalSize; i++) {
		for (int j = 0; j < mSideSize; j++) {
			mCanBeGone[i][j] = false;
			mGhostCanBeGone[i][j] = false;
			mEscapee1CanBeGone[i][j] = false;
			mEscapee2CanBeGone[i][j] = false;
			mEscapee3CanBeGone[i][j] = false;
		}
	}

	//到達可能なところをmCanBeGoneに保存
	SearchCanBeGone(mGhostCanBeGone, initGhost);
	SearchCanBeGone(mEscapee1CanBeGone, initEscapee1);
	SearchCanBeGone(mEscapee2CanBeGone, initEscapee2);
	SearchCanBeGone(mEscapee3CanBeGone, initEscapee3);

	int cnt = 0;
	for (int i = 0; i < mVerticalSize; i++) {
		for (int j = 0; j < mSideSize; j++) {
			if (mGhostCanBeGone[i][j] && mEscapee1CanBeGone[i][j] && mEscapee2CanBeGone[i][j] && mEscapee3CanBeGone[i][j]) {
				cnt++;
				mCanBeGone[i][j] = true;
			}
		}
	}
	if (cnt < 3)return false;

	SaveStage();
	return true;
}

void Stage::SearchCanBeGone(vector<vector<bool>>& can_be_gone, pair<int, int> init_pos) {
	queue<pair<int, int>> q;
	q.emplace(init_pos);
	while (!q.empty()) {
		int ni = q.front().first, nj = q.front().second;
		q.pop();
		if (can_be_gone[ni][nj])continue;
		can_be_gone[ni][nj] = true;
		for (int k = 0; k<4; k++) {
			int nxi = ni + di[k], nxj=nj + dj[k];
			if (nxi < 0 || nxi >= mVerticalSize || nxj < 0 || nxj >= mSideSize)continue;
			if ((mStageObjects[nxi][nxj] != 0 && mStageObjects[nxi][nxj]->GetAttribute() == StageObject::Attribute::Brock)
				|| (mStageObjects[nxi][nxj] != 0 && mStageObjects[nxi][nxj]->GetAttribute() == StageObject::Attribute::Wall)
				|| (mStageObjects[nxi][nxj] != 0 && mStageObjects[nxi][nxj]->GetAttribute() == StageObject::Attribute::Patrol)
				|| (mStageObjects[nxi][nxj] != 0 && mStageObjects[nxi][nxj]->GetAttribute() == StageObject::Attribute::TreasureChest))continue;
			q.push(pair(nxi, nxj));
		}
	}

}

bool Stage::SaveStage() {

	//Attribute  Clockwise  PatrolRange  BatterySize  Treasure  Speed  CanBeGone
	vector<vector<tuple<StageObject::Attribute, int, int, StageObject::BatterySize, StageObject::Treasure, float, bool>>>
		mDetails(mVerticalSize, vector<tuple<StageObject::Attribute, int, int, StageObject::BatterySize, StageObject::Treasure, float, bool>>
			(mSideSize, tuple(StageObject::Attribute::None, 0, 0, StageObject::BatterySize::Zero, StageObject::Treasure::Empty, 0.0f, false)));

	//保存
	for (int i = 0; i < mVerticalSize; i++) {
		for (int j = 0; j < mSideSize; j++) {
			if (mStageObjects[i][j] == 0)mDetails[i][j] = tuple(StageObject::Attribute::None, 0, 0, StageObject::BatterySize::Zero, StageObject::Treasure::Empty, 0.0f, mCanBeGone[i][j]);
			else mDetails[i][j] = tuple(mStageObjects[i][j]->GetAttribute(), mStageObjects[i][j]->GetClockwise(), mStageObjects[i][j]->GetPatrolRange(), mStageObjects[i][j]->GetBatterySize(), mStageObjects[i][j]->GetTreasure(), mStageObjects[i][j]->GetSpeed(), mCanBeGone[i][j]);
		}
	}

	//Candle
	vector<tuple<bool, Vec2, float>> mCandleDetails(mCandles.size(), tuple(false, Vec2(0, 0), 0.0f));
	//保存
	for (int i = 0; i < mCandles.size(); i++) {
		if (mCandles[i] == 0)continue;
		else mCandleDetails[i] = tuple(true, mCandles[i]->GetPosition(), mCandles[i]->GetLightRad());
	}

	//バイナリファイルに保存
	StageName = RegisterStageName();        //Stageの名前
	Serializer<BinaryWriter> writer{ U"Stage/" + StageName + U"/" + U"Data.bin" };

	//画像の保存
	ScreenCapture::RequestCurrentFrame();
	Image image; 
	ScreenCapture::GetFrame(image);
	Vec2 LeftTop = ConvertToView(Vec2(mLeft, mUp));
	Image image2 = image.clipped(Rect(LeftTop.x, LeftTop.y,
		(int32)(mWidth / 2.0 * GetScreenWidth()), (int32)(mHeight / 2.0 * GetScreenHeight())));


	image2.save(U"Stage/" + StageName + U"/" + U"Image.png");
	writer(mDetails); 
	writer(mCandleDetails);
	return true;
}

String Stage::RegisterStageName() {
	vector<String> stageNames;
	Deserializer<BinaryReader> reader{U"Stage/StageNames.bin"};
	if (reader) {
		reader(stageNames);
	}
	stageNames.push_back(GetCreateStage()->GetStageName());
	

	Serializer<BinaryWriter> writer{U"Stage/StageNames.bin"};
	writer(stageNames);
	return GetCreateStage()->GetStageName();
}



//Game/////////////////////////////////////////////////////////////////////////////////////////////
void Stage::Initialize_Game(class Game* game, FilePath fileName) {
	mGame = game;
	Deserializer<BinaryReader> reader{ fileName };
	if (not reader) {
		throw Error{ U"Failed to open file" };
	}
	vector<vector<tuple<StageObject::Attribute, int, int, StageObject::BatterySize, StageObject::Treasure, float, bool>>>
		mDetails(mVerticalSize, vector<tuple<StageObject::Attribute, int, int, StageObject::BatterySize, StageObject::Treasure, float, bool>>
			(mSideSize, tuple(StageObject::Attribute::None, 0, 0, StageObject::BatterySize::Zero, StageObject::Treasure::Empty, 0.0f, false)));
	//0Attribute  1Clockwise  2PatrolRange  3BatterySize  4Treasure  5Speed  6CanBeGone
	vector<tuple<bool, Vec2, float>> mCandleDetails(mCandles.size(), tuple(false, Vec2(0, 0), 0.0f));

	reader(mDetails);
	reader(mCandleDetails);

	mStageObjects.resize(mVerticalSize);
	for (auto& row : mStageObjects) {
		row.resize(mSideSize);
		for (auto& so : row) {
			so = 0;
		}
	}

	mCandles.assign(30, 0);


	mRects.resize(mVerticalSize);
	for (auto& row : mRects) {
		row.resize(mSideSize);
	}

	mCanBeGone.resize(mVerticalSize);
	for (auto& row : mCanBeGone) {
		row.resize(mSideSize);
	}
	Array<int> mGoalCandidates;

	for (int i = 0; i < mVerticalSize; i++) {
		for (int j = 0; j < mSideSize; j++) {
			if (get<0>(mDetails[i][j]) == StageObject::Attribute::None) {
				mStageObjects[i][j] = 0;
			}
			else {
				if (get<0>(mDetails[i][j]) == StageObject::Attribute::Ghost) {
					mGhostIteration = pair(i, j);
					mGhostSpeed = get<4>(mDetails[i][j]);
				}
				else if (get<0>(mDetails[i][j]) == StageObject::Attribute::Escapee1) {
					mEscapee1Iteration = pair(i, j);
					mEscapee1Speed = get<4>(mDetails[i][j]);
				}
				else if (get<0>(mDetails[i][j]) == StageObject::Attribute::Escapee2) {
					mEscapee2Iteration = pair(i, j);
					mEscapee2Speed = get<4>(mDetails[i][j]);
				}
				else if (get<0>(mDetails[i][j]) == StageObject::Attribute::Escapee3) {
					mEscapee3Iteration = pair(i, j);
					mEscapee3Speed = get<4>(mDetails[i][j]);
				}
				else {
					SetNewStageObject_Attribute(i, j, get<0>(mDetails[i][j]));
					mStageObjects[i][j]->SetClockwise(get<1>(mDetails[i][j]));
					mStageObjects[i][j]->SetPatrolRange(get<2>(mDetails[i][j]));
					mStageObjects[i][j]->SetBatterySize(get<3>(mDetails[i][j]));
					mStageObjects[i][j]->SetTreasure(get<4>(mDetails[i][j]));
					mStageObjects[i][j]->SetSpeed(get<5>(mDetails[i][j]));
					mStageObjects[i][j]->SetIteration(pair(i, j));
					mStageObjects[i][j]->InitializeStage_Game();
				}
			}
			mCanBeGone[i][j] = get<6>(mDetails[i][j]);
			if(mCanBeGone[i][j])mGoalCandidates<<(i * mVerticalSize + mSideSize);

			
		}
	}

	InitCandle = new Candle(Vec2(0, 0),
		 mRectWidth / 3,
		 mRectHeight / 3,
		 mRectHeight / 6);
	InitCandle->InitializeStageObject_Game(mGame);
	for (int i = 0; i < mCandles.size(); i++) {
		if (!get<0>(mCandleDetails[i]))continue;
		InitCandle->SetPosition(get<1>(mCandleDetails[i]));
		InitCandle->SetLightRad(get<2>(mCandleDetails[i]));
		SetNewCandle(InitCandle);
	}

	delete InitCandle;
	InitCandle = 0;

	int mGoal = mGoalCandidates.choice();
	mGoalIteration = pair(mGoal / mVerticalSize, mGoal % mSideSize);
}


//Gameの終了判定
void Stage::Update_Game(float deltaTime) {
	mGameTime += deltaTime;
    bool mIsEscapeesAlive = true;
	/*for (auto player : GetGame()->GetPlayers()) {
		if (player->GetIsAlive()) {
			mIsEscapeesAlive = true;
		}
	}*/

	if (mGameTime > GoalTime) {
		mIsGoal = true;
	}
	if (mGameTime > GameLimitTime) {
		GetGame()->Shutdown();
	}
	if (!mIsEscapeesAlive) {
		GetGame()->Shutdown();
	}
}

void Stage::Draw_Game() {
	DrawRect(Vec2{ mLeft + mWidth / 2,mUp - mHeight / 2 }, mWidth, mHeight, ColorF(0, 0, 0));
	DrawRectFrame(Vec2{ mLeft + mWidth / 2,mUp - mHeight / 2 },
		mWidth, mHeight, 0.003, 0, ColorF(1, 1, 1));

	for (int i = 0; i < mVerticalSize; i++) {
		DrawSquareDotLine({ mLeft,mUp - i * mRectHeight },
			{ mLeft + mWidth,mUp - i * mRectHeight }, 0.005, ColorF(1, 1, 1));
	}
	for (int j = 0; j < mSideSize; j++) {
		DrawSquareDotLine({ mLeft + j * mRectWidth,mUp },
			{ mLeft + j * mRectWidth,mUp - mHeight }, 0.005, ColorF(1, 1, 1));
	};

	if (mIsGoal) {
		DrawRect(Vec2({ (float)mLeft + mGoalIteration.second * mRectWidth + mRectWidth / 2,
		(float)mUp - (mGoalIteration.first + 1) * mRectHeight + mRectHeight / 2 }), mRectWidth, mRectHeight,ColorF(1,0,0));
	}
	
}


