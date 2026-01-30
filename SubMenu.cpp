#include"SubMenu.h"

SubMenu::SubMenu()
	:mSeqID(Parent::SEQ_NONE)
	, mIsRunning(true)
	, mSelect(SubMenu::SelectChangeWindowSize)
{
	Initialize();
}

SubMenu::~SubMenu() {
	Shutdown();
}

void SubMenu::Initialize() {
	Scene::SetBackground(ColorF(180.0 / 255.0));
	inputLeft = KeyA;
	inputUp = KeyW;
	inputDown = KeyS;
	inputRight = KeyD;
	inputDecision = KeySpace;
	inputBack = KeyBackspace;

	mUp = mSelectUp = 0.95;
	mLeft = mSelectLeft = -0.95;
	mWidth = mHeight=mSelectHeight=0.95 * 2.0;
	mSelectWidth = 1.4f;

	mSelectRectWidth = mSelectWidth * 0.80;

	mSelectRectHeight = mSelectHeight / 12.0;
	mSelectRectRound = mSelectWidth / 35.0f;
	mSelectRectColor = ColorF(1.0);

	float fs = mSelectRectHeight * GetScreenHeight() * 0.25;
	int32 fontSize = (int32)fs;
	FontAsset::Register(U"Font_SubMenu", fontSize, Typeface::Medium);

	// rule
	TextureAsset::Load(U"rule_game");
	TextureAsset::Load(U"rule_escapee1");
	TextureAsset::Load(U"rule_escapee2");
	TextureAsset::Load(U"rule_ghost1");
	TextureAsset::Load(U"rule_object");
	mGameRuleTextures.emplace_back(TextureAsset(U"rule_game"));
	mGameRuleTextures.emplace_back(TextureAsset(U"rule_escapee1"));
	mGameRuleTextures.emplace_back(TextureAsset(U"rule_escapee2"));
	mGameRuleTextures.emplace_back(TextureAsset(U"rule_ghost1"));
	mGameRuleTextures.emplace_back(TextureAsset(U"rule_object"));
	mGameRuleSize = mGameRuleTextures.size();

	TextureAsset::Load(U"rule_create");
	TextureAsset::Load(U"rule_AI_create");
	TextureAsset::Load(U"rule_minigame");
	mCreateRuleTextures.emplace_back(TextureAsset(U"rule_create"));
	mCreateRuleTextures.emplace_back(TextureAsset(U"rule_AI_create"));
	mCreateRuleTextures.emplace_back(TextureAsset(U"rule_minigame"));
	mCreateRuleSize = mCreateRuleTextures.size();
}

void SubMenu::update(Parent* parent) {
	if (mIsRunning) {
		if (mSeqID != Parent::SEQ_NONE) {
			moveTo(parent, mSeqID);
		}
		ProcessInput();
		UpdateSubMenu();
		draw();
	}
}

void SubMenu::ProcessInput() {

}

void SubMenu::UpdateSubMenu() {
	if (mIsGameRule) {
		UpdateGameRule();
		return;
	}

	if (mIsCreateRule) {
		UpdateCreateRule();
		return;
	}

	switch (mSelect) {
	case SubMenu::SelectChangeWindowSize:
		if (inputDecision.down()) {
			mSeqID = Parent::SEQ_CHANGEWINDOWSIZE;
		}
		if (inputDown.down() || KeyDown.down()) {
			mSelect = SubMenu::SelectGameRule;
		}
		break;
	case  SubMenu::SelectGameRule:
		if (inputDecision.down()) {
			mIsGameRule = true;
		}
		if (inputDown.down() || KeyDown.down()) {
			mSelect = SubMenu::SelectCreateRule;
		}
		if (inputUp.down() || KeyUp.down()) {
			mSelect = SubMenu::SelectChangeWindowSize;
		}
		break;
	case SubMenu::SelectCreateRule:
		if (inputDecision.down()) {
			mIsCreateRule = true;
		}
		if (inputUp.down() || KeyDown.down()) {
			mSelect = SubMenu::SelectGameRule;
		}
		break;
	default:
		break;
	}

	if (inputBack.down()) {
		mSeqID = Parent::SEQ_MAINMENU;
	}

}

void SubMenu::UpdateGameRule() {
	if (KeyLeft.down() || KeyA.down()) {
		if (mGameRuleIteration != 0) {
			mGameRuleIteration--;
		}
	}

	if (KeyRight.down() || KeyD.down()) {
		if (mGameRuleIteration < mGameRuleSize - 1) {
			mGameRuleIteration++;
		}
	}

	if (inputBack.down()) {
		mIsGameRule = false;
		mGameRuleIteration = 0;
	}

	return;
}

void SubMenu::UpdateCreateRule() {
	if (KeyLeft.down() || KeyA.down()) {
		if (mCreateRuleIteration != 0) {
			mCreateRuleIteration--;
		}
	}

	if (KeyRight.down() || KeyD.down()) {
		if (mCreateRuleIteration < mCreateRuleSize - 1) {
			mCreateRuleIteration++;
		}
	}

	if (inputBack.down()) {
		mIsCreateRule = false;
		mCreateRuleIteration = 0;
	}

	return;
}


