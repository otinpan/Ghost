#pragma once
#include"StageObject.h"
#include"Battery.h"

class TreasureChest :public StageObject {
public:
	TreasureChest(Vec2 pos, float width,float height);
	~TreasureChest();

	enum Treasure {
		None,
		Key,
		Battery,
	};

	void InitializeStageObject_CreateStage(class CreateStage* createStage) override;

	void UpdateStageObject_CreateStage(float deltaTime)override;

	void InitializeStageMenu_CreateStage()override;
	void UpdateStageMenu_CreateStage(float deltaTime)override;
	void DrawStageMenu_CreateStage()override;
	void ShutdownStageMenu_CreateStage()override;

private:
	class SquareComponent* mNoneSC;
	class SquareComponent* mBatterySC;
	class SquareComponent* mKeySC;
	class CircleComponent* mSmallCC;
	class CircleComponent* mMidCC;
	class CircleComponent* mBigCC;

	float mMidBatteryRad;

	Vec2 mNonePos;
	Vec2 mBatteryPos;
	Vec2 mKeyPos;

	float mRectWidth;
	float mRectHeight;
	float mEachHeight;

	Battery::BatterySize mBatterySize;

	Vec2 mMidPos;

	Treasure mTreasure;
};
