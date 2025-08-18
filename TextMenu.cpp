#include"TextMenu.h"
#include"Parent.h"
#include<Siv3D.hpp>

TextMenu::TextMenu(String text)
	:mIsTextDecide(false)
	, mText(text)
	, mCursorPos(text.size())
	, mTimerNotEditing(StartImmediately::Yes)
{

}

TextMenu::~TextMenu(){
	mCreateStage = nullptr;
}

void TextMenu::Initialize_CreateStage(CreateStage* createstage){
	mBackgroundRectPos = Vec2(0, 0);
	mBackgroundRectWidth = (float)1.7;
	mBackgroundRectHeight = (float)1.5;
	mBackgroundRectColor = ColorF(0);
	mTextRectPos = Vec2(0, 0.3);
	mTextRectWidth = 1.5;
	mTextRectHeight = 0.3;
	mTextRectColor = ColorF(1);
	mTextColor=ColorF( 0.95 );
	mCursorWidth = 0.005;
	mCursorColor = ColorF(0.8);
	EditingTextColor = ColorF{ Palette::White };
	EditingTextBgColor = ColorF{ Palette::Blue,0.8 };
	HelpTextColor = ColorF{ Palette::Gray };
	MaxTextSize = 20;

	FontSize = 0.09 * GetScreenHeight();
	FontAsset::Register(U"text", FontMethod::MSDF, FontSize, Typeface::Medium);
	HelpFont =Font{ FontMethod::MSDF,FontSize/2,Typeface::Light};

	mCreateStage = createstage;

	for (int i = 0; i < 26; i++) {
		ValidInput.insert((char)('a' + i));
		ValidInput.insert((char)('A' + i));
		ValidInput.insert((char)('0'+(i % 10)));
	}
	ValidInput.insert('_');
	ValidInput.insert('-');

	
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

	mCursorPos = TextInput::UpdateText(mText, mCursorPos, TextInputMode::AllowBackSpaceDelete);
	


	//終了
	/////////////////////////////////////
	if (KeyEnter.pressed()) {
		if(EndEdit_CreateStage())return;
		
	}

}

bool TextMenu::EndEdit_CreateStage() {
	std::vector<String> stageNames;
	Deserializer<BinaryReader> reader{ U"Stage/StageNames.bin" };
	if (reader) {
		reader(stageNames);
	}
	//無効な名前なら
	for (auto c : mText) {
		if (!ValidInput.count(c))return false;
	}

	//もし名前が存在するなら
	auto iter = std::find(stageNames.begin(), stageNames.end(), mText);
	if (iter != stageNames.end()) {
		return false;
	}

	mCreateStage->SetStageName(mText);
	mCreateStage->SetShouldCloseTextMenu(true);
	return true;
}


void TextMenu::Draw(float fontSize)const {
	DrawRoundRect(mBackgroundRectPos, mBackgroundRectWidth, mBackgroundRectHeight,mBackgroundRectWidth/50.0,
		mBackgroundRectColor);
	DrawRectFrame(mTextRectPos, mTextRectWidth, mTextRectHeight,0,0.001, mTextRectColor);

	Vec2 mPos = ConvertToView(Vec2(mTextRectPos.x - mTextRectWidth / 2.1, mTextRectPos.y-mTextRectHeight/1.8));
	const RectF textRegion = textboxFont()(mText)
		.region(fontSize,  mPos.x, mPos.y );


	//テキストを1文字ずつ描画
	Vec2 penPos = textRegion.tl();
	Vec2 CursorPos = penPos;
	{
		const ScopedCustomShader2D shader{
			Font::GetPixelShader(textboxFont().method())
		};

		for (auto [charIndex, glyph] : Indexed(textboxFont().getGlyphs(mText))) {
			const auto glyphRect = glyph.texture.draw(penPos.movedBy(0, -textRegion.h * 3 / 2) + glyph.getOffset(), mTextColor);
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
		textboxFont()(editingText).region(CursorPos.movedBy(0, -textRegion.h * 1.5)).draw(EditingTextBgColor);
		textboxFont()(editingText).draw(CursorPos.movedBy(0, -textRegion.h * 1.5), EditingTextColor);
	}

	//カーソル
	Line{ CursorPos.movedBy(0,-textRegion.h/3.0),CursorPos.movedBy(0,-textRegion.h*1.1) }.draw(mCursorWidth * GetScreenWidth(), mCursorColor);
	
	//操作説明
	HelpFont(U"[Enter]キーで決定").drawAt(ConvertToView(mTextRectPos.movedBy(0, -mTextRectHeight)), HelpTextColor);
	HelpFont(U"アルファベット、-、_、数字以外は無効").drawAt(ConvertToView(mTextRectPos.movedBy(0, -mTextRectHeight*2)), HelpTextColor);
	
}



