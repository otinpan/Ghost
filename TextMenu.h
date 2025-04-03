#pragma once
#include<Siv3D.hpp>
#include"Parent.h"

class TextMenu {
public:
	TextMenu(String text);
	~TextMenu();

	void Initialize();

	void Update(float deltaTime);
	void Draw(float fontSize,const Vec2& posDrawAt) const;

	bool GetIsTextDecide() { return mIsTextDecide; }
	void SetIsTextDecide(bool isNameDecide) { mIsTextDecide = isNameDecide; }
	String GetText() { return mText; }
	void SetName(String text) { mText = text; }
	const Vec2 GetTextRectPos() { return mTextRectPos; }

	bool editing() const { return TextInput::GetEditingText() || mTimerNotEditing.sF() < 0.5f; }

private:
	bool mIsTextDecide;
	String mText;
	size_t mCursorPos;
	Stopwatch mTimerNotEditing;

	Vec2 mTextRectPos;
	float mTextRectWidth;
	float mTextRectHeight;
	ColorF mTextRectColor;
	ColorF mTextColor;
	ColorF mCursorColor;
	float mCursorWidth;
	ColorF EditingTextColor;
	ColorF EditingTextBgColor;
	ColorF HelpTextColor{ Palette::Gray };

	
	FontAsset textboxFont()const {
		return FontAsset(U"text");
	}


};
