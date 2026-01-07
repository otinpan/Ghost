#pragma once
#include "MoveComponent.h"

class Controller : public MoveComponent {
public:
	enum ControllerType {
		KEYBOARD,
		JOYCON_L0,
		JOYCON_L1,
		JOYCON_L2,
		JOYCON_L3,
		JOYCON_R0,
		JOYCON_R1,
		JOYCON_R2,
		JOYCON_R3,
		NONE,
	};
	Controller(class Actor* owner, ControllerType type);
	~Controller();

	float GetMaxXSpeed() const { return mMaxXSpeed; }
	float GetMaxYSpeed() const { return mMaxYSpeed; }
	float GetMaxAngularSpeed() const { return mMaxAngularSpeed; }
	void SetMaxXSpeed(float speed) { mMaxXSpeed = speed; }
	void SetMaxYSpeed(float speed) { mMaxYSpeed = speed; }
	void SetMaxAngularSpeed(float speed) { mMaxAngularSpeed = speed; }

	Input GetInputA()const {return inputA; }
	Input GetInputB() const { return inputB; }
	Input GetInputX() const { return inputX; }
	Input GetInputY() const { return inputY; }
	Input GetInputL() const { return inputL; }
	Input GetInputR() const { return inputR; }
	Input GetInputPlus() const { return inputPlus; }
	Input GetInputMinus() const { return inputMinus; }
	void SetInputA(Input input) { inputA = input; }
	void SetInputB(Input input) { inputB = input; }
	void SetInputX(Input input) { inputX = input; }
	void SetInputY(Input input) { inputY = input; }
	void SetInputL(Input input) { inputL = input; }
	void SetInputR(Input input) { inputR = input; }
	void SetInputPlus(Input input) { inputPlus = input; }
	void SetInputMinus(Input input) { inputMinus = input; }

	ControllerType GetControllerType() { return mControllerType; }

	void ProcessInput() override = 0;

private:
	ControllerType mControllerType;

	//許容できる最大スピード
	float mMaxXSpeed;
	float mMaxYSpeed;
	float mMaxAngularSpeed;

	// 入力
	Input inputA;
	Input inputB;
	Input inputX;
	Input inputY;
	Input inputL;
	Input inputR;
	Input inputPlus;
	Input inputMinus;
};