void SubMenu::draw() {
	std::map<SubSelect, Vec2> pos;
	std::map<SubSelect, String> text;
	float eachHeight = 0.2f;
	
	pos[SubMenu::SelectChangeWindowSize ]
		= Vec2(mSelectLeft + mSelectRectWidth / 2.0, mSelectUp - eachHeight / 2.0);
	pos[SubMenu::SelectGameRule]
		= Vec2(mSelectLeft + mSelectRectWidth / 2.0f, mSelectUp - eachHeight * 3.0f / 2.0f);
	pos[SubMenu::SelectCreateRule]
		= Vec2(mSelectLeft + mSelectRectWidth / 2.0f, mSelectUp - eachHeight * 5.0f / 2.0f);

	text[SubMenu::SelectChangeWindowSize] = U"windowのサイズを変更";
	text[SubMenu::SelectGameRule] = U"ゲームのルール";
	text[SubMenu::SelectCreateRule] = U"ステージ作成のルール";
	for (auto [mode, p] : pos) {
		DrawRoundRect(p, mSelectRectWidth, mSelectRectHeight, mSelectRectRound, mSelectRectColor);
		FontAsset(U"Font_SubMenu")(text[mode]).draw(Arg::center(ConvertToView(p)), ColorF(0));
	}
	DrawRoundRectFrame(
			pos[mSelect],
			mSelectRectWidth,
			mSelectRectHeight,
			mSelectRectRound,
			0,
			mSelectRectHeight / 40.0f,
			mSelectRectColor
	);

	if (mIsGameRule) {
		DrawGameRule();
		return;
	}

	if (mIsCreateRule) {
		DrawCreateRule();
		return;
	}
}


void SubMenu::DrawGameRule() {
	std::vector<float> ruleCircleX(mGameRuleSize);
	float left = -0.5f;
	float right = 0.5f;
	float eachCircleWidth = (float)(right - left) / mGameRuleSize;
	float radius = 0.01f;
	DrawRect(Vec2(0.0f, 0.0f), 1.85f, 1.85f, ColorF(0.0f));
	DrawTexture(mGameRuleTextures[mGameRuleIteration], Vec2(0, 0), 0.9f, 0.9f, 0.0f);
	for (int i = 0; i < mGameRuleSize; i++) {
		ColorF color = ColorF(1.0f);
		if (mGameRuleIteration == i)color = ColorF(1.0f, 1.0f, 102.0f / 255.0f);
		// circle
		DrawCircle(
			Vec2(left + eachCircleWidth * i + eachCircleWidth / 2.0f, -(1.7f / 2.0f)),
			radius * 1.2f,
			ColorF(0.0f)
		);
		DrawCircle(
			Vec2(left + eachCircleWidth * i + eachCircleWidth / 2.0f, -(1.7f / 2.0f)),
			radius,
			color
		);

	}
}

void SubMenu::DrawCreateRule() {
	std::vector<float> ruleCircleX(mCreateRuleSize);
	float left = -0.5f;
	float right = 0.5f;
	float eachCircleWidth = (float)(right - left) / mCreateRuleSize;
	float radius = 0.01f;

	DrawRect(Vec2(0.0f, 0.0f), 1.85f, 1.85f, ColorF(0.0f));
	DrawTexture(mCreateRuleTextures[mCreateRuleIteration], Vec2(0, 0), 0.9f, 0.9f, 0.0f);
	for (int i = 0; i < mCreateRuleSize; i++) {
		ColorF color = ColorF(1.0f);
		if (mCreateRuleIteration == i)color = ColorF(1.0f, 1.0f, 102.0f / 255.0f);
		// circle
		DrawCircle(
			Vec2(left + eachCircleWidth * i + eachCircleWidth / 2.0f, -(1.7f / 2.0f)),
			radius * 1.2f,
			ColorF(0.0f)
		);
		DrawCircle(
			Vec2(left + eachCircleWidth * i + eachCircleWidth / 2.0f, -(1.7f / 2.0f)),
			radius,
			color
		);

	}

}

void SubMenu::Shutdown() {
	TextureAsset::Release(U"rule_game");
	TextureAsset::Release(U"rule_escapee1");
	TextureAsset::Release(U"rule_escapee2");
	TextureAsset::Release(U"rule_ghost1");
	TextureAsset::Release(U"rule_object");
}

void SubMenu::moveTo(Parent* parent, Parent::SeqID id) {
	if (id == Parent::SEQ_MAINMENU)parent->moveTo(Parent::SEQ_MAINMENU, Parent::SEQ_SUBMENU);
	if (id == Parent::SEQ_STAGESELECT)parent->moveTo(Parent::SEQ_STAGESELECT, Parent::SEQ_SUBMENU);
	if (id == Parent::SEQ_SUBMENU)parent->moveTo(Parent::SEQ_SUBMENU, Parent::SEQ_SUBMENU);
	if (id == Parent::SEQ_GAME)parent->moveTo(Parent::SEQ_GAME, Parent::SEQ_SUBMENU);
	if (id == Parent::SEQ_CREATESTAGE)parent->moveTo(Parent::SEQ_CREATESTAGE, Parent::SEQ_SUBMENU);
	if (id == Parent::SEQ_GAMERESULT)parent->moveTo(Parent::SEQ_GAMERESULT, Parent::SEQ_SUBMENU);
	if (id == Parent::SEQ_CHANGEWINDOWSIZE)parent->moveTo(Parent::SEQ_CHANGEWINDOWSIZE, Parent::SEQ_SUBMENU);
}
