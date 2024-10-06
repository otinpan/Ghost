#pragma once
#include"Actor.h"

class StageObject :public Actor {
public:
	StageObject(Vec2 pos,float width,float height);
	~StageObject();

	enum Attribute {
		Wall,
		Brock,
		Door,
	};

	void InitializeActor_CreateStage(class CreateStage* createstage)override;


	void UpdateActor_CreateStage(float deltaTime)override;
	void ActorInput(std::vector<Input> keyState)override;

	class SquareComponent* GetSquareComponent() { return sqc; }

	bool GetIsGripen() { return mIsGripen; }
	void SetIsGripen(bool b) { mIsGripen = b; }
	Attribute GetAttribute() { return mAttribute; }
	void SetAttribute(Attribute attribute) { mAttribute = attribute; }
	bool GetIsInStage() { return mIsInStage; }
	void SetIsInStage(bool isInStage) { mIsInStage = isInStage; }


private:
	class SquareComponent* sqc;
	class CircleComponent* LeftTopCC;
	class CircleComponent* RightBottomCC;

	bool mIsGripen;
	bool mIsInStage;//Stageの中にあるか

	Attribute mAttribute;

	Vec2 mCenter;
	float mWidth;
	float mHeight;
};
