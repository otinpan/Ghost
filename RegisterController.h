#pragma once
#include"Parent.h"
#include"Common.h"
#include"Actor.h"
#include"Controller.h"

class RegisterController {
public:
	RegisterController();
	~RegisterController();

	void update(class Parent*);
	void draw();

	void Initialize();
	void Shutdown();

	void moveTo(Parent* parent, Parent::SeqID id);
	void SetSeqID(Parent::SeqID id) { mSeqID = id; }


private:
	void ProcessInput();
	void UpdateRegisterController();

	// コントローラー
	std::vector<Controller::ControllerType> mControllers;
	int mControllerIteration;
	bool IsExistController(Controller::ControllerType type); // mControllersにtypeが既に存在するか
	bool DeleteController(Controller::ControllerType type); 

	// 描画
	std::vector<Vec2> mControllersPos;
	float drawSize;
	void DrawKeyboard(Vec2 pos);
	void DrawJoyCon(Controller::ControllerType type,Vec2 pos);

	Parent::SeqID mSeqID;
	bool mIsRunning;
};
