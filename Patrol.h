#pragma once
#include"StageObject.h"

class Patrol :public StageObject{
public:
	Patrol(Vec2 pos, float width, float height);
	~Patrol();

	void InitializeStageObject_CreateStage(class CreateStage* createStage)override;

	void UpdateStageObject_CreateStage(float deltaTime)override;

	void InitializeStageMenu_CreateStage()override;
	void UpdateStageMenu_CreateStage(float deltaTime)override;
	void DrawStageMenu_CreateStage()override;
	void ShutdownStageMenu_CreateStage()override;

private:
	class CircleComponent* mUpCC;
	class CircleComponent* mDownCC;
	class CircleComponent* mRightCC;
	class CircleComponent* mLeftCC;
	class CircleComponent* mPlusCC;
	class CircleComponent* mMinusCC;

	Vec2 mTriCenter;
	Vec2 mUpTriPos;
	Vec2 mDownTriPos;
	Vec2 mRightTriPos;
	Vec2 mLeftTriPos;
	float mTriLength;
	float mTriLengthFromCenter;

	Vec2 mPlusPos;
	Vec2 mMinusPos;
	Vec2 mAddCenter;
	float mAddLengthFromCenter;
	float mPlusWidth;
	float mPlusHeight;
	float mMinusWidth;
	float mMinusHeight;

	float mPlusTime;
	float mMinusTime;
	float mPlusLastTime;
	float mMinusLastTime;
	bool mIsPlusLasting;
	bool mIsMinusLasting;
};
