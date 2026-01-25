#include"InputComponent_JoyCon.h"
#include"Actor.h"
#define _USE_MATH_DEFINES
#include<math.h>
InputComponent_JoyCon::InputComponent_JoyCon(class Actor* owner, Controller::ControllerType type)
	:Controller(owner, type)
{
	
}

void InputComponent_JoyCon::Initialize() {
	bool isLeft = false;
	switch (GetControllerType()) {
	case ControllerType::JOYCON_L0:
		joy = JoyConL(0);
		isLeft = true;
		break;
	case ControllerType::JOYCON_L1:
		joy = JoyConL(1);
		isLeft = true;
		break;
	case ControllerType::JOYCON_L2:
		joy = JoyConL(2);
		isLeft = true;
		break;
	case ControllerType::JOYCON_L3:
		joy = JoyConL(3);
		isLeft = true;
		break;
	case ControllerType::JOYCON_R0:
		joy = JoyConR(0);
		break;
	case ControllerType::JOYCON_R1:
		joy = JoyConR(1);
		break;
	case ControllerType::JOYCON_R2:
		joy = JoyConR(2);
		break;
	case ControllerType::JOYCON_R3:
		joy = JoyConR(3);
		break;
	default:
		joy = none;
		return;
	}

	if (joy.has_value()) {
		SetInputB(joy->button0);
		SetInputA(joy->button1);
		SetInputY(joy->button2);
		SetInputX(joy->button3);
		SetInputL(joy->buttonSL);
		SetInputR(joy->buttonSR);
		if (isLeft)SetInputPlus(joy->buttonMinus);
		else SetInputPlus(joy->buttonPlus);
	}
}

InputComponent_JoyCon::~InputComponent_JoyCon() {

}

void InputComponent_JoyCon::ProcessInput(){
	float xSpeed = 0.0f;
	float ySpeed = 0.0f;
	float rad = 0.0f;
	Actor::Direction dir=Actor::Direction::DIR_UP;
	if (joy.has_value()) {
		if (auto d = joy->povD8()) {
			switch (*d) {
			case 0:
				ySpeed += GetMaxYSpeed();
				rad = M_PI / 2.0f;
				dir = Actor::Direction::DIR_UP;
				break;
			case 1:
				xSpeed += GetMaxXSpeed();
				ySpeed += GetMaxYSpeed();
				rad = M_PI/4.0f;
				dir = Actor::Direction::DIR_UPRIGHT;
				break;
			case 2:
				xSpeed += GetMaxXSpeed();
				rad = 0.0f;
				dir = Actor::Direction::DIR_RIGHT;
				break;
			case 3:
				xSpeed += GetMaxXSpeed();
				ySpeed -= GetMaxYSpeed();
				rad = M_PI * 7.0f / 4.0f;
				dir = Actor::Direction::DIR_DOWNRIGHT;
				break;
			case 4:
				ySpeed -= GetMaxYSpeed();
				rad = (M_PI * 3.0f / 2.0f);
				dir = Actor::Direction::DIR_DOWN;
				break;
			case 5:
				xSpeed -= GetMaxXSpeed();
				ySpeed -= GetMaxYSpeed();
				rad = M_PI * 5.0f / 4.0f;
				dir = Actor::Direction::DIR_DOWNLEFT;
				break;
			case 6:
				xSpeed -= GetMaxXSpeed();
				rad = M_PI;
				dir = Actor::Direction::DIR_LEFT;
				break;
			case 7:
				xSpeed -= GetMaxXSpeed();
				ySpeed += GetMaxYSpeed();
				rad = M_PI * 3.0f / 4.0f;
				dir = Actor::Direction::DIR_UPLEFT;
				break;
			default:
				break;
			}

		}
	}
	Vec2 v{xSpeed,ySpeed};
	if (v.lengthSq() > 0) {
		v = v.normalized() * GetMaxSpeed();
	}
	SetXSpeed(v.x);
	SetYSpeed(v.y);
	if (!GetOwner()->GetIsSlide()) {
		GetOwner()->SetRotation(rad);
		GetOwner()->SetDirection(dir);
	}
}


