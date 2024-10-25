#include"CreateStage.h"
#include"Hand.h"
#include"StageObject.h"
#include"Stage.h"
#include"Brock.h"
#include"StageMenu.h"
#include"Door.h"
#include"Patrol.h"
#include"Candle.h"

CreateStage::CreateStage()
	:mUpdatingActors(false)
	, mIsRunning(true)
	, mSeqID(Parent::SEQ_NONE)
{
	Initialize();
}

CreateStage::~CreateStage() {

}

bool CreateStage::Initialize() {
	LoadData();
	return true;
}

void CreateStage::update(Parent* parent) {
	if (mIsRunning) {
		ClearPrint();
		if (mSeqID != Parent::SEQ_NONE) {
			moveTo(parent, mSeqID);
		}
		ProcessInput();
		UpdateGame();
		draw();
		Print << mHand->GetIsChoose();
		//Print << mActors.size();
		//Print << mHand->GetIsExpand();
	}
}

void CreateStage::ProcessInput() {
	const std::vector<Input> keyState = Keyboard::GetAllInputs();

	mUpdatingActors = true;
	for (auto actor : mActors) {
		actor->ProcessInput(keyState);
	}
	mUpdatingActors = false;
}


void CreateStage::UpdateGame(){
	float deltaTime = Scene::DeltaTime();


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

	mStage->Update_CreateStage(deltaTime);
	mStageMenu->Update_CreateStage(deltaTime);
}



void CreateStage::draw() {
	mStage->Draw_CreateStage();
	mStageMenu->Draw_CreateStage();
	for (auto square : mSquares) {
		square->Draw();
	}
	for (auto circle : mCircles) {
		circle->Draw();
	}
	for (auto sprite : mSprites) {

	}
}

void CreateStage::LoadData() {
	mHand = new Hand();
	mHand->InitializeActor_CreateStage(this);
	mStage = new Stage(1.6f, 1.5f);
	mStage->Initialize_CreateStage(this);
	mStageMenu = new StageMenu();
	mStageMenu->Initialize_CreateStage(this);
	mBrock = new Brock(Vec2({ 0.0f,-0.7f }), mStage->GetRectWidth()
		, mStage->GetRectHeight());
	mBrock->InitializeStageObject_CreateStage(this);
	mDoor = new Door(Vec2{ 0.4f,-0.7f }, mStage->GetRectWidth()
		,mStage->GetRectHeight());
	mDoor->InitializeStageObject_CreateStage(this);
	mPatrol = new Patrol(Vec2{ 0.2f,-0.7f }, mStage->GetRectWidth()
		, mStage->GetRectHeight());
	mPatrol->InitializeStageObject_CreateStage(this);
	mCandle = new Candle(Vec2{ -0.2f,-0.7f }, mStage->GetRectWidth() / 3
	, mStage->GetRectHeight() / 3, mStage->GetHeight() / 5);
	mCandle->InitializeStageObject_CreateStage(this);
}

void CreateStage::UnloadData() {
	while (!mActors.empty()) {
		delete mActors.back();
	}
	delete mStage;
}


void CreateStage::Shutdown() {
	UnloadData();
}


void CreateStage::AddActor(Actor* actor) {
	if (mUpdatingActors) {
		mPendingActors.emplace_back(actor);
	}
	else {
		mActors.emplace_back(actor);
	}

}


void CreateStage::RemoveActor(Actor* actor) {
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

void CreateStage::AddSprite(SpriteComponent* sprite)
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

void CreateStage::RemoveSprite(SpriteComponent* sprite)
{
	// (We can't swap because it ruins ordering)
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

void CreateStage::AddCircle(CircleComponent* circle) {
	mCircles.emplace_back(circle);
}

void CreateStage::RemoveCircle(CircleComponent* circle) {
	auto iter = std::find(mCircles.begin(), mCircles.end(), circle);

	if (iter != mCircles.end()) {
		mCircles.erase(iter);
	}
}

void CreateStage::AddSquare(SquareComponent* square) {
	mSquares.emplace_back(square);
}

void CreateStage::RemoveSquare(SquareComponent* square) {
	auto iter = std::find(mSquares.begin(), mSquares.end(), square);
	if (iter != mSquares.end()) {
		mSquares.erase(iter);
	}
}

void CreateStage::AddStageObject(StageObject* stageobject) {
	mStageObjects.emplace_back(stageobject);
}

void CreateStage::RemoveStageObject(StageObject* stageobject) {
	auto iter = std::find(mStageObjects.begin(), mStageObjects.end(), stageobject);
	if (iter != mStageObjects.end()) {
		mStageObjects.erase(iter);
	}
}



void CreateStage::moveTo(Parent* parent, Parent::SeqID id) {
	if (id == Parent::SEQ_GAME)parent->moveTo(Parent::SEQ_GAME);
	if (id == Parent::SEQ_CREATESTAGE)parent->moveTo(Parent::SEQ_CREATESTAGE);
}



