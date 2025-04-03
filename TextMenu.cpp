#include"TextMenu.h"
#include"Parent.h"


TextMenu::TextMenu(String text)
	:mIsTextDecide(false)
	, mText(text)
	, mCursorPos(text.size())
	, mTimerNotEditing(StartImmediately::Yes)
{
	Initialize();
}

TextMenu::~TextMenu(){}

void TextMenu::Initialize(){
	mTextRectPos = Vec2(0, 0.3);
	mTextRectWidth = 0.8;
	mTextRectHeight = 0.3;
	mTextRectColor = ColorF(0, 0.9);
	mTextColor=ColorF( 0.95 );
	mCursorWidth = 0.02;
	mCursorColor = ColorF(Palette::Blue,0.8);
	EditingTextColor = ColorF{ Palette::White };
	EditingTextBgColor = ColorF{ Palette::Blue,0.8 };
	HelpTextColor = ColorF{ Palette::Gray };
}

void TextMenu::Update(float deltaTime) {
	if (TextInput::GetEditingText()) {
		mTimerNotEditing.reset();
	}
	else if (not mTimerNotEditing.isRunning()) {
		mTimerNotEditing.restart();
	}

	if (KeyLeft.down()) {
		mCursorPos = (mCursorPos == 0) ? 0 : mCursorPos - 1;
	}
	if (KeyRight.down()) {
		mCursorPos = Min(mCursorPos + 1, mText.size());
	}

	if (KeyHome.down()) {
		mCursorPos = 0;
	}
	if (KeyEnd.down()) {
		mCursorPos = mText.size();
	}

	mCursorPos = TextInput::UpdateText(mText, mCursorPos, TextInputMode::AllowBackSpaceDelete);
}


void TextMenu::Draw(float fontSize,const Vec2& posDrawAt)const {
	DrawRect(mTextRectPos, mTextRectWidth, mTextRectHeight, mTextRectColor);

	
	const auto textRegion = textboxFont()(mText).regionAt(fontSize, posDrawAt);

	//テキストを1文字ずつ描画
	Vec2 penPos = textRegion.tl();
	Vec2 CursorPos = penPos;
	Print << penPos;

	{
		const ScopedCustomShader2D shader{
			Font::GetPixelShader(textboxFont().method())
		};

		for (auto [charIndex, glyph] : Indexed(textboxFont().getGlyphs(mText))) {
			const auto glyphRect = glyph.texture.draw(ConvertToView(penPos) + glyph.getOffset(), mTextColor);
			if (mCursorPos == charIndex) {
				CursorPos = penPos;
			}
			penPos.x += glyph.xAdvance;
		}
	}


	if (mCursorPos == mText.size()) {
		CursorPos = penPos;
	}

	//未変換のテキストを描画
	if (const auto editingText = TextInput::GetEditingText(); editingText) {
		textboxFont()(editingText).region(ConvertToView(CursorPos)).draw(EditingTextBgColor);
		textboxFont()(editingText).draw(ConvertToView(CursorPos), EditingTextColor);
	}

	
	//カーソル
	Line{ ConvertToView(CursorPos),ConvertToView(CursorPos.movedBy(0,textRegion.h)) }.draw(mCursorWidth * GetScreenWidth(), mCursorColor);

	//操作説明
	textboxFont()(U"[Enter],[Escape]キーで決定"). drawAt(ConvertToView(Vec2{ 0, -0.1 }), HelpTextColor);
}




