#pragma once
#include "Controller.h"
#include"Siv3D.hpp"

class InputComponent_Keyboard :public Controller {
public:
	InputComponent_Keyboard(class Actor* owner);
	~InputComponent_Keyboard();

	void Initialize();

	void ProcessInput()override;


	InputGroup GetInputUp() const { return inputUp; }
	InputGroup GetInputDown() const { return inputDown; }
	InputGroup GetInputRight() const { return inputRight; }
	InputGroup GetInputLeft() const { return inputLeft; }
	InputGroup GetInputClockwise() const { return inputClockwise; }
	InputGroup GetInputCounterClockwise() const { return inputCounterClockwise; }



	void SetInputUp(Input key) { inputUp = key; }
	void SetInputDown(InputGroup key) { inputDown = key; }
	void SetInputRight(InputGroup key) { inputRight = key; }
	void SetInputLeft(InputGroup key) { inputLeft = key; }
	void SetInputClockwise(InputGroup key) { inputClockwise = key; }
	void SetInputCounterClockwise(InputGroup key) { inputCounterClockwise = key;}

private:


	Input inputUp;
	InputGroup inputDown;
	InputGroup inputRight;
	InputGroup inputLeft;
	InputGroup inputClockwise;
	InputGroup inputCounterClockwise;
	
};
