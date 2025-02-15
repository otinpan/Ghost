#pragma once
using namespace std;
#include"Actor.h"

class Player :public Actor {
public:
	Player(Vec2 pos, float speed);
	~Player();

	enum Attribute {
		Ghost,
		GhostClone,
		Escapee1,
		Escapee2,
		Escapee3,
	};

	void InitializeActor_Game(class Game* game)override;
	virtual void InitializePlayer_Game(class Game* game);

	void UpdateActor_Game(float deltaTime)override;
	virtual void UpdatePlayer_Game(float deltaTime);

	void SetAttribute(Attribute attribute) { mAttribute = attribute; }
	Attribute GetAttribute() { return mAttribute; }

	class CircleComponent* GetCircleComponent() { return cc; }
	class CircleComponent* GetBigCircleComponent() { return Bigcc; }
	class CircleComponent* GetMidCircleComponent() { return Midcc; }
	class CircleComponent* GetSmallCircleComponent() { return Smallcc; }

	void UpdatePos_Game(float deltaTime);
	virtual void UpdatePlayerPos_Game(float deltaTime);

	float GetSpeedMagnification() { return mSpeedMagnification; }
	void SetSpeedMagnification(float speedMagnification) { mSpeedMagnification = speedMagnification; }
	float GetStandardSpeed() { return StandardSpeed; }
	void SetStandardSpeed(float standardSpeed) { StandardSpeed = standardSpeed; }
	float GetPlayerRadius() { return mRadius; }
	void SetPlayerRadius(float radius) { mRadius = radius; }
	bool GetIsAlive() { return mIsAlive; }
	void SetIsAlive(bool isAlive) { mIsAlive = isAlive; }
	bool GetIsLighted() { return mIsLighted; }
	void SetIsLighted(bool isLighted) { mIsLighted = isLighted; }

	void UpdateHeartbeat(float deltaTime);
	virtual void UpdatePlayerHeartbeat(float deltaTime);

	float GetHeartbeatLimitTime() { return HeartbeatLimitTime; }
	void SetHeartbeatLimitTime(float heartbeatLimitTime) { HeartbeatLimitTime = heartbeatLimitTime; }

private:
	class CircleComponent* cc;
	//検知の範囲
	class CircleComponent* Bigcc;
	class CircleComponent* Midcc;
	class CircleComponent* Smallcc;

	Attribute mAttribute;

	float mSpeedMagnification;

	float StandardSpeed;

	int mVerticalSize;
	int mSideSize;

	//Flashlight
	bool mIsAlive;
	bool mIsLighted;

    float mObjectLeft;
	float mObjectRight;
	float mObjectUp;
	float mObjectDown;
	Line LineL;
	Line LineR;
	Line LineU;
	Line LineD;
	Vec2 mPos;
	float mRadius;

	//鼓動
	float mHeartbeatTime;
	float HeartbeatLimitTime;
};
