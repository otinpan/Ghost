#pragma once
#include"Common.h"
#include"Parent.h"
#include"Actor.h"
#include"SpriteComponent.h"
#include"CircleComponent.h"

class CreateStage
{
public:
	CreateStage();
	~CreateStage();

	void update(class Parent*);
	void draw();

	bool Initialize();
	void Shutdown();

	void AddStageObject(class Actor* actor);
	void RemoveStageObject(class Actor* actor);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	void AddCircle(class CircleComponent* circle);
	void RemoveCircle(class CircleComponent* circle);

	//Sequence
	void moveTo(Parent* paretn, Parent::SeqID id);
	void SetSeqID(Parent::SeqID id) { mSeqID = id; }

private:
	void ProcessInput();
	void UpdateGame();
	void LoadData();
	void UnloadData();

	bool mIsRunning;
	bool mUpdatingActors;

	// All the actors in the game
	std::vector<class Actor*> mStageObjects;
	// Any pending actors
	std::vector<class Actor*> mPendingStageObjects;

	// All the sprite components drawn
	std::vector<class SpriteComponent*> mSprites;

	//All the Circle components drawn
	std::vector<class CircleComponent*> mCircles;

	Parent::SeqID mSeqID;
};
