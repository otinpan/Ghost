#pragma once
#include"Common.h"
#include"Parent.h"
#include"Actor.h"
#include"TextMenu.h"

class GameResult {
public:
	GameResult();
	~GameResult();

	void update(class Parent*);
	void draw();

	void Initialize();
	void Shutdown();

	void moveTo(Parent* parent, Parent::SeqID id);
	void SetSeqID(Parent::SeqID id) { mSeqID = id; }

private:
	void ProcessInput();
	void UpdateGameResult();

	Parent::SeqID mSeqID;
	bool mIsRunning;

	std::unique_ptr<TextMenu> mTextMenu;
};
