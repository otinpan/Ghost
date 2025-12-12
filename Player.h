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

	void UpdatePos_Game(float deltaTime);
	virtual void UpdatePlayerPos_Game(float deltaTime);

	float GetSpeedMagnification() { return mSpeedMagnification; }
	void SetSpeedMagnification(float speedMagnification) { mSpeedMagnification = speedMagnification; }
	float GetStandardSpeed() { return StandardSpeed; }
	void SetStandardSpeed(float standardSpeed) { StandardSpeed = standardSpeed; }
	float GetPlayerRadius() { return mRadius; }
	void SetPlayerRadius(float radius) { mRadius = radius; }
	bool GetIsAlive() { return mIsAlive; }
	virtual void SetIsAlive_Game(bool isAlive,class Game* game);
	bool GetIsLighted() { return mIsLighted; }
	void SetIsLighted(bool isLighted) { mIsLighted = isLighted; }
	float GetRadius() { return mRadius; }
	ColorF GetCircleColor();
	float GetLightedTime() { return mLightedTime; }
	void SetLightedTime(float lightedTime) { mLightedTime = lightedTime; }
	float GetLightedLimitTime() { return mLightedLimitTime; }
	void SetLightedLimitTime(float lightedLimitTime) { mLightedLimitTime=lightedLimitTime; }


private:
	class CircleComponent* cc;
	ColorF mGhostColor;
	ColorF mEscapee1Color;
	ColorF mEscapee2Color;
	ColorF mEscapee3Color;


	Attribute mAttribute;

	float mSpeedMagnification;

	float StandardSpeed;

	int mVerticalSize;
	int mSideSize;

	//Flashlight
	bool mIsAlive;
	bool mIsLighted;
	float mLightedTime;
	float mLightedLimitTime;

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
};
