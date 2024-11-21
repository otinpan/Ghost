#include<Siv3D.hpp>
#include"Game.h"
#include<algorithm>
#include"Actor.h"
#include"CircleComponent.h"
#include"SpriteComponent.h"
#include"Stage.h"
#include"Ghost_Game.h"
#include"Escapee_Game.h"


Game::Game()
	:mUpdatingActors(false)
	, mIsRunning(true)
	, mIsHitstop(false)
	, HitstopTime(0.0f)
	, mSeqID(Parent::SEQ_NONE)
{
	Initialize();
}

Game::~Game() {
	Shutdown();
}

bool Game::Initialize() {
	LoadData();
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
		
	}

	mUpdatingActors = false;
}

void Game::UpdateGame() {
	float h = (float)2 / 15, w = (float)2/24;
	for (float i = -1.0; i <= 1.0; i += h) {
		for (float j = -1.0; j <= 1.0; j += w) {
			Vec2 pos = { (float)j + w / 2,(float)i + h / 2 };
			DrawRect(pos, w, h, ColorF(0, 0, 0));
			DrawRectFrame(pos, w, h, 0.01,0, ColorF(1, 1, 1));
		}
	}
	float deltaTime = Scene::DeltaTime();

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
	for (auto circle : mCircles) {
		circle->Draw();
	}
	for (auto square : mSquares) {
		square->Draw();
	}
	for (auto sprite : mSprites) {
		
	}
}

void Game::LoadData() {
	mStage = new Stage(1.92f,1.92f);
	//mStage->Initialize_Game(this,U"Stage1.bin");
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

void Game::AddSprite(SpriteComponent* sprite)
{
	// Find the insertion point in the sorted vector
	// (The first element with a higher draw order than me)
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (;
		iter != mSprites.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	// Inserts element before position of iterator
	mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	// (We can't swap because it ruins ordering)
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
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

void Game::moveTo(Parent* parent, Parent::SeqID id) {
	if (id == Parent::SEQ_GAME)parent->moveTo(Parent::SEQ_GAME);
	if (id == Parent::SEQ_CREATESTAGE)parent->moveTo(Parent::SEQ_CREATESTAGE);
}
