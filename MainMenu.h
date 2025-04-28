#pragma once
#include"Common.h"
#include"Parent.h"
#include"Actor.h"

class MainMenu
{
public:
	MainMenu();
	~MainMenu();

	enum MainSelect {
		SelectGame,
		SelectCreateStage,
		SelectSubMenu,
	};

	void update(class Parent*);
	void draw();

	void Initialize();
	void Shutdown();

	void moveTo(Parent* parent, Parent::SeqID id);
	void SetSeqID(Parent::SeqID id) { mSeqID = id; }

private:
	void ProcessInput();
	void UpdateMainMenu();

	InputGroup inputUp;
	InputGroup inputDown;
	InputGroup inputRight;
	InputGroup inputLeft;
	InputGroup inputDecision;
	InputGroup inputBack;

	Vec2 mCenterCirclePos;
	float mCenterCircleRadius;
	Vec2 mGameRectCenter;
	Vec2 mCreateStageRectCenter;
	Vec2 mSubMenuRectCenter;

	float mSelectWidth;
	float mSelectHeight;
	float mRectRound;
	ColorF mGameRectColor;
	ColorF mCreateStageRectColor;
	ColorF mSubMenuRectColor;

	MainSelect mSelect;

	Parent::SeqID mSeqID;

	bool mIsRunning;
};
