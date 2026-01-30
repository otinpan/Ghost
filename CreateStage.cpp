#include"CreateStage.h"
#include"Hand.h"
#include"StageObject.h"
#include"Stage.h"
#include"Brock.h"
#include"StageMenu.h"
#include"Door.h"
#include"Patrol.h"
#include"Candle.h"
#include"TreasureChest.h"
#include"DrawingComponent.h"
#include"Common.h"

CreateStage::CreateStage(String stageName)
	:mUpdatingActors(false)
	, mIsRunning(true)
	, mSeqID(Parent::SEQ_NONE)
	, mIsMoveTo(false)
	, mCanSave(false)
	, mSelectedStageName(stageName)
	, mShouldCloseGPTMenu(false)
	, mShouldCloseTextMenu(false)
{
	Initialize();
}

CreateStage::~CreateStage() {

}

bool CreateStage::Initialize() {
	Scene::SetBackground(ColorF((float)192/255,(float)192/255, (float)192/255));
	LoadData();
	return true;
}

void CreateStage::update(Parent* parent) {
	if (mIsRunning) {
		//ClearPrint();
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
	for (auto actor : mActors) {
		actor->ProcessInput(keyState);
	}
	mUpdatingActors = false;
}


void CreateStage::UpdateGame(){
	float deltaTime = Scene::DeltaTime();
	if (mCanSave) {
		mStage->SaveStage();
		SetSeqID(Parent::SEQ_STAGESELECT);
	}

	// TextMenu
	if (mTextMenu) {
		mTextMenu->Update(deltaTime);
		if (mShouldCloseTextMenu) {
			CloseTextMenu();
			if (mIsMoveTo) {
				mCanSave = true;
			}
		}
		return;
	}
	// GPTMenu
	if (mGPTMenu) {
		mGPTMenu->Update(deltaTime);
		if (mShouldCloseGPTMenu) {
			CloseGPTMenu();
		}
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

	mStage->Update_CreateStage(deltaTime);
	mStageMenu->Update_CreateStage(deltaTime);

	
}



void CreateStage::draw() {
	mStage->Draw_CreateStage();
	mStageMenu->Draw_CreateStage();
	/*for (auto square : mSquares) {
		square->Draw();
	}
	for (auto circle : mCircles) {
		circle->Draw();
	}*/

	for (auto& drawing : mDrawings_Back) {
		drawing->Draw();
	}
	for (auto& drawing : mDrawings_Front) {
		drawing->Draw();
	}
	for (auto& drawing : mDrawings_Unaffected) {
		drawing->Draw();
	}
	

	mStage->DrawForward_CreateStage();
	if (mTextMenu)mTextMenu->Draw(40*GetScreenWidth()/960);
	if (mGPTMenu)mGPTMenu->Draw();
}

void CreateStage::LoadData() {
	// Assetロード
	TextureAsset::Load(U"brock_stone");
	TextureAsset::Load(U"borck_grass");
	TextureAsset::Load(U"borck_wood");
	TextureAsset::Load(U"candle");
	TextureAsset::Load(U"key");
	TextureAsset::Load(U"treasure");
	TextureAsset::Load(U"battery");
	TextureAsset::Load(U"cursor_arrow");
	TextureAsset::Load(U"cursor_hand");
	TextureAsset::Load(U"ghost");
	TextureAsset::Load(U"escapee1");
	TextureAsset::Load(U"escapee2");
	TextureAsset::Load(U"escapee3");
	TextureAsset::Load(U"patrol");


	mStage = new Stage(1.6f, 1.5f);
	if (mSelectedStageName == U"") {
		mStage->Initialize_CreateStage(this);
		mStageName = U"StageName";
	}
	else {
		const FilePath path = U"Stage/" + mSelectedStageName + U"/Data.bin";
		mStage->Initialize_CreateStage(this, path);
		mStageName = mSelectedStageName;
	}
	mHand = new Hand();
	mHand->InitializeActor_CreateStage(this);

	mStageMenu = new StageMenu();
	mStageMenu->Initialize_CreateStage(this);
	mShouldCloseTextMenu = false;
}

void CreateStage::UnloadData() {
	while (!mActors.empty()) {
		delete mActors.back();
	}
	delete mStage;

	TextureAsset::Release(U"brock_stone");
	TextureAsset::Release(U"brock_grass");
	TextureAsset::Release(U"brock_wood");
	TextureAsset::Release(U"candle");
	TextureAsset::Release(U"key");
	TextureAsset::Release(U"treasure");
	TextureAsset::Release(U"battery");
	TextureAsset::Release(U"cursor_arrow");
	TextureAsset::Release(U"cursor_hand");
	TextureAsset::Release(U"ghost");
	TextureAsset::Release(U"escapee1");
	TextureAsset::Release(U"escapee3");
	TextureAsset::Release(U"escapee2");
	TextureAsset::Release(U"patrol");
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

void CreateStage::AddDrawing(DrawingComponent* drawing)
{
	int myDrawOrder = drawing->GetDrawOrder();
	if (drawing->GetDrawingState() == DrawingComponent::DrawingState::BACK) {
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
	else if (drawing->GetDrawingState() == DrawingComponent::DrawingState::FRONT) {
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

void CreateStage::RemoveDrawing(DrawingComponent* drawing)
{
	if (drawing->GetDrawingState() == DrawingComponent::DrawingState::BACK) {
		auto iter = std::find(mDrawings_Back.begin(), mDrawings_Back.end(), drawing);
		mDrawings_Back.erase(iter);
	}
	else if (drawing->GetDrawingState() == DrawingComponent::DrawingState::FRONT) {
		auto iter = std::find(mDrawings_Front.begin(), mDrawings_Front.end(), drawing);
		mDrawings_Front.erase(iter);
	}
	else {
		auto iter = std::find(mDrawings_Unaffected.begin(), mDrawings_Unaffected.end(), drawing);
		mDrawings_Unaffected.erase(iter);
	}
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

void CreateStage::AddTriangle(TriangleComponent* tri) {
	mTriangles.emplace_back(tri);
}

void CreateStage::RemoveTriangle(TriangleComponent* tri) {
	auto iter = std::find(mTriangles.begin(), mTriangles.end(), tri);
	if (iter != mTriangles.end()) {
		mTriangles.erase(iter);
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

void CreateStage::OpenTextMenu() {
	mTextMenu = std::make_unique<TextMenu>(mStageName);
	mTextMenu->Initialize_CreateStage(this);
}

void CreateStage::CloseTextMenu() {
	if (mStage->EndCreateStage(mStageName)) {
		mIsMoveTo = true;
	}
	else {
		mShouldCloseTextMenu = false;
	}
	if(mTextMenu)mTextMenu.reset();
}

void CreateStage::OpenGPTMenu() {
	mGPTMenu = std::make_unique<GPTMenu>();
	mGPTMenu->Initialize_CreateStage(this);
	mShouldCloseGPTMenu = false;
}

void CreateStage::CloseGPTMenu() {
	if (mGPTMenu)mGPTMenu.reset();
}

void CreateStage::moveTo(Parent* parent, Parent::SeqID id) {
	if (id == Parent::SEQ_MAINMENU)parent->moveTo(Parent::SEQ_MAINMENU,Parent::SEQ_CREATESTAGE);
	if (id == Parent::SEQ_STAGESELECT)parent->moveTo(Parent::SEQ_STAGESELECT, Parent::SEQ_CREATESTAGE);
	if (id == Parent::SEQ_GAME)parent->moveTo(Parent::SEQ_GAME,Parent::SEQ_CREATESTAGE);
	if (id == Parent::SEQ_CREATESTAGE)parent->moveTo(Parent::SEQ_CREATESTAGE, Parent::SEQ_CREATESTAGE);
	if (id == Parent::SEQ_GAMERESULT)parent->moveTo(Parent::SEQ_GAMERESULT,Parent::SEQ_CREATESTAGE);
	if (id == Parent::SEQ_CHANGEWINDOWSIZE)parent->moveTo(Parent::SEQ_CHANGEWINDOWSIZE, Parent::SEQ_CREATESTAGE);
	if (id == Parent::SEQ_SUBMENU)parent->moveTo(Parent::SEQ_SUBMENU, Parent::SEQ_CREATESTAGE);
}


void CreateStage::SetStageName(const String& name) {
	mStageName = name;
}

