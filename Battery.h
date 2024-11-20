#pragma once
#include"StageObject.h"

class Battery :public StageObject {
public:
	Battery(Vec2 pos, float width, float height);
	~Battery();

	enum BatterySize {
		Small,
		Mid,
		Big,
	};

	void InitializeStageObject_CreateStage(class CreateStage* createStage)override;
	void InitializeStageObject_Game(class Game* game)override;

	void UpdateStageObject_CreateStage(float deltaTime)override;
	void UpdateStageObject_Game(float deltaTime)override;

	void InitializeStageMenu_CreateStage()override;
	void UpdateStageMenu_CreateStage(float deltaTime)override;
	void DrawStageMenu_CreateStage()override;
	void ShutdownStageMenu_CreateStage()override;

private:
	CircleComponent *mSmallCC;
	CircleComponent* mMidCC;
	CircleComponent* mBigCC;

	Vec2 mSmallPos;
	Vec2 mMidPos;
	Vec2 mBigPos;
	float mSmallRad;
	float mMidRad;
	float mBigRad;

	BatterySize mBatterySize;
};
