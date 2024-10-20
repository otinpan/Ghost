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


};
