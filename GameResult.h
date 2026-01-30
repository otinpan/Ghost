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
	void draw(const class Parent* parent);

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

	Font selectFont;

	// result
	void DrawResult(const class Parent* parent);
	Font resultFont{ ConvertToInt((float)0.2 * GetScreenHeight()),Typeface::Black,FontStyle::Bitmap };

	InputGroup inputLeft;
	InputGroup inputRight;
	InputGroup inputL;
	InputGroup inputR;
	InputGroup inputDecision;
};
