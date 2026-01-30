#include"GameResult.h"

GameResult::GameResult(Parent::GameJudgement judge)
	:mSeqID(Parent::SEQ_NONE)
	, mIsRunning(true)
	, mGameJudgement(judge)
	, mResultSelect(ResultSelect::STAGE_SELECT)
{
	Initialize();
}

GameResult::~GameResult() {
	TextureAsset::Release(U"ghost");
	TextureAsset::Release(U"escapee1");
	TextureAsset::Release(U"escapee2");
	TextureAsset::Release(U"escapee3");
}

void GameResult::Initialize() {
	Scene::SetBackground(ColorF(0.95));
	inputRight = KeyD;
	inputLeft = KeyA;
	inputR = KeyRight;
	inputL = KeyLeft;
	inputDecision = KeySpace;

	mResultSelect = ResultSelect::STAGE_SELECT;
	int FontSize = 0.1 * GetScreenHeight();
	selectFont = Font{ FontMethod::MSDF,FontSize / 2,Typeface::Black };

	TextureAsset::Load(U"ghost");
	TextureAsset::Load(U"escapee1");
	TextureAsset::Load(U"escapee2");
	TextureAsset::Load(U"escapee3");
}

void GameResult::update(Parent* parent) {
	if (mIsRunning) {
		if (mSeqID != Parent::SEQ_NONE) {
			moveTo(parent, mSeqID);
		}
	}
	ClearPrint();
	ProcessInput();
	UpdateGameResult();
	draw(parent);
}

void GameResult::ProcessInput() {

}

void GameResult::UpdateGameResult() {
	float deltaTime = Scene::DeltaTime();

	switch (mResultSelect) {
	case ResultSelect::STAGE_SELECT:
		if (inputRight.down() || inputR.down()) {
			mResultSelect = ResultSelect::CONTROLLER_SELECT;
		}
		if (inputDecision.down()) {
			SetSeqID(Parent::SeqID::SEQ_STAGESELECT);
			IsJumpToGame = true;
		}
		break;
	case ResultSelect::CONTROLLER_SELECT:
		if (inputLeft.down() || inputL.down()) {
			mResultSelect = ResultSelect::STAGE_SELECT;
		}
		if (inputRight.down() || inputR.down()) {
			mResultSelect = ResultSelect::MAIN_MENU;
		}
		if (inputDecision.down()) {
			SetSeqID(Parent::SeqID::SEQ_REGISTERCONTROLLER);
		}
		break;
	case ResultSelect::MAIN_MENU:
		if (inputLeft.down() || inputL.down()) {
			mResultSelect = ResultSelect::CONTROLLER_SELECT;
		}
		if (inputRight.down() || inputR.down()) {
			mResultSelect = ResultSelect::CREATE_STAGE;
		}
		if (inputDecision.down()) {
			SetSeqID(Parent::SeqID::SEQ_MAINMENU);
		}
		break;
	case ResultSelect::CREATE_STAGE:
		if (inputLeft.down() || inputL.down()) {
			mResultSelect = ResultSelect::MAIN_MENU;
		}
		if (inputDecision.down()) {
			SetSeqID(Parent::SeqID::SEQ_STAGESELECT);
			IsJumpToGame = false;
		}
	}
}

void GameResult::draw(const Parent* parent) {
	Scene::SetBackground(ColorF(0.7));
	std::map<ResultSelect, Vec2> pos;
	std::map<ResultSelect, String> text;


	float width = 1.9f;
	float eachWidth = width / 4.0f;
	float left = -1.0+(2.0 - width) / 2.0f;
	float posY = -0.7f;
	pos[STAGE_SELECT] = Vec2(left + eachWidth / 2.0f, posY);
	pos[CONTROLLER_SELECT] = Vec2(left + eachWidth*3.0f / 2.0f, posY);
	pos[MAIN_MENU] = Vec2(left + eachWidth *5.0f/ 2.0f, posY);
	pos[CREATE_STAGE] = Vec2(left + eachWidth *7.0f/ 2.0f, posY);

	text[STAGE_SELECT] = U"STAGE";
	text[CONTROLLER_SELECT] = U"CONTROLLER";
	text[MAIN_MENU] = U"HOME";
	text[CREATE_STAGE] = U"CREATE";

	float rectWidth = eachWidth*0.85f;
	float rectHeight = 0.35f;

	for (auto [mode, p] : pos) {
		DrawRect(p, rectWidth, rectHeight, ColorF(1.0f));
		DrawRectFrame(p, rectWidth, rectHeight,0.0f,0.008f, ColorF(0.0f));
		selectFont(text[mode]).drawAt(ConvertToView(p), ColorF(0.0f));
	}

	DrawRectFrame(pos[mResultSelect], rectWidth, rectHeight, 0.01f, 0.01f,
		ColorF((float)240/255.0f,(float)230/255,(float)140/255));

	DrawResult(parent);
}

