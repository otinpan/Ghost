#include<Siv3D.hpp>
#include"Game.h"
#include<algorithm>
#include"CircleComponent.h"
#include"SpriteComponent.h"
#include"TriangleComponent.h"
#include"Stage.h"
#include"Ghost_Game.h"
#include"Escapee_Game.h"
#include"DrawingComponent.h"


Game::Game(String selectedStageName,std::vector<Controller::ControllerType> controllers)
	:mUpdatingActors(false)
	, mIsRunning(true)
	, mIsHitstop(false)
	, HitstopTime(0.0f)
	, mSeqID(Parent::SEQ_NONE)
	, mSelectedStageName(selectedStageName)
	, mGameTime(300.0f)
	, mIsPaused(false)
	, mIsTimeUp(false)
	, mEscapee1(nullptr)
	, mEscapee2(nullptr)
	, mEscapee3(nullptr)
	, mGhost(nullptr)
	, mControllers(controllers)
{
	Initialize();
}

Game::~Game() {
	Shutdown();
}

bool Game::Initialize() {
	Scene::SetBackground(ColorF((float)100 / 255));
	LoadData();

	vs2D = HLSL{ U"example/shader/hlsl/default2d.hlsl", U"VS" }
	| GLSL{ U"example/shader/glsl/default2d.vert", {{U"VSConstants2D", 0}} };
	ps2DTexture = HLSL{ U"example/shader/hlsl/multi_texture_mask.hlsl", U"PS" }
	| GLSL{ U"example/shader/glsl/multi_texture_mask.frag", {{U"PSConstants2D", 0}} };

	if (not vs2D || not ps2DTexture) {
		throw Error{ U"Failed to load a shader file" };
	}

	renderTexture = RenderTexture{ Scene::Size() };
	renderTextureLight = RenderTexture{ Scene::Size() };


	// Pause
	mPauseMode = PauseSelectedMode::CONTINUE;
	int FontSize = 0.09 * GetScreenHeight();
	pauseFont = Font{ FontMethod::MSDF,FontSize / 2,Typeface::Light };


	return true;
}

void Game::update(Parent* parent) {
	if (mIsRunning) {
		// 終了判定
		if (mIsGameEnd) {
			parent->setGameJudgement(mJudgement);
			mSeqID = Parent::SeqID::SEQ_GAMERESULT;
		}
		if (mSeqID != Parent::SEQ_NONE) {
			moveTo(parent, mSeqID);
		}

		ProcessInput();
		UpdateGame();
		draw();
	}
}

void Game::ProcessInput() {
	const std::vector<Input> keyState = Keyboard::GetAllInputs();

	mUpdatingActors = true;
	for (auto actor : mActors) {
		actor->ProcessInput(keyState);
	}

	mUpdatingActors = false;
}

