// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>

Actor::Actor()
	:mState(EActive)
	, mPosition(Vec2{ 0,0 })
	, mScale(1.0f)
	, mRotation(0.0f)
	,mGame(0)
	,mCreateStage(0)
	,mIsDead(false)
{
}

Actor::~Actor()
{
	if(mGame)mGame->RemoveActor(this);
	if (mCreateStage)mCreateStage->RemoveActor(this);
	// Need to delete components
	// Because ~Component calls RemoveComponent, need a different style loop

	DeleteComponents();
}

void Actor::DeleteComponents() {
	while (!mComponents.empty()) {
		delete mComponents.back();
	}
}

void Actor::Initialize_Game(Game* game) {
	mGame = game;
	mGame->AddActor(this);
}

void Actor::Initialize_CreateStage(CreateStage* createstage) {
	mCreateStage = createstage;
	mCreateStage->AddActor(this);
}

void Actor::InitializeActor_Game(Game* game) {

}

void Actor::InitializeActor_CreateStage(CreateStage* createstage) {

}


void Actor::Update(float deltaTime)
{
	if (mIsDead)mState = EDead;
	if (mState == EActive)
	{
		UpdateComponents(deltaTime);
		if(mGame)UpdateActor_Game(deltaTime);
		if (mCreateStage)UpdateActor_CreateStage(deltaTime);
	}
}

void Actor::UpdateComponents(float deltaTime)
{
	for (auto comp : mComponents)
	{
		comp->Update(deltaTime);
	}
}

void Actor::UpdateActor_Game(float deltaTime)
{
}

void Actor::UpdateActor_CreateStage(float deltaTime)
{

}

void Actor::ProcessInput(const std::vector<Input> keyState)
{
	if (mState == EActive)
	{
		// First process input for components
		for (auto comp : mComponents)
		{
			comp->ProcessInput(keyState);
		}

		ActorInput(keyState);
	}
}

void Actor::ActorInput(const std::vector<Input> keyState)
{
}

void Actor::AddComponent(Component* component)
{
	// Find the insertion point in the sorted vector
	// (The first element with a order higher than me)
	int myOrder = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	for (;
		iter != mComponents.end();
		++iter)
	{
		if (myOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}

	// Inserts element before position of iterator
	mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}
