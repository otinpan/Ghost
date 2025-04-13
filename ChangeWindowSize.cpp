#include"ChangeWindowSize.h"

ChangeWindowSize::ChangeWindowSize()
	:mIsRunning(true)
	,mSeqID(Parent::SEQ_NONE)
{
	Initialize();
}

ChangeWindowSize::~ChangeWindowSize(){}

void ChangeWindowSize::Initialize() {
	Scene::SetBackground(ColorF(1));

	float fs = 0.1 * GetMagnification();
	int32 FontSize = (int32)fs;
	HelpFont = Font(FontSize, Typeface::Medium);
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
	Window::SetStyle(WindowStyle::Sizable);
	Scene::SetResizeMode(ResizeMode::Actual);

	if (KeyEnter.down()||KeyEscape.down()) {
		Scene::SetResizeMode(ResizeMode::Keep);
		mSeqID = Parent::SEQ_MAINMENU;
	}
}

void ChangeWindowSize::draw() {
	HelpFont(U"画面のサイズを変更できます").drawAt(ConvertToView(Vec2(0, 0)), ColorF(0));
	HelpFont(U"[Enter],[Escape]キーで決定").drawAt(ConvertToView(Vec2(0, -0.3)), ColorF(0));
}

void ChangeWindowSize::Shutdown() {

}

void ChangeWindowSize::moveTo(Parent* parent,Parent::SeqID id) {
	if (id == Parent::Parent::SEQ_MAINMENU)parent->moveTo(Parent::SEQ_MAINMENU, Parent::SEQ_CHANGEWINDOWSIZE);
	if (id == Parent::Parent::SEQ_STAGESELECT)parent->moveTo(Parent::SEQ_STAGESELECT, Parent::SEQ_CHANGEWINDOWSIZE);
	if (id == Parent::Parent::SEQ_GAMERESULT)parent->moveTo(Parent::SEQ_GAMERESULT, Parent::SEQ_CHANGEWINDOWSIZE);
	if (id == Parent::Parent::SEQ_CREATESTAGE)parent->moveTo(Parent::SEQ_CREATESTAGE, Parent::SEQ_CHANGEWINDOWSIZE);
	if (id == Parent::Parent::SEQ_GAME)parent->moveTo(Parent::SEQ_GAME, Parent::SEQ_CHANGEWINDOWSIZE);
	if (id == Parent::Parent::SEQ_CHANGEWINDOWSIZE)parent->moveTo(Parent::SEQ_CHANGEWINDOWSIZE, Parent::SEQ_CHANGEWINDOWSIZE);
}
