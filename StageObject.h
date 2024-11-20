#pragma once
#include"Actor.h"

class StageObject :public Actor {
public:
	StageObject(Vec2 pos, float width, float height);
	~StageObject();

	enum Attribute {
		None,
		Wall,
		Brock,
		Door,
		Patrol,
		Battery,
		Key,
		TreasureChest,
		Candle,
		Ghost,
		Escapee1,
		Escapee2,
		Escapee3,
	};

	void InitializeActor_CreateStage(class CreateStage* createstage)override;
	virtual void InitializeStageObject_CreateStage(class CreateStage* createStage);

	void InitializeActor_Game(class Game* game)override;
	virtual void InitializeStageObject_Game(class Game* game);

	void UpdateActor_CreateStage(float deltaTime)override;
	virtual void UpdateStageObject_CreateStage(float deltaTime);

	void UpdateActor_Game(float deltaTime)override;
	virtual void UpdateStageObject_Game(float deltaTime);

	void ActorInput(std::vector<Input> keyState)override;

	class SquareComponent*& GetSquareComponent() { return sqc; }
	std::vector<CircleComponent*>& GetCircleComponents() { return cc; }

	bool GetIsGripen() { return mIsGripen; }
	void SetIsGripen(bool b) { mIsGripen = b; }
	Attribute GetAttribute() { return mAttribute; }
	void SetAttribute(Attribute attribute) { mAttribute = attribute; }
	bool GetIsInStage() { return mIsInStage; }
	void SetIsInStage(bool isInStage) { mIsInStage = isInStage; }
	std::pair<int, int> GetIteration() { return mIteration; }
	void SetIteration(std::pair<int, int> iter) { mIteration = iter; }
	int GetClockwise() { return mClockwise; }
	void SetClockwise(int rotation) { mClockwise = rotation; }
	float GetWidth() { return mWidth; }
	float GetHeight() { return mHeight; }
	int PatrolRange() { return mPatrolRange; }
	void SetPatrolRange(int patrolRange) { mPatrolRange = patrolRange; }
	int GetPatrolRange() { return mPatrolRange; }
	void AddPatrolRange(bool isPlus);
	void AdjustPatrolRange();
	void SetRadius(float rad) { mRadius = rad; }
	float GetRadius() { return mRadius; }
	void SetLightRad(float lightRad) { mLightRad = lightRad; }
	float GetLightRad() { return mLightRad; }
	void SetMaxLightRad(float maxLightRad) { mMaxLightRad = maxLightRad; }
	float GetMaxLightRad() { return mMaxLightRad; }
	void SetMinLightRad(float minLightRad) { mMinLightRad = minLightRad; }
	float GetMinLightRad() { return mMinLightRad; }
	void SetIsInObjectMenu(bool isInObjectMenu) { mIsInObjectMenu = isInObjectMenu; }
	bool GetIsInObjectMenu() { return mIsInObjectMenu; }
	int GetCandleIteration() { return mCandleIteration; }
	void SetCandleIteration(int candleIteration) { mCandleIteration = candleIteration; }
	float GetLightRadRange() { return mLightRadRange; }
	void SetLightRadRange(float lightRadRange) { mLightRadRange = lightRadRange; }
	

	Vec2 GetLeftTop();
	Vec2 GetRightTop();
	Vec2 GetRightBottom();
	Vec2 GetLeftBottom();
	Vec2 GetExpandFulcrum(int i);

	void RotateClockwise(bool isClockwise);
	void SpreadLightRad(bool isPlus);

	//Menu
	virtual void UpdateStageMenu_CreateStage(float deltaTime);
	virtual void DrawStageMenu_CreateStage();
	virtual void InitializeStageMenu_CreateStage();
	virtual void ShutdownStageMenu_CreateStage();


private:
	class SquareComponent* sqc;
	std::vector<class CircleComponent*> cc;
	//0lefttop 1righttop 2rightbottom 3leftbottom

	std::vector<float> dx;
	std::vector<float> dy;

	bool mIsGripen;
	bool mIsInStage;//Stageの中にあるか
	bool mIsInObjectMenu;//ObjectMenuの中にあるか

	Attribute mAttribute;

	Vec2 mCenter;
	float mWidth;
	float mHeight;
	float mRadius;
	float mLightRad;
	float mMaxLightRad;
	float mMinLightRad;
	float mLightRadRange;
	std::pair<int, int> mIteration;//stageにある場合stageのどこにあるかを保存
	int mCandleIteration;
	int mClockwise;

	int mPatrolRange;
	
};

float ConvertToSpeed(float barMin,float barWidth,float pos);
int ConvertToInt(float f);
