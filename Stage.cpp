#include"CreateStage.h"
#include"Stage.h"
#include"StageObject.h"
#include"Brock.h"
#include"Wall.h"

Stage::Stage(float width, float height)
	:mVerticalSize(15)
	,mSideSize(24)
	,mWidth(width)
	,mHeight(height)
	,mLeft(-0.96f)
	,mUp(0.96f)
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
			mRects[i][j] = RectF({ mLeft+mRectWidth * j,mUp-mRectHeight * i },
				mRectWidth, mRectHeight);
		}
	}

	mCreateStage = createStage;
	mStageRect = RectF({ mLeft,mUp }, mWidth, mHeight);
}

void Stage::SetNewStageObject(int i, int j,StageObject::Attribute attribute) {
	if (attribute == StageObject::Attribute::Brock) {
		mStageObjects[i][j] = new Brock(Vec2({ (float)mLeft + j * mRectWidth + mRectWidth / 2,
		(float)mUp - i * mRectHeight + mRectHeight / 2 }), mRectWidth, mRectHeight);
		mStageObjects[i][j]->InitializeActor_CreateStage(mCreateStage);
		mStageObjects[i][j]->SetIsInStage(true);
	}
	/*mStageObjects[i][j] = new StageObject(Vec2({(float)mLeft + j * mRectWidth + mRectWidth / 2,
		(float)mUp-i * mRectHeight + mRectHeight / 2 }), mRectWidth, mRectHeight);
	mStageObjects[i][j]->InitializeActor_CreateStage(mCreateStage);*/
}

void Stage::Update_CreateStage(float delteTime) {

}

void Stage::Draw_CreateStage() {
	DrawRectFrame(Vec2{mLeft + mWidth / 2,mUp - mHeight / 2},
		mWidth, mHeight, 0.005, ColorF(0, 0, 0));

	for (int i = 0; i < mVerticalSize; i++) {
		DrawSquareDotLine({ mLeft,mUp-i * mRectHeight },
			{ mLeft+mWidth,mUp-i * mRectHeight }, 0.005, ColorF(0, 0, 0));
	}
	for (int j = 0; j < mSideSize; j++) {
		DrawSquareDotLine({ mLeft+j*mRectWidth,mUp },
			{mLeft+ j*mRectWidth,mUp-mHeight }, 0.005, ColorF(0, 0, 0));
	};


}

