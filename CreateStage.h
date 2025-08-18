#pragma once
#include"Common.h"
#include"Parent.h"
#include"Actor.h"
#include"SpriteComponent.h"
#include"CircleComponent.h"
#include"SquareComponent.h"
#include"TextMenu.h"

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

	void AddDrawing(class DrawingComponent* drawing);
	void RemoveDrawing(class DrawingComponent* drawing);

 	void AddCircle(class CircleComponent* circle);
	void RemoveCircle(class CircleComponent* circle);

	void AddSquare(class SquareComponent* square);
	void RemoveSquare(class SquareComponent* square);

	void AddTriangle(class TriangleComponent* tri);
	void RemoveTriangle(class TriangleComponent* tri);

	void AddStageObject(class StageObject* stageobject);
	void RemoveStageObject(class StageObject* stageobject);

	void OpenTextMenu();
	void CloseTextMenu();

	void SetStageName(const String& stagename);
	const String& GetStageName() const{ return mStageName; }


	class Hand* &GetHand() { return mHand; }
	std::vector<class StageObject*>& GetStageObjects() { return mStageObjects; }
	class Stage* &GetStage() { return mStage; }
	class StageMenu*& GetStageMenu() { return mStageMenu; }

	void SetShouldCloseTextMenu(bool shouldCloseTextMenu) { mShouldCloseTextMenu = shouldCloseTextMenu; }

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

	//All the Drwaing
	std::vector<class DrawingComponent*> mDrawings_Background;
	std::vector<class DrawingComponent*> mDrawings_Foreground;

	//All the Circle components drawn
	std::vector<class CircleComponent*> mCircles;

	//All the Square component drawn
	std::vector<class SquareComponent*> mSquares;

	//All the Triangle components drawn
	std::vector<class TriangleComponent*> mTriangles;

	Parent::SeqID mSeqID;

	String mStageName;

	class Hand* mHand;
	class StageObject* mStageObject;
	std::vector<class StageObject*> mStageObjects;
	std::vector<class Candle*> mCandles;
	class Stage* mStage;
	class StageMenu* mStageMenu;
	std::unique_ptr<class TextMenu> mTextMenu;
	class Brock* mBrock;
	class Door* mDoor;
	class Patrol* mPatrol;
	class Candle* mCandle;

	bool mShouldCloseTextMenu;
};
