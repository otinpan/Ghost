#include"InputComponent_JoyCon.h"

InputComponent_JoyCon::InputComponent_JoyCon(class Actor* owner, Controller::ControllerType type)
	:Controller(owner, type)
{
	
}

void InputComponent_JoyCon::Initialize() {
	switch (GetControllerType()) {
	case ControllerType::JOYCON_L0:
		joy = JoyConL(0);
		break;
	case ControllerType::JOYCON_L1:
		joy = JoyConL(1);
		break;
	case ControllerType::JOYCON_L2:
		joy = JoyConL(2);
		break;
	case ControllerType::JOYCON_L3:
		joy = JoyConL(3);
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
		SetInputPlus(joy->buttonPlus);
		SetInputMinus(joy->buttonMinus);
	}
}

InputComponent_JoyCon::~InputComponent_JoyCon() {

}

void InputComponent_JoyCon::ProcessInput(){
	float xSpeed = 0.0f;
	float ySpeed = 0.0f;
	if (joy.has_value()) {
		if (auto d = joy->povD8()) {
			switch (d.has_value()) {
			case 0:
				xSpeed += GetMaxXSpeed();
				break;
			case 1:
				xSpeed += GetMaxXSpeed();
				ySpeed += GetMaxYSpeed();
				break;
			case 2:
				xSpeed += GetMaxXSpeed();
				break;
			case 3:
				xSpeed += GetMaxXSpeed();
				ySpeed -= GetMaxYSpeed();
				break;
			case 4:
				ySpeed -= GetMaxYSpeed();
				break;
			case 5:
				xSpeed -= GetMaxXSpeed();
				ySpeed -= GetMaxYSpeed();
				break;
			case 6:
				xSpeed -= GetMaxXSpeed();
				break;
			case 7:
				xSpeed -= GetMaxXSpeed();
				ySpeed += GetMaxYSpeed();
				break;
			default:
				break;
			}

		}
	}
	SetXSpeed(xSpeed);
	SetYSpeed(ySpeed);
}


