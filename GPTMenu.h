#pragma once
#include<Siv3D.hpp>
#include"Parent.h"
#include"CreateStage.h"

class GPTMenu {
public:
	GPTMenu();
	~GPTMenu();

	enum SelectedButton {
		SEND,
		CLOSE,
		NONE
	};

	void Initialize_CreateStage(class CreateStage* createStage);

	void Update(float deltaTime);
	void Draw() const;

private:
	class CreateStage* mCreateStage;

	// 全体
	Vec2 mBackgroundRectPos;  //背景の領域の位置
	float mBackgroundRectWidth;
	float mBackgroundRectHeight;
	ColorF mBackgroundRectColor;

	// 送信ボタン
	Vec2 mSendRectPos;
	float mSelectRectWidth;
	float mSelectRectHeight;

	// 終了
	Vec2 mCloseRectPos;

	Font selectFont;

	// 入力
	Input inputUp;
	Input inputDown;
	Input inputRight;
	Input inputLeft;
	InputGroup inputDecision;

	// selected button
	SelectedButton mSelectedButton = SelectedButton::CLOSE;

	bool EndGPTMenu_CreateStage();
};
