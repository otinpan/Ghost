#pragma once
#include"Common.h"
#include"Parent.h"

class ChangeWindowSize {
public:
	ChangeWindowSize();
	~ChangeWindowSize();

	void update(class Parent*);
	void draw();

	void Initialize();
	void Shutdown();

	void moveTo(Parent* parent, Parent::SeqID id);
	void SetSeqID(Parent::SeqID id) { mSeqID = id; }

private:
	void ProcessInput();
	void UpdateChangeWindowSize();

	Parent::SeqID mSeqID;
	bool mIsRunning;

	Font HelpFont;
};
