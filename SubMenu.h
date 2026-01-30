#pragma once
#include"Common.h"
#include"Parent.h"

class SubMenu {
public:
	SubMenu();
	~SubMenu();

	enum SubSelect {
		SelectChangeWindowSize,
		SelectGameRule,
		SelectCreateRule,
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

	// Rule
	std::vector<TextureAsset> mGameRuleTextures;
	std::vector<TextureAsset> mCreateRuleTextures;
	int mGameRuleIteration = 0;
	int mCreateRuleIteration = 0;
	int mGameRuleSize;
	int mCreateRuleSize;
	bool mIsGameRule=false;
	bool mIsCreateRule = false;
	void UpdateGameRule();
	void UpdateCreateRule();
	void DrawGameRule();
	void DrawCreateRule();

	bool mIsRunning;

	Parent::SeqID mSeqID;
};
