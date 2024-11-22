#pragma once
#include"CreateStage.h"
#include"StageObject.h"

class Stage :public Actor {
public:
	Stage(float width, float height);
	~Stage();

	void Initialize_CreateStage(CreateStage* createStage);
	void Initialize_Game(Game* game,FilePath fileName);

	void Update_Game(float deltaTime);
	void Draw_Game();

	void Update_CreateStage(float deltaTime);
	void Draw_CreateStage();

	int GetVerticalSize() { return mVerticalSize; }
	int GetSideSize() { return mSideSize; }
	float GetLeft() { return mLeft; }
	float GetUp() { return mUp; }
	float GetRight() { return mLeft + mWidth; }
	float GetDown() { return mUp - mHeight; }
	float GetHeight() { return mHeight; }
	float GetWidth() { return mWidth; }
	float GetRectHeight() { return mRectHeight; }
	float GetRectWidth() { return mRectWidth; }
	Vec2 GetExpandFulcrum() { return mExpandFulcrumPos; }
	void SetExpandFulcrum(Vec2 pos) { mExpandFulcrumPos = pos; }
	std::pair<int, int> GetExpandFulcrumIter() { return mExpandFulcrumIter; }
	void SetExpandFulcrumIter(std::pair<int, int> iter) { mExpandFulcrumIter = iter; }
	StageObject::Attribute GetExpandAttribute() { return mExpandAttribute; }
	void SetExpandAttribute(StageObject::Attribute at) { mExpandAttribute = at; }
	void SetDeleteFulcrumPos(Vec2 pos) { mDeleteFulcrumPos = pos; }
	bool SetNewCandle(class StageObject* candle);
	void DeleteCandle(class StageObject* candle);


	RectF GetStageRect() { return mStageRect; }
	RectF GetViewStageRect();
	std::vector<std::vector<class StageObject*>>& GetStageObjects() { return mStageObjects; }
	void SetStageObject(int i, int j, StageObject* stageObject) { mStageObjects[i][j] = stageObject; }
	std::vector<std::vector<RectF>>& GetRects() { return mRects; }
	std::vector<class Candle*>& GetCandle() { return mCandles; }

	void SetNewStageObject(int i, int j, StageObject* stageObject);
	void SetNewStageObject_Attribute(int i, int j, StageObject::Attribute attribute);
	void RemakeStageObjects();
	void DeleteStageObject(int i, int j);
	void DeleteStageObjects();

	//End
	bool EndCreateStage();

	int GetRevHandToFul(int i, int j); //mHandがmFulcrumに対してどこにあるか

	//Game////////////////////////////////////////////////////////////////////////
	std::pair<int, int> GetGhostIteration() { return mGhostIteration; }
	std::pair<int, int> GetEscapee1Iteration() { return mEscapee1Iteration; }
	std::pair<int, int> GetEscapee2Iteration() { return mEscapee2Iteration; }
	std::pair<int, int> GetEscapee3Iteration() { return mEscapee3Iteration; }
	float GetGhostSpeed() { return mGhostSpeed; }
	float GetEscapee1Speed() { return mEscapee1Speed; }
	float GetEscapee2Speed() { return mEscapee2Speed; }
	float GetEscapee3Speed() { return mEscapee3Speed; }


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
	std::pair<int, int> mExpandFulcrumIter; //支点となる位置
	Vec2 mExpandFulcrumPos;//拡大のとき支点となる座標
	StageObject::Attribute mExpandAttribute;//拡大のときのObjectの属性
	RectF mExpandRect;
	Vec2 mExpandRectCenter;
	float mExpandRectWidth;
	float mExpandRectHeight;
	Vec2 mDeleteFulcrumPos;
	Vec2 mDeleteRectCenter;
	float mDeleteRectWidth;
	float mDeleteRectHeight;

	std::vector<std::vector<class StageObject* >> mStageObjects;
	std::vector<class Candle*> mCandles;
	std::vector<std::vector<RectF>> mRects;
	RectF mStageRect;
	RectF mDeleteRect;
	std::vector<std::vector<bool>> mCanBeGone;
	std::vector<int> di = {0, 0, 1, -1};
	std::vector<int> dj = { 1,-1,0,0 };

	//Save
	bool mIsSaveError;
	Vec2 mSaveErrorPos;
	float mSaveErrorRectWidth;
	float mSaveErrorRectHeight;

	//Font
	const Font mSaveErrorFont{ ConvertToInt(0.05 * GetMagnification()),Typeface::Bold };

	//Game//////////////////////////////////////////////////////////
	class Game* mGame;
	class Candle* InitCandle;

	std::pair<int, int> mGoalIteration;
	std::pair<int, int> mGhostIteration;
	std::pair<int, int> mEscapee1Iteration;
	std::pair<int, int> mEscapee2Iteration;
	std::pair<int, int> mEscapee3Iteration;
	float mGhostSpeed;
	float mEscapee1Speed;
	float mEscapee2Speed;
	float mEscapee3Speed;
};
