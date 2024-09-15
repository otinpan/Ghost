#include"Parent.h"
#include"Game.h"

Parent::Parent()
	:mGame(0)
	, mNext(SEQ_NONE)
{
	mGame = new Game();
}

Parent::~Parent() {
	if (mGame)delete mGame;
}


void Parent::update() {
	if (mGame)mGame->update(this);
}

void Parent::moveTo(SeqID next) {
	mNext = next;
}

float GetScreenHeight() {
	return (float)Scene::Height();
}

float GetScreenWidth() {
	return (float)Scene::Width();
}

float GetMagnification() {
	return (float)(Scene::Height() + Scene::Width()) / 4;
}

Vec2 ConvertToView(Vec2 pos) {
	float X = pos.x, Y = pos.y;
	float h = Scene::Height();
	float w = Scene::Width();
	X *= (float)w / 2;
	X += (float)w / 2;
	Y *= (float)-h / 2;
	Y += (float)h / 2;
	return { X,Y };
}

Vec2 ConvertToWorld(Vec2 pos) {
	float X = pos.x, Y = pos.y;
	float h = Scene::Height();
	float w = Scene::Width();
	X *= (float)2 / w;
	X -= 1.0f;
	Y *= -(float)2 / h;
	Y += 1.0f;
	return { X,Y };
}

void DrawRect(Vec2 pos, float width, float height, ColorF color) {
	RectF(Arg::center(ConvertToView(pos)),
		GetScreenWidth() * width / 2,
		GetScreenHeight() * height / 2).draw(color);
}

void DrawRectFrame(Vec2 pos, float width, float height, float linewidth, ColorF color) {
	RectF(Arg::center(ConvertToView(pos)),
		GetScreenWidth() * width / 2,
		GetScreenHeight() * height / 2).drawFrame(linewidth * GetMagnification(), color);
}
