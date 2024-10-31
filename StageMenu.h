#pragma once


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

	class Brock*& GetBrock() { return mBrock; }

	RectF GetViewStageMenuRect();

private:
	class CreateStage* mCreateStage;

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

	int mObjectNum; //Objectの種類数
	float mObjectEachWidth;

	class Brock* mBrock;
	class Door* mDoor;
	class Battery* mBattery;
	class Patrol* mPatrol;
	class Key* mKey;
	class TreasureChest* mTreasureChest;
	class Candle* mCandle;
};
