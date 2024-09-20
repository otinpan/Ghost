#include"StageObject.h"

StageObject::StageObject(CreateStage* createstage)
	:mState(EActive)
	, mPosition(Vec2{ 0,0 })
	, mRotation(0.0f)
	, mCreateStage(createstage)
{

}

StageObject::~StageObject() {

}


void StageObject::Update(float deltaTime) {
	if (mState == EActive) {
		UpdateStageObject(deltaTime);
	}
}

void StageObject::UpdateStageComponents(float deltaTime) {
	for (auto comp : mStageComponents) {
		comp->Update(deltaTime);
	}
}

void StageObject::UpdateStageObject(float deltaTime) {

}

void StageObject::ProcessInput(const std::vector<Input> keyState)
{
	if (mState == EActive)
	{
		// First process input for components
		for (auto comp : mStageComponents)
		{
			comp->ProcessInput(keyState);
		}

		StageObjectInput(keyState);
	}
}

void StageObject::StageObjectInput(const std::vector<Input> keyState)
{
}

void StageObject::AddStageComponent(StageComponent* component) {
	int myOrder = component->GetUpdateOrder();
	auto iter = mStageComponents.begin();
	for (;
		iter != mStageComponents.end();
		iter++)
	{
		if (myOrder < (*iter)->GetUpdateOrder()) {
			break;
		}
	}

	mStageComponents.insert(iter, component);
}

void StageObject::RemoveStageComponent(StageComponent* component) {
	auto iter = std::find(mStageComponents.begin(), mStageComponents.end(), component);
	if (iter != mStageComponents.end()) {
		mStageComponents.erase(iter);
	}
}
