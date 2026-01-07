#pragma once
#include"Parent.h"
#include"Common.h"
#include"Actor.h"


class RegisterController {
public:
	RegisterController();
	~RegisterController();

	void update(class Parent*);
	void draw();

	void Initialize();
	void Shutdown();

	void moveTo(Parent* parent, Parent::SeqID id);
	void SetSeqID(Parent::SeqID id) { mSeqID = id; }


private:
	void ProcessInput();
	void UpdateRegisterController();

	// コントローラー

	Parent::SeqID mSeqID;
	bool mIsRunning;
};