void GameResult::DrawResult(const Parent* parent) {
	float posY = 0.1f;
	const auto& controllers = parent->getControllers();
	int n = controllers.size();

	// test
	/*mGameJudgement = Parent::GameJudgement::ESCAPEES_WIN;
	n = 4;*/
	String res;
	if (mGameJudgement == Parent::GameJudgement::GHOST_WIN) {
		res = U"GHOST WIN";
		DrawTexture(TextureAsset(U"ghost"), Vec2(0.0f, posY), 0.3f, 0.3f,0.0f);
	}
	else if (mGameJudgement == Parent::GameJudgement::DRAW) {
		res = U"DRAW";
		DrawTexture(TextureAsset(U"ghost"), Vec2(-0.4f, posY), 0.3f, 0.3f, 0.0f);
		switch (n) {
		case 2:
			DrawTexture(TextureAsset(U"escapee1"), Vec2(0.4f, posY), 0.3f, 0.3f, 0.0f);
			break;
		case 3:
			DrawTexture(TextureAsset(U"escapee1"), Vec2(0.3f, posY), 0.2f, 0.2f, 0.0f);
			DrawTexture(TextureAsset(U"escapee2"), Vec2(0.7f,posY), 0.2f, 0.2f, 0.0f);
			break;
		case 4:
			DrawTexture(TextureAsset(U"escapee1"), Vec2(0.2f, posY), 0.15f, 0.15f, 0.0f);
			DrawTexture(TextureAsset(U"escapee2"), Vec2(0.5f, posY), 0.15f, 0.15f, 0.0f);
			DrawTexture(TextureAsset(U"escapee3"), Vec2(0.8f, posY), 0.15f, 0.15f, 0.0f);
			break;
		default:
			break;
		}
	}
	else {
		res = U"ESCAPEES WIN";
		switch (n) {
		case 2:
			DrawTexture(TextureAsset(U"escapee1"), Vec2(0.0f, posY), 0.3f, 0.3f, 0.0f);
			break;
		case 3:
			DrawTexture(TextureAsset(U"escapee1"), Vec2(-0.3f, posY), 0.3f, 0.3f, 0.0f);
			DrawTexture(TextureAsset(U"escapee2"), Vec2(0.3f, posY), 0.3f, 0.3f, 0.0f);
			break;
		case 4:
			DrawTexture(TextureAsset(U"escapee1"), Vec2(-0.5f, posY), 0.2f, 0.2f, 0.0f);
			DrawTexture(TextureAsset(U"escapee2"), Vec2(0.0f, posY), 0.2f, 0.2f, 0.0f);
			DrawTexture(TextureAsset(U"escapee3"), Vec2(0.5f, posY), 0.2f, 0.2f, 0.0f);
			break;
		}
	}

	resultFont(res).drawAt(ConvertToView(Vec2(0.0f, 0.8f)), ColorF(0.0f));
}



void GameResult::Shutdown() {
}



void GameResult::moveTo(Parent* parent, Parent::SeqID id) {
	if (id == Parent::SEQ_MAINMENU)parent->moveTo(Parent::SEQ_MAINMENU, Parent::SEQ_GAMERESULT);
	if (id == Parent::SEQ_STAGESELECT) {
		parent->setStageSelectGame(IsJumpToGame);
		parent->moveTo(Parent::SEQ_STAGESELECT, Parent::SEQ_GAMERESULT);
		parent->setControllers(parent->getControllers());
	}
	if (id == Parent::SEQ_REGISTERCONTROLLER)parent->moveTo(Parent::SEQ_REGISTERCONTROLLER, Parent::SEQ_GAMERESULT);
	if (id == Parent::SEQ_CREATESTAGE)parent->moveTo(Parent::SEQ_CREATESTAGE, Parent::SEQ_GAMERESULT);
	if (id == Parent::SEQ_GAME)parent->moveTo(Parent::SEQ_GAME, Parent::SEQ_GAMERESULT);
	if (id == Parent::SEQ_GAMERESULT)parent->moveTo(Parent::SEQ_GAMERESULT, Parent::SEQ_GAMERESULT);
	if (id == Parent::SEQ_CHANGEWINDOWSIZE)parent->moveTo(Parent::SEQ_CHANGEWINDOWSIZE, Parent::SEQ_GAMERESULT);
}
