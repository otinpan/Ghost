#pragma once
#include"Parent.h"
#include"Actor.h"

class StageSelect {
public:
	StageSelect();
	~StageSelect();

	void update(class Parent*);
	void draw();

	void Initialize();
	void Shutdown();

	void moveTo(Parent* parent, Parent::SeqID id);
	void SetSeqID(Parent::SeqID id) { mSeqID = id; }

private:
	void ProcessInput();
	void UpdateStageSelect();

	InputGroup inputUp;
	InputGroup inputDown;
	InputGroup inputLeft;
	InputGroup inputRight;
	InputGroup inputDecision;
	InputGroup inputBack;

	bool mIsRunning;

	Parent::SeqID mSeqID;
	
};
