#include"InputComponent_Keyboard.h"
#include"Actor.h"

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

	if (inputRight.pressed())xSpeed += GetMaxXSpeed();
	if (inputLeft. pressed())xSpeed -= GetMaxXSpeed();

	float ySpeed = 0.0f;
	if (inputUp.pressed())ySpeed += GetMaxYSpeed();
	if (inputDown.pressed())ySpeed -= GetMaxYSpeed();

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

	
}
