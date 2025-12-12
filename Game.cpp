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


Game::Game(String selectedStageName)
	:mUpdatingActors(false)
	, mIsRunning(true)
	, mIsHitstop(false)
	, HitstopTime(0.0f)
	, mSeqID(Parent::SEQ_NONE)
	, mSelectedStageName(selectedStageName)
	, mGameTime(300.0f)
	, mIsPaused(false)
	, mIsTimeUp(false)
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
	return true;
}

void Game::update(Parent* parent) {
	if (mIsRunning) {
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
	}

	// timer更新
	UpdateTimer(deltaTime);


	if (mIsHitstop) {
		UpdateHitstop(deltaTime);
		return;
	}

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
	mStage = new Stage(1.85f,1.85f);


	const FilePath path = U"Stage/" + mSelectedStageName + U"/Data.bin";
	mStage->Initialize_Game(this,path);
	mGhost = new Ghost_Game(Vec2({(float)mStage->GetLeft() +
		mStage->GetGhostIteration().second * mStage->GetRectWidth() + mStage->GetRectWidth() / 2,
		(float)mStage->GetUp() -
		(mStage->GetGhostIteration().first + 1) * mStage->GetRectHeight() + mStage->GetRectHeight() / 2 }),
		mStage->GetGhostSpeed()
	);
	mGhost->InitializePlayer_Game(this);
	mEscapee1 = new Escapee_Game(Vec2({(float)mStage->GetLeft() +
		mStage->GetEscapee1Iteration().second * mStage->GetRectWidth() + mStage->GetRectWidth() / 2,
		(float)mStage->GetUp() -
		(mStage->GetEscapee1Iteration().first + 1) * mStage->GetRectHeight() + mStage->GetRectHeight() / 2 }),
		mStage->GetGhostSpeed(),1);
	mEscapee1->InitializePlayer_Game(this);
	mEscapee2 = new Escapee_Game(Vec2({ (float)mStage->GetLeft() +
		mStage->GetEscapee2Iteration().second * mStage->GetRectWidth() + mStage->GetRectWidth() / 2,
		(float)mStage->GetUp() -
		(mStage->GetEscapee2Iteration().first + 1) * mStage->GetRectHeight() + mStage->GetRectHeight() / 2 }),
		mStage->GetGhostSpeed(),2);
	mEscapee2->InitializePlayer_Game(this);
	mEscapee3 = new Escapee_Game(Vec2({ (float)mStage->GetLeft() +
		mStage->GetEscapee3Iteration().second * mStage->GetRectWidth() + mStage->GetRectWidth() / 2,
		(float)mStage->GetUp() -
		(mStage->GetEscapee3Iteration().first + 1) * mStage->GetRectHeight() + mStage->GetRectHeight() / 2 }),
		mStage->GetGhostSpeed(),3);
	mEscapee3->InitializePlayer_Game(this);
}

void Game::UnloadData() {
	while (!mActors.empty()) {
		delete mActors.back();
	}
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
	if (drawing->GetDrawState()==DrawingComponent::DrawState::BACK) {
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
	else if(drawing->GetDrawState()==DrawingComponent::DrawState::FRONT){
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
	if (drawing->GetDrawState()==DrawingComponent::DrawState::BACK) {
		auto iter = std::find(mDrawings_Back.begin(), mDrawings_Back.end(), drawing);
		mDrawings_Back.erase(iter);
	}
	else if(drawing->GetDrawState()==DrawingComponent::DrawState::FRONT){
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

void Game::moveTo(Parent* parent, Parent::SeqID id) {
	if (id == Parent::SEQ_MAINMENU)parent->moveTo(Parent::SEQ_MAINMENU,Parent::SEQ_GAME);
	if (id == Parent::SEQ_STAGESELECT)parent->moveTo(Parent::SEQ_STAGESELECT, Parent::SEQ_GAME);
	if (id == Parent::SEQ_GAME)parent->moveTo(Parent::SEQ_GAME,Parent::SEQ_GAME);
	if (id == Parent::SEQ_CREATESTAGE)parent->moveTo(Parent::SEQ_CREATESTAGE,Parent::SEQ_GAME);
	if (id == Parent::SEQ_GAMERESULT)parent->moveTo(Parent::SEQ_GAMERESULT, Parent::SEQ_GAME);
	if (id == Parent::SEQ_CHANGEWINDOWSIZE)parent->moveTo(Parent::SEQ_CHANGEWINDOWSIZE, Parent::SEQ_GAME);
	if (id == Parent::SEQ_SUBMENU)parent->moveTo(Parent::SEQ_SUBMENU, Parent::SEQ_GAME);
}
