#pragma once
#include"Common.h"
#include"Parent.h"
#include"Actor.h"
#include"TextMenu.h"

class GameResult {
public:
	GameResult(Parent::GameJudgement judge);
	~GameResult();

	enum ResultSelect {
		STAGE_SELECT,
		CONTROLLER_SELECT,
		MAIN_MENU,
		CREATE_STAGE,
	};

	void update(class Parent*);
	void draw();

	void Initialize();
	void Shutdown();

	void moveTo(Parent* parent, Parent::SeqID id);
	void SetSeqID(Parent::SeqID id) { mSeqID = id; }

private:
	void ProcessInput();
	void UpdateGameResult();

	ResultSelect mResultSelect;
	bool IsJumpToGame; // stageselectでgameかcreatestageか

	Parent::GameJudgement mGameJudgement;

	Parent::SeqID mSeqID;
	bool mIsRunning;

	Font resultFont;

	InputGroup inputLeft;
	InputGroup inputRight;
	InputGroup inputL;
	InputGroup inputR;
	InputGroup inputDecision;
};
