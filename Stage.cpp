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

#include<cmath>


Stage::Stage(float width, float height)
	:mVerticalSize(15)
	, mSideSize(24)
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
{
	mRectWidth = mWidth / mSideSize;
	mRectHeight = mHeight / mVerticalSize;

}

Stage::~Stage() {}

void Stage::Initialize_CreateStage(CreateStage* createStage) {
	mStageObjects.resize(mVerticalSize);
	for (auto& row : mStageObjects) {
		row.resize(mSideSize);
		for (auto& so : row) {
			so = 0;
		}
	}

	mCandles.assign(20,0);


	mRects.resize(mVerticalSize);
	for (auto& row : mRects) {
		row.resize(mSideSize);
	}

	//mRectsの初期設定
	for (int i = 0; i < mVerticalSize; i++) {
		for (int j = 0; j < mSideSize; j++) {
			mRects[i][j] = RectF({ mLeft + mRectWidth * j,mUp - mRectHeight * i },
				mRectWidth, mRectHeight);
		}
	}

	mCreateStage = createStage;
	mStageRect = RectF({ mLeft,mUp }, mWidth, mHeight);

}

void Stage::SetNewStageObject(int i, int j, StageObject::Attribute attribute) {
	if (attribute == StageObject::Attribute::Brock) {
		mStageObjects[i][j] = new Brock(Vec2({ (float)mLeft + j * mRectWidth + mRectWidth / 2,
		(float)mUp - i * mRectHeight + mRectHeight / 2 }), mRectWidth, mRectHeight);
	}
	else if (attribute == StageObject::Attribute::Door) {
		mStageObjects[i][j]=new Door(Vec2({ (float)mLeft + j * mRectWidth + mRectWidth / 2,
		(float)mUp - i * mRectHeight + mRectHeight / 2 }),mRectWidth, mRectHeight);
	}
	else if (attribute == StageObject::Attribute::Patrol) {
		mStageObjects[i][j]=new Patrol(Vec2({ (float)mLeft + j * mRectWidth + mRectWidth / 2,
		(float)mUp - i * mRectHeight + mRectHeight / 2 }), mRectWidth, mRectHeight);
	}
	else if (attribute == StageObject::Attribute::Key) {
		mStageObjects[i][j] = new Key(Vec2({ (float)mLeft + j * mRectWidth + mRectWidth / 2,
		(float)mUp - i * mRectHeight + mRectHeight / 2 }), mRectWidth, mRectHeight);
	}
	else if (attribute == StageObject::Attribute::Battery) {
		mStageObjects[i][j] = new Battery(Vec2({ (float)mLeft + j * mRectWidth + mRectWidth / 2,
		(float)mUp - i * mRectHeight + mRectHeight / 2 }), mRectWidth, mRectHeight);
	}
	else if (attribute == StageObject::TreasureChest) {
		mStageObjects[i][j]=new TreasureChest(Vec2({ (float)mLeft + j * mRectWidth + mRectWidth / 2,
		(float)mUp - i * mRectHeight + mRectHeight / 2 }), mRectWidth, mRectHeight);
	}
	mStageObjects[i][j]->SetIsInStage(true);
	mStageObjects[i][j]->SetIteration(std::pair{ i,j });
	mStageObjects[i][j]->InitializeStageObject_CreateStage(mCreateStage);
}

bool Stage::SetNewCandle(class StageObject* candle) {
	for (int i = 0; i < mCandles.size(); i++) {
		if (mCandles[i] == 0) {
			mCandles[i] =
				new Candle(candle->GetPosition(), candle->GetWidth(), candle->GetHeight(), candle->GetRadius());
			mCandles[i]->InitializeStageObject_CreateStage(mCreateStage);
			mCandles[i]->SetIsInStage(true);
			mCandles[i]->SetLightRad(candle->GetLightRad());
			mCandles[i]->SetCandleIteration(i);
			Print << i;
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
				SetNewStageObject(i, j, mExpandAttribute);
			}
		}
	}
}

void Stage::DeleteStageObject(int i,int j) {
	if (mStageObjects[i][j] == 0)return;
	delete mStageObjects[i][j];
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
						mUp - mRectHeight * i + mRectHeight / 2 },
						mRectWidth, mRectHeight,0.003,0, ColorF(0, 1, 1));
				}
			}
			//Delete
			if (mCreateStage->GetHand()->GetIsDelete()) {
				if (mDeleteRect.intersects(mRects[i][j])) {
					DrawRectFrame(Vec2{ mLeft + mRectWidth * j + mRectWidth / 2,
						mUp - mRectHeight * i + mRectHeight / 2 },
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
						mUp - mRectHeight * (i-di) + mRectHeight / 2},
						mRectWidth, mRectHeight, 0.003,0, ColorF(0, (float)102/255, 0));
					}
					break;
				case 1:
					for (int dj = 0; dj < mStageObjects[i][j]->GetPatrolRange(); dj++) {
						DrawRectFrame(Vec2{ mLeft + mRectWidth * (j+dj) + mRectWidth / 2,
						mUp - mRectHeight * i + mRectHeight / 2 },
						mRectWidth, mRectHeight, 0.003,0, ColorF(0, (float)102 / 255, 0));
					}
					break;
				case 2:
					for (int di = 0; di < mStageObjects[i][j]->GetPatrolRange(); di++) {
						DrawRectFrame(Vec2{ mLeft + mRectWidth * j + mRectWidth / 2,
						mUp - mRectHeight * (i + di) + mRectHeight / 2 },
						mRectWidth, mRectHeight, 0.003,0, ColorF(0, (float)102 / 255, 0));
					}
					break;
				case 3:
					for (int dj = 0; dj < mStageObjects[i][j]->GetPatrolRange(); dj++) {
						DrawRectFrame(Vec2{ mLeft + mRectWidth * (j - dj) + mRectWidth / 2,
						mUp - mRectHeight * i + mRectHeight / 2 },
				    	mRectWidth, mRectHeight, 0.003,0, ColorF(0, (float)102 / 255, 0));
					}
					break;

				}
			}
		}
	}

}


RectF Stage::GetViewStageRect() {
	return RectF(ConvertToView(Vec2{ mLeft,mUp }), GetScreenWidth() * mWidth/2.0f, GetScreenHeight() * mHeight/2.0f);
}
