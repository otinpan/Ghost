#include"ChangeWindowSize.h"

ChangeWindowSize::ChangeWindowSize()
	:mIsRunning(true)
	,mSeqID(Parent::SEQ_NONE)
{
	Initialize();
}

ChangeWindowSize::~ChangeWindowSize(){
	Shutdown();
}

void ChangeWindowSize::Initialize() {
	Scene::SetBackground(ColorF(1));
	Window::SetStyle(WindowStyle::Sizable);

	float fs = 0.08 * GetScreenHeight();
	int32 fontSize = (int32)fs;
	FontAsset::Register(U"HelpFont_ChangeWindowSize", fontSize, Typeface::Medium);
}

void ChangeWindowSize::update(Parent* parent) {
	if (mIsRunning) {
		if (mSeqID != Parent::SEQ_NONE) {
			moveTo(parent, mSeqID);
			return;
		}
		ProcessInput();
		UpdateChangeWindowSize();
		draw();
	}
}

void ChangeWindowSize::ProcessInput() {

}

void ChangeWindowSize::UpdateChangeWindowSize() {
	//aspect fix 16:9 
	int mag_width = Window::GetState().virtualSize.x / 16;
	int mag__height = Window::GetState().virtualSize.y / 9;
	int mag = std::min(mag_width, mag__height);
	Scene::Resize(16 * mag, 9 * mag);

	if (KeyEnter.down()||KeyEscape.down()) {
		mSeqID = Parent::SEQ_SUBMENU;
	}
}

void ChangeWindowSize::draw() {
	FontAsset(U"HelpFont_ChangeWindowSize")(U"画面のサイズを変更できます").drawAt(ConvertToView(Vec2(0, 0)), ColorF(0));
	FontAsset(U"HelpFont_ChangeWindowSize")(U"[Enter],[Escape]キーで決定").drawAt(ConvertToView(Vec2(0, -0.3)), ColorF(0));
	
}

void ChangeWindowSize::Shutdown() {
	Window::SetStyle(WindowStyle::Fixed);
}

void ChangeWindowSize::moveTo(Parent* parent,Parent::SeqID id) {
	if (id == Parent::Parent::SEQ_MAINMENU)parent->moveTo(Parent::SEQ_MAINMENU, Parent::SEQ_CHANGEWINDOWSIZE);
	if (id == Parent::Parent::SEQ_SUBMENU)parent->moveTo(Parent::SEQ_SUBMENU, Parent::SEQ_CHANGEWINDOWSIZE);
	if (id == Parent::Parent::SEQ_STAGESELECT)parent->moveTo(Parent::SEQ_STAGESELECT, Parent::SEQ_CHANGEWINDOWSIZE);
	if (id == Parent::Parent::SEQ_GAMERESULT)parent->moveTo(Parent::SEQ_GAMERESULT, Parent::SEQ_CHANGEWINDOWSIZE);
	if (id == Parent::Parent::SEQ_CREATESTAGE)parent->moveTo(Parent::SEQ_CREATESTAGE, Parent::SEQ_CHANGEWINDOWSIZE);
	if (id == Parent::Parent::SEQ_GAME)parent->moveTo(Parent::SEQ_GAME, Parent::SEQ_CHANGEWINDOWSIZE);
	if (id == Parent::Parent::SEQ_CHANGEWINDOWSIZE)parent->moveTo(Parent::SEQ_CHANGEWINDOWSIZE, Parent::SEQ_CHANGEWINDOWSIZE);
}
