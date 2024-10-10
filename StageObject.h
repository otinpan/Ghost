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

	class SquareComponent* &GetSquareComponent() { return sqc; }
	std::vector<CircleComponent*> &GetCircleComponents() { return cc; }

	bool GetIsGripen() { return mIsGripen; }
	void SetIsGripen(bool b) { mIsGripen = b; }
	Attribute GetAttribute() { return mAttribute; }
	void SetAttribute(Attribute attribute) { mAttribute = attribute; }
	bool GetIsInStage() { return mIsInStage; }
	void SetIsInStage(bool isInStage) { mIsInStage = isInStage; }
	std::pair<int, int> GetIteration() { return mIteration; }
	void SetIteration(std::pair<int, int> iter) { mIteration = iter; }
	
	Vec2 GetLeftTop();
	Vec2 GetRightTop();
	Vec2 GetRightBottom();
	Vec2 GetLeftBottom();
	Vec2 GetExpandFulcrum(int i);



private:
	class SquareComponent* sqc;
	std::vector<class CircleComponent*> cc;
	//0lefttop 1righttop 2rightbottom 3leftbottom

	std::vector<float> dx;
	std::vector<float> dy;

	bool mIsGripen;
	bool mIsInStage;//Stageの中にあるか

	Attribute mAttribute;

	Vec2 mCenter;
	float mWidth;
	float mHeight;
	std::pair<int, int> mIteration;
	//stageにある場合stageのどこにあるかを保存
};
