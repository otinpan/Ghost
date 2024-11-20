#pragma once
#include<Siv3D.hpp>
#include"Parent.h"
#include"StageObject.h"


class StageMenu {
public:
	StageMenu();
	~StageMenu();

	void Initialize_CreateStage(class CreateStage* createStage);

	void Update_CreateStage(float deltaTime);
	void Draw_CreateStage();

	float GetMenuLeft() { return mMenuLeft; }
	float GetMenuUp() { return mMenuUp; }
	float GetMenuRight() { return mMenuRight; }
	float GetMenuDown() { return mMenuDown; }
	float GetMenuWidth() { return mMenuWidth; }
	float GetMenuHeight() { return mMenuHeight; }
	Vec2 GetMenuPos() { return mMenuPos; }
	void RemakeStageObject(class StageObject* stageObject);
	void RemakePlayer(class StageObject* stageObject);

	//End
	Vec2 GetEndPos() { return mEndPos; }
	float GetEndRectWidth() { return mEndRectWidth; }
	float GetEndRectHeight() { return mEndRectHeight; }
	bool GetIsEndOver() { return mIsEndOver; }
	void SetIsEndOver(bool isEndOver) { mIsEndOver = isEndOver; }


	class Brock*& GetBrock() { return mBrock; }

	RectF GetViewStageMenuRect();

private:
	class CreateStage* mCreateStage;
	class SquareComponent* mEndSC;

	float mMenuLeft;
	float mMenuUp;
	float mMenuDown;
	float mMenuRight;
	float mMenuWidth;
	float mMenuHeight;
	RectF mMenuRect;
	Vec2 mMenuPos;

	//StageObject置き場
	float mObjectMenuLeft;
	float mObjectMenuRight;
	float mObjectMenuUp;
	float mObjectMenuDown;
	float mObjectMenuWidth;
	float mObjectMenuHeight;
	Vec2 mObjectMenuPos;

	//Player
	Vec2 mPlayerPos;
	float mPlayerRectWidth;
	float mPlayerRectHeight;

	//End
	Vec2 mEndPos;
	float mEndRectWidth;
	float mEndRectHeight;
	RectF mEndRect;
	bool mIsEndOver;

	int mObjectNum; //Objectの種類数
	float mObjectEachWidth;

	class Brock* mBrock;
	class Door* mDoor;
	class Battery* mBattery;
	class Patrol* mPatrol;
	class Key* mKey;
	class TreasureChest* mTreasureChest;
	class Candle* mCandle;
	class Escapee_CreateStage* mEscapee1;
	class Escapee_CreateStage* mEscapee2;
	class Escapee_CreateStage* mEscapee3;
	class Ghost_CreateStage* mGhost;

	//Font
	Font mEndFont{ ConvertToInt((float)0.08 * GetMagnification()),Typeface::Bold};
};
