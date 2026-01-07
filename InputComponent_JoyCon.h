#pragma once
#include "Controller.h"

class InputComponent_JoyCon: public Controller{
public:
	InputComponent_JoyCon(class Actor* actor, Controller::ControllerType type);
	~InputComponent_JoyCon();

	void Initialize();

	
	void ProcessInput() override;

	
	Optional<JoyCon> GetJoyCon() const { return joy; }

private:
	Optional<JoyCon> joy;


	// スティック入力は変数に出来ない
};
