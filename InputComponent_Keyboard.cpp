#include"InputComponent_Keyboard.h"
#include"Actor.h"

InputComponent_Keyboard::InputComponent_Keyboard(class Actor* owner)
	:MoveComponent(owner)
	,mMaxAngularSpeed(0.0f)
	,mMaxXSpeed(0.0f)
	,mMaxYSpeed(0.0f)
	, mUpKey()
	, mDownKey()
	, mRightKey()
	, mLeftKey()
	, mClockwiseKey()
	, mCounterClockwiseKey()
{

}


void InputComponent_Keyboard::ProcessInput(std::vector<Input> keyState) {
	float xSpeed = 0.0f;

	if (mRightKey.pressed())xSpeed += mMaxXSpeed;
	if (mLeftKey. pressed())xSpeed -= mMaxXSpeed;
	SetXSpeed(xSpeed);

	float ySpeed = 0.0f;
	if (mUpKey.pressed())ySpeed += mMaxYSpeed;
	if (mDownKey.pressed())ySpeed -= mMaxYSpeed;
	SetYSpeed(ySpeed);

	float angularSpeed = 0.0f;
	if (mClockwiseKey.pressed())angularSpeed += mMaxAngularSpeed;
	if (mCounterClockwiseKey.pressed())angularSpeed -= mMaxAngularSpeed;
	SetAngularSpeed(angularSpeed);

	
}
