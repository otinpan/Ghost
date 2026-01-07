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

	enum BatterySize {
		Zero,
		Small,
		Mid,
		Big,
	};

	enum Treasure {
		Empty,
		TreasureKey,
		TreasureBattery,
	};

	enum Material {
		Stone,
		Wood,
		Grass,
	};

	void InitializeActor_CreateStage(class CreateStage* createstage)override;
	virtual void InitializeStageObject_CreateStage(class CreateStage* createStage);
	virtual void InitializeStage_CreateStage(); // InitializeStageObjectの後にもう一度Initializeする

	void InitializeActor_Game(class Game* game)override;
	virtual void InitializeStageObject_Game(class Game* game);//InitializeActor_GameによってStageObjectLeft等が上書きされてしまう
	virtual void InitializeStage_Game(); //上書きをさらに上書きする

	void UpdateActor_CreateStage(float deltaTime)override;
	virtual void UpdateStageObject_CreateStage(float deltaTime);


	void UpdateActor_Game(float deltaTime)override;
	virtual void UpdateStageObject_Game(float deltaTime);

	void ActorInput(std::vector<Input> keyState)override;

	class SquareComponent*& GetSquareComponent() { return sqc; }
	std::vector<CircleComponent*>& GetCircleComponents() { return cc; }
	class SpriteComponent*& GetSpriteComponent() { return sc; }

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
	BatterySize GetBatterySize() { return mBatterySize; }
	void SetBatterySize(BatterySize batterySize) { mBatterySize = batterySize; }
	Treasure GetTreasure() { return mTreasure; }
	void SetTreasure(Treasure treasure) { mTreasure = treasure; }
	Material GetMaterial() { return mMaterial; }
	void SetMaterial(Material material) { mMaterial = material; }


	Vec2 GetLeftTop();
	Vec2 GetRightTop();
	Vec2 GetRightBottom();
	Vec2 GetLeftBottom();
	Vec2 GetExpandFulcrum(int i);

	void RotateClockwise(bool isClockwise);
	void SpreadLightRad(bool isPlus);

	Vec2 GetCenter() { return mCenter; }
	Vec2 GetDoorCenter() { return mDoorCenter; }
	void SetDoorCenter(Vec2 pos) { mDoorCenter = pos; }
	float GetDoorWidth() { return mDoorWidth; }
	void SetDoorWidth(float width) { mDoorWidth = width; }
	float GetDoorHeight() { return mDoorHeight; }
	void SetDoorHeight(float height) { mDoorHeight = height; }
	float GetObjectLeft() { return mObjectLeft; }
	void SetObjectLeft(float objectLeft) { mObjectLeft = objectLeft; }
	float GetObjectRight() { return mObjectRight; }
	void SetObjectRight(float objectRight) { mObjectRight = objectRight; }
	float GetObjectUp() { return mObjectUp; }
	void SetObjectUp(float objectUp) { mObjectUp = objectUp; }
	float GetObjectDown() { return mObjectDown; }
	void SetObjectDown(float objectDown) { mObjectDown = objectDown; }
	Line GetLineL() { return LineL; }
	void SetLineL(Line lineL) { LineL = lineL; }
	Line GetLineR() { return LineR; }
	void SetLineR(Line lineR) { LineR = lineR; }
	Line GetLineU() { return LineU; }
	void SetLineU(Line lineU) { LineU = lineU; }
	Line GetLineD() { return LineD; }
	void SetLineD(Line lineD) { LineD = lineD; }
	float GetStandardSpeed() { return StandardSpeed; }
	void SetStandardSpeed(float standardSpeed) { StandardSpeed = standardSpeed; }
	bool GetIsTurn() { return mIsTurn; }
	void SetIsTurn(bool isTurn) { mIsTurn = isTurn; }
	bool GetIsChosen() { return mIsChosen; }
	void SetIsChosen(bool isChosen) { mIsChosen = isChosen; }


	//Menu
	virtual void UpdateStageMenu_CreateStage(float deltaTime);
	virtual void DrawStageMenu_CreateStage();
	virtual void InitializeStageMenu_CreateStage();
	virtual void ShutdownStageMenu_CreateStage();


private:
	class SquareComponent* sqc;
	std::vector<class CircleComponent*> cc;
	class SpriteComponent* sc;
	//0lefttop 1righttop 2rightbottom 3leftbottom

	std::vector<float> dx;
	std::vector<float> dy;

	bool mIsGripen;
	bool mIsInStage;//Stageの中にあるか
	bool mIsInObjectMenu;//ObjectMenuの中にあるか
	bool mIsChosen;

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

	// Brock
	Material mMaterial;

	//Patrol
	int mPatrolRange;
	float StandardSpeed;
	bool mIsTurn;

	//Door
	Vec2 mDoorCenter;
	float mDoorWidth;
	float mDoorHeight;

	//Battery
	BatterySize mBatterySize;

	//Treasure
	Treasure mTreasure;

	//Object当たり判定
	float mObjectLeft;
	float mObjectRight;
	float mObjectUp;
	float mObjectDown;
	Line LineL;
	Line LineR;
	Line LineU;
	Line LineD;


};

float ConvertToSpeed(float barMin,float barWidth,float pos);

