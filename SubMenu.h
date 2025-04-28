#pragma once
#include"Common.h"
#include"Parent.h"

class SubMenu {
public:
	SubMenu();
	~SubMenu();

	enum SubSelect {
		SelectChangeWindowSize,
	};

	void update(class Parent*);
	void draw();

	void Initialize();
	void Shutdown();

	void moveTo(Parent* parent, Parent::SeqID id);
	void SetSeqID(Parent::SeqID id) { mSeqID = id; }

private:
	void ProcessInput();
	void UpdateSubMenu();

	Vec2 mChangeWindowSizeRectCenter;
	float mSelectRectWidth;
	float mSelectRectHeight;
	float mSelectRectRound;
	ColorF mSelectRectColor;
	//描画領域
	float mUp;
	float mLeft; 
	float mWidth;
	float mHeight;
	//SubMenuバーの描画領域
	float mSelectLeft;
	float mSelectUp;
	float mSelectWidth;
	float mSelectHeight;

	SubSelect mSelect;

	InputGroup inputUp;
	InputGroup inputDown;
	InputGroup inputRight;
	InputGroup inputLeft;
	InputGroup inputDecision;
	InputGroup inputBack;

	bool mIsRunning;

	Parent::SeqID mSeqID;
};
