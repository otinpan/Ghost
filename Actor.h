// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <vector>
#include "Math.h"
#include <cstdint>
#include<Siv3D.hpp>
#include"Game.h"
#include"CreateStage.h"

class Actor
{
public:
	enum State
	{
		EActive,
		EPaused,
		EDead
	};

	Actor();
	virtual ~Actor();

	void Initialize_Game(class Game* game);
	void Initialize_CreateStage(class CreateStage* createstage);

	virtual void InitializeActor_Game(class Game* game);
	virtual void InitializeActor_CreateStage(class CreateStage* createstage);

	// Update function called from Game (not overridable)
	void Update(float deltaTime);
	// Updates all the components attached to the actor (not overridable)
	void UpdateComponents(float deltaTime);
	// Any actor-specific update code (overridable)
	virtual void UpdateActor_Game(float deltaTime);
	virtual void UpdateActor_CreateStage(float deltaTime);

	// ProcessInput function called from Game (not overridable)
	void ProcessInput(const std::vector<Input> keyState);
	// Any actor-specific input code (overridable)
	virtual void ActorInput(const std::vector<Input> keyState);

	// Getters/setters
	const Vec2& GetPosition() const { return mPosition; }
	void SetPosition(const Vec2& pos) { mPosition = pos; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; }
	bool GetIsDead() { return mIsDead; }
	void SetIsDead(bool isDead) { mIsDead = isDead; }

	Vec2 GetForward() const { return Vec2(Math::Cos(mRotation), -Math::Sin(mRotation)); }

	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }

	class Game* GetGame() { return mGame; }
	class CreateStage* GetCreateStage(){ return mCreateStage; }


	// Add/remove components
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);
private:
	// Actor's state
	State mState;

	// Transform
	Vec2 mPosition;
	float mScale;
	float mRotation;

	bool mIsDead;

	std::vector<class Component*> mComponents;
	class Game* mGame;
	class CreateStage* mCreateStage;
};