void Game::UpdateGame() {
	float deltaTime = Scene::DeltaTime();
	if (mIsPaused) {
		// pauseの関数作成
		UpdatePause(deltaTime);
		return;
	}

	if (mIsHitstop) {
		UpdateHitstop(deltaTime);
		return;
	}


	// timer更新
	UpdateTimer(deltaTime);
	// 終了判定
	CheckIsGameEnd();



	mUpdatingActors = true;
	for (auto actor : mActors) {
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	for (auto pending : mPendingActors) {
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	std::vector<Actor*> deadActors;
	for (auto actor : mActors) {
		if (actor->GetState() == Actor::EDead) {
			deadActors.emplace_back(actor);
		}
	}

	for (auto actor : deadActors) {
		delete actor;
	}

	mStage->Update_Game(deltaTime);

}

void Game::SetHitstop(float hitstopTime) {
	mHitstopTime = 0.0f;
	HitstopTime = hitstopTime;
	mIsHitstop = true;
}

void Game::UpdateHitstop(float deltaTime) {
	if (mIsHitstop) {
		if (mHitstopTime > HitstopTime)mIsHitstop = false;
		else mHitstopTime += deltaTime;
	}
}


void Game::draw() {
	renderTexture.clear(ColorF(0));
	renderTextureLight.clear(ColorF(0));



	// 描画する領域を指定
	{
		const ScopedRenderTarget2D target{ renderTextureLight };
		for (auto& drawing : mDrawings_Front) {
			drawing->Draw();
		}

	}
	renderTextureLight. draw(Vec2(0,0));

	// 影響を受けないActorの描画
	{
		for (auto& drawing : mDrawings_Unaffected) {
			drawing->Draw();
		}
	}

	// Background
	{
		const ScopedRenderTarget2D target{ renderTexture };
		mStage->Draw_Game();
		for (auto& drawing : mDrawings_Back) {
			drawing->Draw();
		}
	}


	Graphics2D::SetPSTexture(1, renderTextureLight);
	{
		{
			const ScopedCustomShader2D shader{ vs2D,ps2DTexture };
			renderTexture.draw(Vec2(0,0));
		}
	}

	// Timerの表示
	String timeStr = U"{:02}:{:02}"_fmt(mGameMin, mGameSec);
	mTimerFont(timeStr)
		.draw(Arg::center(ConvertToView(Vec2(0.0f, 0.93f))), ColorF(1.0f));

	if (mIsPaused) {
		DrawPause();
	}
	/*for (auto& drawing : mDrawings_Front) {
		drawing->Draw();
	}
	for (auto& drawing : mDrawings_Unaffected) {
		drawing->Draw();
	}
	for (auto& drawing : mDrawings_Back) {
		//Print << U"front";
		drawing->Draw();
	}*/

}

void Game::LoadData() {

	// Assetロード
	TextureAsset::Load(U"brock_stone");
	TextureAsset::Load(U"borck_grass");
	TextureAsset::Load(U"borck_wood");
	TextureAsset::Load(U"candle");
	TextureAsset::Load(U"key");
	TextureAsset::Load(U"treasure");
	TextureAsset::Load(U"battery");



	mStage = new Stage(1.85f,1.85f);

	const FilePath path = U"Stage/" + mSelectedStageName + U"/Data.bin";
	mStage->Initialize_Game(this,path);
	// todo playerのコンストラクタの引数にコントローラーを渡す
	if (mControllers.size() >= 1) {
		mGhost = new Ghost_Game(Vec2({ (float)mStage->GetLeft() +
			mStage->GetGhostIteration().second * mStage->GetRectWidth() + mStage->GetRectWidth() / 2,
			(float)mStage->GetUp() -
			(mStage->GetGhostIteration().first + 1) * mStage->GetRectHeight() + mStage->GetRectHeight() / 2 }),
			mStage->GetGhostSpeed(),
			mControllers[0]
		);
		mGhost->InitializePlayer_Game(this);
	}

	if (mControllers.size() >= 2) {
		mEscapee1 = new Escapee_Game(Vec2({ (float)mStage->GetLeft() +
			mStage->GetEscapee1Iteration().second * mStage->GetRectWidth() + mStage->GetRectWidth() / 2,
			(float)mStage->GetUp() -
			(mStage->GetEscapee1Iteration().first + 1) * mStage->GetRectHeight() + mStage->GetRectHeight() / 2 }),
			mStage->GetGhostSpeed(),
			1,
			mControllers[1]);
		mEscapee1->InitializePlayer_Game(this);
	}
	if (mControllers.size() >= 3) {
		mEscapee2 = new Escapee_Game(Vec2({ (float)mStage->GetLeft() +
			mStage->GetEscapee2Iteration().second * mStage->GetRectWidth() + mStage->GetRectWidth() / 2,
			(float)mStage->GetUp() -
			(mStage->GetEscapee2Iteration().first + 1) * mStage->GetRectHeight() + mStage->GetRectHeight() / 2 }),
			mStage->GetGhostSpeed(),
			2,
			mControllers[2]);
		mEscapee2->InitializePlayer_Game(this);
	}
	if (mControllers.size() >= 4) {
		mEscapee3 = new Escapee_Game(Vec2({ (float)mStage->GetLeft() +
			mStage->GetEscapee3Iteration().second * mStage->GetRectWidth() + mStage->GetRectWidth() / 2,
			(float)mStage->GetUp() -
			(mStage->GetEscapee3Iteration().first + 1) * mStage->GetRectHeight() + mStage->GetRectHeight() / 2 }),
			mStage->GetGhostSpeed(),
			3,
			mControllers[3]);
		mEscapee3->InitializePlayer_Game(this);
	}

}

void Game::UpdatePause(float deltaTime) {
	// Gameに戻る
	if (inputPause.down()||inputBack.down()) {
		mIsPaused = false;
	}
	switch (mPauseMode) {
	case CONTINUE:
		if (inputDown.down()) {
			mPauseMode = MAIN_MENU;
			break;
		}
		if (inputDecision.down()) {
			mIsPaused = false;
			break;
		}
		break;
	case MAIN_MENU:
		if (inputUp.down()) {
			mPauseMode = CONTINUE;
			break;
		}
		if (inputDown.down()) {
			mPauseMode = STAGE_SELECT;
			break;
		}
		if (inputDecision.down()) {
			SetSeqID(Parent::SeqID::SEQ_MAINMENU);
			break;
		}
		break;
	case STAGE_SELECT:
		if (inputUp.down()) {
			mPauseMode = MAIN_MENU;
			break;
		}
		if (inputDown.down()) {
			mPauseMode = RULE;
			break;
		}
		if (inputDecision.down()) {
			SetSeqID(Parent::SeqID::SEQ_STAGESELECT);
			break;
		}
		break;
	case RULE:
		if (inputUp.down()) {
			mPauseMode = STAGE_SELECT;
			break;
		}
		if (inputDecision.down()) {
			break;
		}
		break;
	default:
		break;
	}
}



void Game::DrawPause() {
	std::map<Game::PauseSelectedMode, Vec2> pos;
	std::map<Game::PauseSelectedMode, String> text;
	float width = 1.5f;
	float height = 1.5f;
	float modeHeight = 1.3;
	float left = (2.0 - width) / 2.0f;
	float top = height / 2.0f;
	float modeTop = modeHeight / 2.0f;
	float eachHeight = modeHeight / 4.0f;

	pos[CONTINUE] = Vec2(0.0f, modeTop - eachHeight / 2.0f);
	pos[MAIN_MENU] = Vec2(0.0f, modeTop - eachHeight * 3.0f / 2.0f);
	pos[STAGE_SELECT] = Vec2(0.0f, modeTop - eachHeight * 5.0f / 2.0f);
	pos[RULE] = Vec2(0.0f, modeTop - eachHeight * 7.0f / 2.0f);
	text[CONTINUE] = U"Continue";
	text[MAIN_MENU] = U"MainMenu";
	text[STAGE_SELECT] = U"StageSelect";
	text[RULE] = U"Rule";

	float rectHeight = eachHeight * 0.7f;
	float rectWidth = width * 0.7f;

	// 描画
	DrawRect(Vec2(0.0f, 0.0f), width, height, ColorF(192.0f / 255.0f));
	for (auto [mode,p] : pos) {
		DrawRect(p, rectWidth, rectHeight,ColorF(1.0f));
		pauseFont(text[mode]).drawAt(ConvertToView(p), ColorF(0.0f));
	}

	DrawRectFrame(pos[mPauseMode], rectWidth, rectHeight, 0.01f, 0.01f, ColorF(0.0f));
	
}

void Game::UnloadData() {
	while (!mActors.empty()) {
		delete mActors.back();
	}

	TextureAsset::Release(U"brock_stone");
	TextureAsset::Release(U"brock_grass");
	TextureAsset::Release(U"brock_wood");
	TextureAsset::Release(U"candle");
	TextureAsset::Release(U"key");
	TextureAsset::Release(U"treasure");
	TextureAsset::Release(U"battery");
}


void Game::Shutdown() {
	UnloadData();
}


void Game::AddActor(Actor* actor) {
	if (mUpdatingActors) {
		mPendingActors.emplace_back(actor);
	}
	else {
		mActors.emplace_back(actor);
	}

}


void Game::RemoveActor(Actor* actor) {
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end()) {
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end()) {
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::AddDrawing(DrawingComponent* drawing) {
	int myDrawOrder = drawing->GetDrawOrder();
	if (drawing->GetDrawingState()==DrawingComponent::DrawingState::BACK) {
		auto iter = mDrawings_Back.begin();
		for (;
			iter != mDrawings_Back.end();
			++iter)
		{
			if (myDrawOrder < (*iter)->GetDrawOrder()) {
				break;
			}
		}
		mDrawings_Back.insert(iter, drawing);
	}
	else if(drawing->GetDrawingState()==DrawingComponent::DrawingState::FRONT){
		auto iter = mDrawings_Front.begin();
		for (;
			iter != mDrawings_Front.end();
			++iter)
		{
			if (myDrawOrder < (*iter)->GetDrawOrder()) {
				break;
			}
		}
		mDrawings_Front.insert(iter, drawing);
	}
	else {
		auto iter = mDrawings_Unaffected.begin();
		for (;
			iter != mDrawings_Unaffected.end();
			++iter)
		{
			if (myDrawOrder < (*iter)->GetDrawOrder()) {
				break;
			}
		}
		mDrawings_Unaffected.insert(iter, drawing);
	}
}

void Game::RemoveDrawing(DrawingComponent* drawing) {
	if (drawing->GetDrawingState()==DrawingComponent::DrawingState::BACK) {
		auto iter = std::find(mDrawings_Back.begin(), mDrawings_Back.end(), drawing);
		mDrawings_Back.erase(iter);
	}
	else if(drawing->GetDrawingState()==DrawingComponent::DrawingState::FRONT){
		auto iter = std::find(mDrawings_Front.begin(), mDrawings_Front.end(), drawing);
		mDrawings_Front.erase(iter);
	}
	else {
		auto iter = std::find(mDrawings_Unaffected.begin(), mDrawings_Unaffected.end(), drawing);
		mDrawings_Unaffected.erase(iter);
	}
}

void Game::AddCircle(CircleComponent* circle) {
	mCircles.emplace_back(circle);
}

void Game::RemoveCircle(CircleComponent* circle) {
	auto iter = std::find(mCircles.begin(), mCircles.end(), circle);

	if (iter != mCircles.end()) {
		mCircles.erase(iter);
	}
}

void Game::AddSquare(SquareComponent* square) {
	mSquares.emplace_back(square);
}

void Game::RemoveSquare(SquareComponent* square) {
	auto iter = std::find(mSquares.begin(), mSquares.end(), square);
	if (iter != mSquares.end()) {
		mSquares.erase(iter);
	}
}

void Game::AddTriangle(TriangleComponent* tri) {
	mTriangles.emplace_back(tri);
}

void Game::RemoveTriangle(TriangleComponent* tri) {
	auto iter = std::find(mTriangles.begin(), mTriangles.end(), tri);
	if (iter != mTriangles.end()) {
		mTriangles.erase(iter);
	}
}

void Game::AddPlayer(Player* player) {
	mPlayers.emplace_back(player);
}
void Game::RemovePlayer(Player* player) {
	auto iter = std::find(mPlayers.begin(), mPlayers.end(), player);
	if (iter != mPlayers.end()) {
		mPlayers.erase(iter);
	}
}

void Game::UpdateTimer(float deltaTime) {
	if (mIsTimeUp)return;

	mGameTime -= deltaTime;
	if (mGameTime <= 0.0f) {
		mGameTime = 0.0f;
		mIsTimeUp = true;
	}

	int time = static_cast<int>(mGameTime);
	mGameMin = time / 60;
	mGameSec = time % 60;
}

void Game::CheckIsGameEnd() {
	// Ghostの負け
	if (!mGhost->GetIsAlive()) {
		mIsGameEnd = true;
		mJudgement = Parent::GameJudgement::ESCAPEES_WIN;
	}
	// Escapeeの負け
	else if (!(
		(mEscapee1&&mEscapee1->GetIsAlive())||
		(mEscapee2&&mEscapee2->GetIsAlive())||
		(mEscapee3&&mEscapee3->GetIsAlive())
		)) {
		mIsGameEnd = true;
		mJudgement = Parent::GameJudgement::GHOST_WIN;

	}
	// 引き分け
	else if (mIsTimeUp) {
		mIsGameEnd = true;
		mJudgement = Parent::GameJudgement::DRAW;
	}
	
}

void Game::moveTo(Parent* parent, Parent::SeqID id) {
	if (id == Parent::SEQ_MAINMENU)parent->moveTo(Parent::SEQ_MAINMENU,Parent::SEQ_GAME);
	if (id == Parent::SEQ_STAGESELECT) {
		parent->setStageSelectGame(true);
		parent->moveTo(Parent::SEQ_STAGESELECT, Parent::SEQ_GAME);
	}
	if (id == Parent::SEQ_GAME)parent->moveTo(Parent::SEQ_GAME,Parent::SEQ_GAME);
	if (id == Parent::SEQ_CREATESTAGE)parent->moveTo(Parent::SEQ_CREATESTAGE,Parent::SEQ_GAME);
	if (id == Parent::SEQ_GAMERESULT)parent->moveTo(Parent::SEQ_GAMERESULT, Parent::SEQ_GAME);
	if (id == Parent::SEQ_CHANGEWINDOWSIZE)parent->moveTo(Parent::SEQ_CHANGEWINDOWSIZE, Parent::SEQ_GAME);
	if (id == Parent::SEQ_SUBMENU)parent->moveTo(Parent::SEQ_SUBMENU, Parent::SEQ_GAME);
}
