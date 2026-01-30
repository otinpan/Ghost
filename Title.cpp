#include"Title.h"

Title::Title() {
	Scene::SetBackground(ColorF(0.0f));
}

Title::~Title() {

}

void Title::update(Parent* parent) {
	if (timer > 3.0f) {
		if (MouseL.down() || KeySpace.down()) {
			parent->moveTo(Parent::SEQ_MAINMENU, Parent::SEQ_TITLE);
		}
	}
	timer += Scene::DeltaTime();
	draw();
}

void Title::draw() {
	titleFont(U"Ghost").draw(Arg::center(ConvertToView(Vec2(0.4f, 0.0f))), ColorF(1.0f));
	titleFont(U"Siv3D").draw(Arg::center(ConvertToView(Vec2(-0.4f, 0.0f))), ColorF(1.0f));
}
