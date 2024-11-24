#pragma once
using namespace std;
#include"Actor.h"

class Player :public Actor {
public:
	Player(Vec2 pos, float speed);
	~Player();

	enum Attribute {
		Ghost,
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

	void UpdatePos_Game(float deltaTime);

private:
	class CircleComponent* cc;
	vector<vector<class StageObject*>> mStageObjects;

	Attribute mAttribute;

	int mVerticalSize;
	int mSideSize;

    float mObjectLeft;
	float mObjectRight;
	float mObjectUp;
	float mObjectDown;
	Vec2 mPos;
	float mRadius;
};
