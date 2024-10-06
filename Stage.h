#pragma once
#include"CreateStage.h"

class Stage {
public:
	Stage(int width,int height);
	~Stage();

	void Initialize_CreateStage(CreateStage* createStage);

	void Update_CreateStage(float deltaTime);
	void Draw_CreateStage();

	int GetVerticalSize() { return mVerticalSize; }
	int GetSideSize() { return mSideSize; }
	float GetHeight() { return mHeight; }

	RectF GetStageRect() { return mStageRect; }
	std::vector<std::vector<class StageObject*>>& GetStageObjects() { return mStageObjects; }
	std::vector<std::vector<RectF>>& GetRects() { return mRects; }

	void SetNewStageObject(int i, int j);

private:
	class CreateStage* mCreateStage;

	int mVerticalSize;//要素数(縦)
	int mSideSize;//要素数(横)
	float mHeight;//全体の高さ
	float mWidth;//全体の横幅
	float mRectWidth;//Rect一つの横幅
	float mRectHeight;//Rect一つの高さ
	float mLeft;//StageRectの左端
	float mUp;//StageRectの上端
	Vec2 mStageCenter;

	std::vector<std::vector<class StageObject* >> mStageObjects;
	std::vector<std::vector<RectF>> mRects;
	RectF mStageRect;

};
