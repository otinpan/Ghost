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

	float GetSpeedMagnification() { return mSpeedMagnification; }
	void SetSpeedMagnification(float speedMagnification) { mSpeedMagnification = speedMagnification; }

private:
	class CircleComponent* cc;

	Attribute mAttribute;

	float mSpeedMagnification;

	int mVerticalSize;
	int mSideSize;

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
