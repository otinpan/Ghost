#include"Parent.h"
#include"Game.h"
#include"CreateStage.h"

Parent::Parent()
	:mGame(0)
	,mCreateStage(0)
	, mNext(SEQ_NONE)
{
	//mGame = new Game();
	mCreateStage = new CreateStage();
}

Parent::~Parent() {
	if (mGame)delete mGame;
	if (mCreateStage)delete mCreateStage;
}


void Parent::update() {
	if (mGame)mGame->update(this);
	if (mCreateStage)mCreateStage->update(this);

	switch (mNext) {
	case SEQ_GAME:
		if (mCreateStage)delete mCreateStage;
		break;
	case SEQ_CREATESTAGE:
		if (mGame)delete mGame;
		break;
	}
	mNext = SEQ_NONE;
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

void DrawRectFrame(Vec2 pos, float width, float height, float innerlinewidth,float outerlinewidth, ColorF color) {
	RectF(Arg::center(ConvertToView(pos)),
		GetScreenWidth() * width / 2,
		GetScreenHeight() * height / 2).drawFrame(innerlinewidth * GetMagnification(),outerlinewidth*GetMagnification(), color);
}

void DrawSquareDotLine(Vec2 pos1, Vec2 pos2, float linewidth, ColorF color) {
	Line{ConvertToView(pos1),ConvertToView(pos2)}
	.draw(LineStyle::SquareDot, linewidth * GetMagnification(),color);
}

void DrawArrow(Vec2 from, Vec2 to, float width, Vec2 headSize,ColorF color) {
	Shape2D::Arrow(ConvertToView(from), ConvertToView(to), GetMagnification() * width, ConvertToView(headSize)).draw(color);
}

void DrawTriangle(Vec2 pos, float length,float deg,ColorF color) {
	Triangle{ ConvertToView(pos),length*GetMagnification(),deg}.draw(color);
}
