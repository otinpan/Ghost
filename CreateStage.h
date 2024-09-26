#pragma once
#include"Common.h"
#include"Parent.h"
#include"Actor.h"
#include"SpriteComponent.h"
#include"CircleComponent.h"
#include"SquareComponent.h"

class CreateStage
{
public:
	CreateStage();
	~CreateStage();

	void update(class Parent*);
	void draw();

	bool Initialize();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	void AddCircle(class CircleComponent* circle);
	void RemoveCircle(class CircleComponent* circle);

	void AddSquare(class SquareComponent* square);
	void RemoveSquare(class SquareComponent* square);

	void AddStageObject(class StageObject* stageobject);
	void RemoveStageObject(class StageObject* stageobject);

	class Hand* &GetHand() { return mHand; }
	std::vector<class StageObject*>& GetStageObjects() { return mStageObjects; }


	//Sequence
	void moveTo(Parent* parent, Parent::SeqID id);
	void SetSeqID(Parent::SeqID id) { mSeqID = id; }

private:
	void ProcessInput();
	void UpdateGame();
	void LoadData();
	void UnloadData();

	bool mIsRunning;
	bool mUpdatingActors;

	// All the actors in the game
	std::vector<class Actor*> mActors;
	// Any pending actors
	std::vector<class Actor*> mPendingActors;

	// All the sprite components drawn
	std::vector<class SpriteComponent*> mSprites;

	//All the Circle components drawn
	std::vector<class CircleComponent*> mCircles;

	//All the Square component drawn
	std::vector<class SquareComponent*> mSquares;

	Parent::SeqID mSeqID;


	class Hand* mHand;
	std::vector<class StageObject*> mStageObjects;
};
