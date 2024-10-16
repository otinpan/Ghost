#pragma once


class StageMenu {
public:
	StageMenu();
	~StageMenu();

	void Initialize_CreateStage(class CreateStage* createStage);

	void Update_CreateStage(float deltaTime);
	void Draw_CreateStage();

private:
	class CreateStage* mCreateStage;

	float mMenuLeft;
	float mMenuUp;
	float mMenuWidth;
	float mMenuHeight;
	RectF mMenuRect;
	Vec2 mMenuPos;


};
