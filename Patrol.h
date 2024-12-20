#pragma once
#include"StageObject.h"
#include"MoveComponent.h"

class Patrol :public StageObject{
public:
	Patrol(Vec2 pos, float width, float height);
	~Patrol();

	void InitializeStageObject_CreateStage(class CreateStage* createStage)override;
	void InitializeStageObject_Game(class Game* game)override;
	void InitializeStage_Game()override;

	void UpdateStageObject_CreateStage(float deltaTime)override;
	void UpdateStageObject_Game(float deltaTime)override;

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
	class SquareComponent* mBarSC_CreateStage;

	class MoveComponent* mMoveC;

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


	//Speed
	Vec2 mBarCenter;
	Vec2 mBarPos;
	float mBarWidth;
	float mBarMin;
	float mBarMax;
	bool mIsBarGripen;

	//Font
	Font mStageMenuFont{ConvertToInt((float)0.05 * GetMagnification())};
	Font mSpeedFont{ ConvertToInt((float)0.04 * GetMagnification()) };

	//どこからどこまで動くか
	Line FromLine;
	Line ToLine;
	Vec2 ToPos;
	float ToLeft;
	float ToRight;
	float ToUp;
	float ToDown;
	Vec2 mVelocity;

};
