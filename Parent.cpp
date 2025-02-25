#include"Parent.h"
#include"MainMenu.h"
#include"Game.h"
#include"CreateStage.h"
#include"StageSelect.h"

Parent::Parent()
	:mGame(0)
	,mCreateStage(0)
	,mMainMenu(0)
	,mStageSelect(0)
	, mNext(SEQ_NONE)
{
	mMainMenu = new MainMenu();
	//mStageSelect=new StageSelect();
	//mGame = new Game();
	//mCreateStage = new CreateStage();
}

Parent::~Parent() {
	if (mMainMenu)delete mMainMenu;
	if (mStageSelect)delete mStageSelect;
	if (mGame)delete mGame;
	if (mCreateStage)delete mCreateStage;
}


void Parent::update() {
	if (mMainMenu)mMainMenu->update(this);
	if (mStageSelect)mStageSelect->update(this);
	if (mGame)mGame->update(this);
	if (mCreateStage)mCreateStage->update(this);

	switch (mNext) {
	case SEQ_MAINMENU:
		if (mStageSelect)delete mStageSelect;
		if (mCreateStage)delete mCreateStage;
		if (mGame)delete mGame;
		break;
	case SEQ_STAGESELECT:
		if (mMainMenu)delete mMainMenu;
		if (mCreateStage)delete mCreateStage;
		if (mGame)delete mGame;
	case SEQ_GAME:
		if (mMainMenu)delete mMainMenu;
		if (mStageSelect)delete mStageSelect;
		if (mCreateStage)delete mCreateStage;
		break;
	case SEQ_CREATESTAGE:
		if (mMainMenu)delete mMainMenu;
		if (mStageSelect)delete mStageSelect;
		if (mGame)delete mGame;
		break;
	}
	mNext = SEQ_NONE;
}

void Parent::moveTo(SeqID next,SeqID pre) {
	mNext = next;
	mPre = pre;
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

void DrawCircle(Vec2 pos, float rad, ColorF color) {
	Circle{ ConvertToView(pos),rad * GetMagnification()}.draw(color);
}

void DrawRect(Vec2 pos, float width, float height, ColorF color) {
	RectF(Arg::center(ConvertToView(pos)),
		GetScreenWidth() * width / 2,
		GetScreenHeight() * height / 2).draw(color);
}

void DrawRoundRect(Vec2 pos, float width, float height, float round, ColorF color) {
	RoundRect(Arg::center(ConvertToView(pos)),
		GetScreenWidth() * width / 2.0f,
		GetScreenHeight() * height / 2.0f,
		GetMagnification() * round).draw(color);
}

void DrawRectFrame(Vec2 pos, float width, float height, float innerlinewidth,float outerlinewidth, ColorF color) {
	RectF(Arg::center(ConvertToView(pos)),
		GetScreenWidth() * width / 2,
		GetScreenHeight() * height / 2).drawFrame(innerlinewidth * GetMagnification(),outerlinewidth*GetMagnification(), color);
}

void DrawRoundRectFrame(Vec2 pos, float width, float height, float round, float innerlinewidth, float outerlinewidth, ColorF color) {
	RoundRect(Arg::center(ConvertToView(pos)),
		GetScreenWidth() * width / 2.0f,
		GetScreenHeight() * height / 2.0f,
		GetMagnification() * round).drawFrame(innerlinewidth * GetMagnification(), outerlinewidth * GetMagnification(), color);
}

void DrawSquareDotLine(Vec2 pos1, Vec2 pos2, float linewidth, ColorF color) {
	Line{ConvertToView(pos1),ConvertToView(pos2)}
	.draw(LineStyle::SquareDot, linewidth * GetMagnification(),color);
}

void DrawLine(Vec2 pos1, Vec2 pos2, float lineWidth, ColorF color) {
	Line{ ConvertToView(pos1),ConvertToView(pos2) }
	.draw(lineWidth * GetMagnification(), color);
}

void DrawArrow(Vec2 from, Vec2 to, float width, Vec2 headSize,ColorF color) {
	Shape2D::Arrow(ConvertToView(from), ConvertToView(to), GetMagnification() * width, ConvertToView(headSize)).draw(color);
}

void DrawTriangle(Vec2 pos, float length,float deg,ColorF color) {
	Triangle{ ConvertToView(pos),length*GetMagnification(),deg}.draw(color);
}

void DrawTriangle_pos(Vec2 pos0, Vec2 pos1, Vec2 pos2,ColorF color0,ColorF color1,ColorF color2) {
	Triangle{ ConvertToView(pos0),ConvertToView(pos1),ConvertToView(pos2) }.draw(color0, color1, color2);
}

void DrawPlus(float height, float width, Vec2 pos, float angle,ColorF color) {
	Shape2D::Plus(height * GetMagnification(), width * GetMagnification(), ConvertToView(pos), angle).draw(color);
}

void DrawGradiationRect(Vec2 pos, float width, float height, ColorF top, ColorF bottom) {
	RectF(Arg::center(ConvertToView(pos)),
		GetScreenWidth() * width / 2,
		GetScreenHeight() * height / 2).draw(Arg::top (top),Arg::bottom (bottom));
}

void AddDeltaTime(bool &mIsLasting, float &mTime, float mLastTime, float deltaTime) {
	if (mIsLasting) {
		mTime += deltaTime;
		if (mLastTime < mTime) {
			mTime = 0.0f;
			mIsLasting = false;
		}
	}
}

RectF GetViewRect(Vec2 pos, float width, float height) {
	return RectF{ Arg::center(ConvertToView(pos)),GetScreenWidth() * width / 2.0f,GetScreenHeight() * height / 2.0f };
}

Circle GetViewCircle(Vec2 pos, float rad) {
	return Circle{ ConvertToView(pos),GetMagnification() * rad };
}


