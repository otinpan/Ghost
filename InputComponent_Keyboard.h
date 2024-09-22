#pragma once
#include "MoveComponent.h"
#include"Siv3D.hpp"

class InputComponent_Keyboard :public MoveComponent {
public:
	InputComponent_Keyboard(class Actor* owner);

	void ProcessInput(const std::vector<Input> keyState)override;

	float GetMaxXSpeed() const { return mMaxXSpeed; }
	float GetMaxYSpeed() const { return mMaxYSpeed; }
	float GetMaxAngularSpeed() const { return mMaxAngularSpeed; }

	InputGroup GetUpKey() const { return mUpKey; }
	InputGroup GetDownKey() const { return mDownKey; }
	InputGroup GetRightKey() const { return mRightKey; }
	InputGroup GetLeftKey() const { return mLeftKey; }
	InputGroup GetClockwiseKey() const { return mClockwiseKey; }
	InputGroup GetCounterClockwiseKey() const { return mCounterClockwiseKey; }

	void SetMaxXSpeed(float speed) { mMaxXSpeed = speed; }
	void SetMaxYSpeed(float speed) { mMaxYSpeed = speed; }
	void SetMaxAngularSpeed(float speed) { mMaxAngularSpeed = speed; }
	void SetUpKey(InputGroup key) { mUpKey = key; }
	void SetDownKey(InputGroup key) { mDownKey = key; }
	void SetRightKey(InputGroup key) { mRightKey = key; }
	void SetLeftKey(InputGroup key) { mLeftKey = key; }
	void SetClockwiseKey(InputGroup key) { mClockwiseKey = key; }
	void SetCounterClockwiseKey(InputGroup key) { mCounterClockwiseKey = key;}

private:
	float mMaxXSpeed;
	float mMaxYSpeed;
	float mMaxAngularSpeed;

	InputGroup mUpKey;
	InputGroup mDownKey;
	InputGroup mRightKey;
	InputGroup mLeftKey;
	InputGroup mClockwiseKey;
	InputGroup mCounterClockwiseKey;
};
