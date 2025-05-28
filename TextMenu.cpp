#include"TextMenu.h"
#include"Parent.h"


TextMenu::TextMenu(String text)
	:mIsTextDecide(false)
	, mText(text)
	, mCursorPos(text.size())
	, mTimerNotEditing(StartImmediately::Yes)
{

}

TextMenu::~TextMenu(){
	if (mCreateStage) {
		delete mCreateStage;
		mCreateStage = 0;
	}
}

void TextMenu::Initialize_CreateStage(CreateStage* createstage){
	mTextRectPos = Vec2(0, 0.3);
	mTextRectWidth = 1.5;
	mTextRectHeight = 0.3;
	mTextRectColor = ColorF(0, 0.9);
	mTextColor=ColorF( 0.95 );
	mCursorWidth = 0.005;
	mCursorColor = ColorF(0.8);
	EditingTextColor = ColorF{ Palette::White };
	EditingTextBgColor = ColorF{ Palette::Blue,0.8 };
	HelpTextColor = ColorF{ Palette::Gray };
	MaxTextSize = 15;

	FontSize = 0.12 * GetScreenHeight();
	FontAsset::Register(U"text", FontMethod::MSDF, FontSize, Typeface::Medium);
	HelpFont =Font{ FontMethod::MSDF,FontSize/2,Typeface::Light};

	mCreateStage = createstage;
	
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

	if (mCursorPos > MaxTextSize) {
		while (mCursorPos > MaxTextSize) {
			mText.pop_back();
			mCursorPos--;
		}
		if (KeyBackspace.down()) {
			mText.pop_back();
			mCursorPos--;
		}
		return;
	}
	//Spaceは受け付けない
	if (KeySpace.pressed() || KeySpace.up())return;
	mCursorPos = TextInput::UpdateText(mText, mCursorPos, TextInputMode::AllowBackSpaceDelete);

	//終了
	/////////////////////////////////////

}

bool TextMenu::EndEdit_CreateStage() {
	std::vector<String> stageNames;
	Deserializer<BinaryReader> reader{ U"Stage/StageNames.bin" };
	if (reader) {
		reader(stageNames);
	}
	//もし名前が存在するなら
	auto iter = std::find(stageNames.begin(), stageNames.end(), mText);
	if (*iter == mText) {
		return false;
	}
	mCreateStage->SetStageName(mText);
	mCreateStage->CloseTextMenu();
}


void TextMenu::Draw(float fontSize, const Vec2& posDrawAt)const {
	DrawRect(mTextRectPos, mTextRectWidth, mTextRectHeight, mTextRectColor);

	const RectF textRegion = textboxFont()(mText).region(fontSize, posDrawAt.x, posDrawAt.y-mTextRectHeight/6);


	//テキストを1文字ずつ描画
	Vec2 penPos = textRegion.tl();
	Vec2 CursorPos = penPos;
	{
		const ScopedCustomShader2D shader{
			Font::GetPixelShader(textboxFont().method())
		};

		for (auto [charIndex, glyph] : Indexed(textboxFont().getGlyphs(mText))) {
			const auto glyphRect = glyph.texture.draw(ConvertToView(penPos.movedBy(0, textRegion.h * 3 / 2)) + glyph.getOffset(), mTextColor);
			if (mCursorPos == charIndex) {
				CursorPos = penPos;
			}
			penPos.x += glyph.xAdvance * 2.0 / GetScreenWidth();
		}
	}


	if (mCursorPos == mText.size()) {
		CursorPos = penPos;
	}

	//未変換のテキストを描画
	if (const auto editingText = TextInput::GetEditingText(); editingText) {
		textboxFont()(editingText).region(ConvertToView(CursorPos.movedBy(0, textRegion.h * 1.5))).draw(EditingTextBgColor);
		textboxFont()(editingText).draw(ConvertToView(CursorPos.movedBy(0, textRegion.h * 1.5)), EditingTextColor);
	}

	//カーソル
	if(CursorPos.x<=mTextRectPos.x+mTextRectWidth/2.0f)Line{ ConvertToView(CursorPos.movedBy(0,-textRegion.h * 0.5)),ConvertToView(CursorPos.movedBy(0,textRegion.h)) }.draw(mCursorWidth * GetScreenWidth(), mCursorColor);

	//操作説明
	HelpFont(U"[Enter],[Escape]キーで決定").drawAt(ConvertToView(mTextRectPos.movedBy(0, -mTextRectHeight)), HelpTextColor);
	
}




