#include"CreateStage.h"
#include"Stage.h"
#include"StageObject.h"

Stage::Stage(int width, int height)
	:mVerticalSize(15)
	,mSideSize(24)
	,mWidth(width)
	,mHeight(height)
	,mLeft(-0.9)
	,mUp(0.9)
{
	mRectWidth = mWidth / mSideSize;
	mRectHeight = mHeight / mVerticalSize;

}

Stage::~Stage(){}

void Stage::Initialize_CreateStage(CreateStage* createStage) {
	mStageObjects.resize(mVerticalSize);
	for (auto& row : mStageObjects) {
		row.resize(mSideSize);
	}

	mRects.resize(mVerticalSize);
	for (auto& row : mRects) {
		row.resize(mSideSize);
	}

	//mRectsの初期設定
	for (int i = 0; i < mVerticalSize; i++) {
		for (int j = 0; j < mSideSize; j++) {
			mRects[i][j] = RectF({ mRectWidth * i,mRectHeight * j },
				mRectWidth, mRectHeight);
		}
	}

	mCreateStage = createStage;
	mStageRect = RectF({ mLeft,mUp }, mWidth, mHeight);
}

void Stage::SetNewStageObject(int i, int j) {
	mStageObjects[i][j] = new StageObject(Vec2({ j * mRectWidth + mRectWidth / 2,
		i * mRectHeight + mRectHeight / 2 }), mRectWidth, mRectHeight);
	mStageObjects[i][j]->InitializeActor_CreateStage(mCreateStage);
}

void Stage::Update_CreateStage(float delteTime) {

}

void Stage::Draw_CreateStage() {
	DrawRectFrame(Vec2{mLeft + mWidth / 2,mUp - mHeight / 2},
		mWidth, mHeight, 0.01, ColorF(0, 0, 0));
	for (int i = 0; i < mVerticalSize; i++) {
		DrawSquareDotLine({ mLeft,i * mRectHeight },
			{ mLeft+mWidth,i * mRectHeight }, 0.01, ColorF(0, 0, 0));
	}
	for (int j = 0; j < mSideSize; j++) {
		DrawSquareDotLine({ j*mRectWidth,mUp },
			{ j*mRectWidth,mUp-mHeight }, 0.01, ColorF(0, 0, 0));
	}


}

