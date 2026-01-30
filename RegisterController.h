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

	// 接続の切れたコントローラーを削除
	void DeleteCanceledController();

	// コントローラー
	std::vector<Controller::ControllerType> mControllers;
	bool IsExistController(Controller::ControllerType type); // mControllersにtypeが既に存在するか
	bool DeleteController(Controller::ControllerType type); 

	// 描画
	std::vector<Vec2> mControllersPos;
	std::vector<Vec2> mPlayersPos;
	float eachWidth;
	float drawSize;
	bool mIsAccepted; //登録人数が正しいか
	void DrawKeyboard(Vec2 pos);
	void DrawJoyCon(Controller::ControllerType type,Vec2 pos);
	void DrawPlayers();
	Effect effect;

	// font
	Font mHelpFont{ ConvertToInt((float)0.03 * GetScreenHeight()),Typeface::Black,FontStyle::Bitmap };
	Font mStartFont{ ConvertToInt((float)0.1 * GetScreenHeight()),Typeface::Bold,FontStyle::Bitmap };

	Parent::SeqID mSeqID;
	bool mIsRunning;
};
