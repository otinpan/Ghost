#pragma once
#include<Siv3D.hpp>
#include"Parent.h"
#include"CreateStage.h"

class TextMenu {
public:
	TextMenu(String text);
	~TextMenu();

	void Initialize_CreateStage(class CreateStage* createStage);

	void Update(float deltaTime);
	void Draw(float fontSize) const;

	bool GetIsTextDecide() { return mIsTextDecide; }
	void SetIsTextDecide(bool isNameDecide) { mIsTextDecide = isNameDecide; }
	String GetText() { return mText; }
	void SetName(String text) { mText = text; }
	const Vec2 GetTextRectPos() { return mTextRectPos; }
	const float GetTextRectWidth() { return mTextRectWidth; }
	const float GetTextRectHeight() { return mTextRectHeight; }

	bool editing() const { return TextInput::GetEditingText() || mTimerNotEditing.sF() < 0.5f; }

private:
	class CreateStage* mCreateStage;

	bool mIsTextDecide;
	String mText;
	size_t mCursorPos;
	size_t MaxTextSize;
	Stopwatch mTimerNotEditing;

	Vec2 mBackgroundRectPos;  //背景の領域の位置
	float mBackgroundRectWidth;
	float mBackgroundRectHeight;
	ColorF mBackgroundRectColor;
	Vec2 mTextRectPos;  //Textを表示する領域の位置
	float mTextRectWidth;
	float mTextRectHeight;
	ColorF mTextRectColor;
	ColorF mTextColor;
	ColorF mCursorColor;
	float mCursorWidth;
	ColorF EditingTextColor;
	ColorF EditingTextBgColor;
	ColorF HelpTextColor{ Palette::Gray };

	//End edit
	bool EndEdit_CreateStage();
	
	
	FontAsset textboxFont()const {
		return FontAsset(U"text");
	}

	Font HelpFont;
	int FontSize;

};
