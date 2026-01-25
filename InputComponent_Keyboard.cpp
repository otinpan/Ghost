#include"InputComponent_Keyboard.h"
#include"Actor.h"
#define _USE_MATH_DEFINES
#include<math.h>

InputComponent_Keyboard::InputComponent_Keyboard(class Actor* owner)
	:Controller(owner,Controller::ControllerType::KEYBOARD)
	, inputUp()
	, inputDown()
	, inputRight()
	, inputLeft()
	, inputClockwise()
	, inputCounterClockwise()
{

}

InputComponent_Keyboard::~InputComponent_Keyboard() {

}

void InputComponent_Keyboard::Initialize() {
	inputUp = KeyW;
	inputDown = KeyS;
	inputLeft = KeyA;
	inputRight = KeyD;
	SetInputA(KeySpace);
	SetInputB(KeyBackspace);
	SetInputX(Key8);
	SetInputY(Key9);
	SetInputL(KeyLeft);
	SetInputR(KeyRight);
	SetInputPlus(KeyP);
	SetInputMinus(KeyO);
	
}

void InputComponent_Keyboard::ProcessInput() {
	float xSpeed = 0.0f;
	float rad = 0.0f;
	Actor::Direction dir=Actor::Direction::DIR_UP;

	if (inputRight.pressed())xSpeed += GetMaxXSpeed();
	if (inputLeft. pressed())xSpeed -= GetMaxXSpeed();

	float ySpeed = 0.0f;
	if (inputUp.pressed())ySpeed += GetMaxYSpeed();
	if (inputDown.pressed())ySpeed -= GetMaxYSpeed();

	if (ySpeed > 0 && xSpeed == 0) { // 上方向
		rad = M_PI / 2.0f;
		dir = Actor::Direction::DIR_UP;
	}
	else if (ySpeed > 0 && xSpeed > 0) {
		rad = M_PI / 4.0f;
		dir = Actor::Direction::DIR_UPRIGHT;
	}
	else if (ySpeed == 0 && xSpeed > 0) {
		rad = 0.0f;
		dir = Actor::Direction::DIR_RIGHT;
	}
	else if (ySpeed < 0 && xSpeed>0) {
		rad = M_PI * 7.0f / 4.0f;
		dir = Actor::Direction::DIR_DOWNRIGHT;
	}
	else if (ySpeed < 0 && xSpeed == 0) {
		rad = M_PI * 3.0f / 2.0f;
		dir = Actor::Direction::DIR_DOWN;
	}
	else if (ySpeed < 0 && xSpeed < 0) {
		rad = M_PI * 5.0f / 4.0f;
		dir = Actor::Direction::DIR_DOWNLEFT;
	}
	else if (ySpeed == 0 && xSpeed < 0) {
		rad = M_PI;
		dir = Actor::Direction::DIR_LEFT;
	}
	else {
		rad = M_PI * 3.0f / 4.0f;
		dir = Actor::Direction::DIR_UPLEFT;
	}
	Vec2 v{ xSpeed,ySpeed };
	if (v.lengthSq() > 0) {
		v = v.normalized() * GetMaxSpeed();
	}
	SetXSpeed(v.x);
	SetYSpeed(v.y);


	float angularSpeed = 0.0f;
	if (inputClockwise.pressed())angularSpeed += GetMaxAngularSpeed();
	if (inputCounterClockwise.pressed())angularSpeed -= GetMaxAngularSpeed();
	SetAngularSpeed(angularSpeed);

	if(!GetOwner()->GetIsSlide()){
		GetOwner()->SetRotation(rad);
		GetOwner()->SetDirection(dir);
	}

	
}
