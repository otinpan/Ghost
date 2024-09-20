#include"CreateStage.h"

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
		if (mSeqID != Parent::SEQ_NONE) {
			moveTo(parent, mSeqID);
		}
		ProcessInput();
		UpdateGame();
		draw();
	}
}

void CreateStage::ProcessInput() {
	const std::vector<Input> keyState = Keyboard::GetAllInputs();

	mUpdatingActors = true;
	for (auto actor : mStageObjects) {
		actor->ProcessInput(keyState);
	}
	mUpdatingActors = false;
}


void CreateStage::UpdateGame(){
	float deltaTime = Scene::DeltaTime();


	mUpdatingActors = true;
	for (auto actor : mStageObjects) {
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	for (auto pending : mPendingStageObjects) {
		mStageObjects.emplace_back(pending);
	}
	mPendingStageObjects.clear();

	std::vector<Actor*> deadActors;
	for (auto actor : mStageObjects) {
		if (actor->GetState() == Actor::EDead) {
			deadActors.emplace_back(actor);
		}
	}

	for (auto actor : deadActors) {
		delete actor;
	}
}



void CreateStage::draw() {
	for (auto circle : mCircles) {
		circle->Draw();
	}
	for (auto sprite : mSprites) {

	}
}

void CreateStage::LoadData() {

}

void CreateStage::UnloadData() {
	while (!mStageObjects.empty()) {
		delete mStageObjects.back();
	}
}


void CreateStage::Shutdown() {
	UnloadData();
}


void CreateStage::AddStageObject(Actor* actor) {
	if (mUpdatingActors) {
		mPendingStageObjects.emplace_back(actor);
	}
	else {
		mStageObjects.emplace_back(actor);
	}

}


void CreateStage::RemoveStageObject(Actor* actor) {
	auto iter = std::find(mPendingStageObjects.begin(), mPendingStageObjects.end(), actor);
	if (iter != mPendingStageObjects.end()) {
		std::iter_swap(iter, mPendingStageObjects.end() - 1);
		mPendingStageObjects.pop_back();
	}

	iter = std::find(mStageObjects.begin(), mStageObjects.end(), actor);
	if (iter != mStageObjects.end()) {
		std::iter_swap(iter, mStageObjects.end() - 1);
		mStageObjects.pop_back();
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

void CreateStage::moveTo(Parent* parent, Parent::SeqID id) {
	if (id == Parent::SEQ_GAME)parent->moveTo(Parent::SEQ_GAME);
}



