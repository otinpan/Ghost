#pragma once
#include"CreateStage.h"
#include"StageObject.h"

class Stage :public Actor{
public:
	Stage(float width,float height);
	~Stage();

	void Initialize_CreateStage(CreateStage* createStage);

	void Update_CreateStage(float deltaTime);
	void Draw_CreateStage();

	int GetVerticalSize() { return mVerticalSize; }
	int GetSideSize() { return mSideSize; }
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


	RectF GetStageRect() { return mStageRect; }
	std::vector<std::vector<class StageObject*>>& GetStageObjects() { return mStageObjects; }
	std::vector<std::vector<RectF>>& GetRects() { return mRects; }

	void SetNewStageObject(int i, int j,StageObject::Attribute attribute);
	void RemakeStageObjects();
	void DeleteStageObjects();

	int GetRevHandToFul(int i, int j); //mHandがmFulcrumに対してどこにあるか

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

	std::vector<std::vector<class StageObject* >> mStageObjects;
	std::vector<std::vector<RectF>> mRects;
	RectF mStageRect;
	

};
