#include "Controller.h"

Controller::Controller(class Actor* owner, ControllerType type)
	:MoveComponent(owner)
	, mControllerType(type)
	, mMaxAngularSpeed(0.0f)
	, mMaxXSpeed(0.0f)
	, mMaxYSpeed(0.0f)
{

}

Controller::~Controller() {

}
