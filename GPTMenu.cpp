#include"GPTMenu.h"
#include"Parent.h"


GPTMenu::GPTMenu()
	:mCreateStage(nullptr)
{

}


GPTMenu::~GPTMenu() {
	mCreateStage = nullptr;
}


void GPTMenu::Initialize_CreateStage(CreateStage* createStage) {
	mCreateStage = createStage;

	// 全体設定
	mBackgroundRectPos = Vec2(0, 0);
	mBackgroundRectWidth = (float)1.7;
	mBackgroundRectHeight = (float)1.8;
	mBackgroundRectColor = ColorF(0);

	// ボタン設定
	mSendRectPos = Vec2(0.4f, -0.7f);
	mSelectRectHeight = 0.18f;
	mSelectRectWidth = 0.5f;

	mCloseRectPos = Vec2(-0.4f, -0.7f);

	// 入力
	inputUp = KeyW;
	inputDown = KeyS;
	inputRight = KeyD;
	inputLeft = KeyA;
	inputDecision = KeySpace|KeyEnter;

	int FontSize = 0.09 * GetScreenHeight();
	selectFont = Font{ FontMethod::MSDF,FontSize / 2,Typeface::Light };
}

void GPTMenu::Update(float deltaTime) {
	RectF sendRect = RectF(Arg::center(ConvertToView(mSendRectPos)),
		mSelectRectWidth * GetScreenWidth() / 2.0f,
		mSelectRectHeight * GetScreenHeight() / 2.0f);

	RectF closeRect = RectF(Arg::center(ConvertToView(mCloseRectPos)),
		mSelectRectWidth * GetScreenWidth() / 2.0f,
		mSelectRectHeight * GetScreenHeight() / 2.0f);

	switch (mSelectedButton) {
	case SelectedButton::NONE:
		if (inputLeft.down()) {
			mSelectedButton = SelectedButton::CLOSE;
		}
		if (inputRight.down()) {
			mSelectedButton = SelectedButton::SEND;
		}
		break;
	case SelectedButton::SEND:
		if (inputLeft.down()) {
			mSelectedButton = SelectedButton::CLOSE;
		}
		break;
	case SelectedButton::CLOSE:
		if (inputDecision.down()) {
			EndGPTMenu_CreateStage();
			return;
		}
		if (inputRight.down()) {
			mSelectedButton = SelectedButton::SEND;
		}
		break;
	}
	

	if (sendRect.leftClicked()) {
		// to do: GPTへ送信
	}
	if (closeRect.leftClicked()) {
		if(EndGPTMenu_CreateStage())return;
	}
}

bool GPTMenu::EndGPTMenu_CreateStage() {
	mCreateStage->SetShouldCloseGPTMenu(true);
	return true;
}


void GPTMenu::Draw() const {
	DrawRoundRect(mBackgroundRectPos, mBackgroundRectWidth, mBackgroundRectHeight, mBackgroundRectWidth / 50.0,
		mBackgroundRectColor);

	std::map < SelectedButton, Vec2> pos;
	std::map<SelectedButton, String> text;
	pos[SEND] = mSendRectPos;
	pos[CLOSE] = mCloseRectPos;
	text[SEND] = U"Send";
	text[CLOSE] = U"Close";

	// 描画
	for (auto [mode, p] : pos) {
		DrawRect(p, mSelectRectWidth, mSelectRectHeight, ColorF(1.0f));
		selectFont(text[mode]).drawAt(ConvertToView(p), ColorF(0.0f));
	}
	DrawRectFrame(pos[mSelectedButton], mSelectRectWidth, mSelectRectHeight, 0.005f, 0.005 , ColorF(1.0f,1.0f,0.0f));


}
