#include"Parent.h"
#include"MainMenu.h"
#include"RegisterController.h"
#include"Game.h"
#include"CreateStage.h"
#include"StageSelect.h"
#include"GameResult.h"
#include"ChangeWindowSize.h"
#include"SubMenu.h"
#include"Title.h";

Parent::Parent()
	:mGame(0)
	,mCreateStage(0)
	,mMainMenu(0)
	,mGameResult(0)
	,mChangeWindowSize(0)
	,mSubMenu(0)
	,mStageSelect(0)
	, mNext(SEQ_NONE)
{
	mTitle = new Title();
	//mMainMenu = new MainMenu();
	//mSubMenu = new SubMenu();
	//mRegisterController = new RegisterController();
	//mStageSelect=new StageSelect(false);
	//mGame = new Game();
	//mCreateStage = new CreateStage();
	//mGameResult = new GameResult(Parent::GameJudgement::DRAW);
	//mChangeWindowSize=new ChangeWindowSize();
}

Parent::~Parent() {
	if (mTitle)delete mTitle;
	if (mMainMenu)delete mMainMenu;
	if (mSubMenu)delete mSubMenu;
	if (mStageSelect)delete mStageSelect;
	if (mGame)delete mGame;
	if (mCreateStage)delete mCreateStage;
	if (mGameResult)delete mGameResult;
	if (mChangeWindowSize)delete mChangeWindowSize;
}


void Parent::update() {
	switch (mNext) {
	case SEQ_TITLE:
		SafeDelete();
		mTitle = new Title();
		break;
	case SEQ_MAINMENU:
		SafeDelete();
		mMainMenu = new MainMenu();
		break;
	case SEQ_SUBMENU:
		SafeDelete();
		mSubMenu = new SubMenu();
		break;
	case SEQ_REGISTERCONTROLLER:
		SafeDelete();
		mRegisterController = new RegisterController();
		break;
	case SEQ_STAGESELECT:
		SafeDelete();
		mStageSelect = new StageSelect(mIsStageSelectGame);
		break;
	case SEQ_GAME:
		SafeDelete();
		mGame = new Game(mSelectedStageName,mControllers);
		break;
	case SEQ_CREATESTAGE:
		SafeDelete();
		mCreateStage = new CreateStage(mSelectedStageName);
		break;
	case SEQ_GAMERESULT:
		SafeDelete();
		mGameResult = new GameResult(mGameJudgement);
		break;
	case SEQ_CHANGEWINDOWSIZE:
		SafeDelete();
		mChangeWindowSize = new ChangeWindowSize();
		break;
	}
	
	mNext = SEQ_NONE;

	if (mTitle)mTitle->update(this);
	if (mMainMenu)mMainMenu->update(this);
	if (mSubMenu)mSubMenu->update(this);
	if (mRegisterController) mRegisterController->update(this);
	if (mStageSelect)mStageSelect->update(this);
	if (mGame)mGame->update(this);
	if (mCreateStage)mCreateStage->update(this);
	if (mGameResult)mGameResult->update(this);
	if (mChangeWindowSize)mChangeWindowSize->update(this);

}

void Parent::SafeDelete() {
	if (mTitle) {
		delete mTitle;
		mTitle = nullptr;
	}
	if (mMainMenu) {
		delete mMainMenu;
		mMainMenu = nullptr;
	}
	if (mSubMenu) {
		delete mSubMenu;
		mSubMenu = nullptr;
	}
	if (mRegisterController) {
		delete mRegisterController;
		mRegisterController = nullptr;
	}
	if (mStageSelect) {
		delete mStageSelect;
		mStageSelect = nullptr;
	}
	if (mGame) {
		delete mGame;
		mGame = nullptr;
	}
	if (mCreateStage) {
		delete mCreateStage;
		mCreateStage = nullptr;
	}
	if (mGameResult) {
		delete mGameResult;
		mGameResult = nullptr;
	}
	if (mChangeWindowSize) {
		delete mChangeWindowSize;
		mChangeWindowSize = nullptr;
	}
}

void Parent::moveTo(SeqID next,SeqID pre) {
	mNext = next;
	mPre = pre;
}

void Parent::setStageName(String stageName) {
	mSelectedStageName = stageName;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////

float GetScreenHeight() {
	return (float)Scene::Height();
}

float GetScreenWidth() {
	return (float)Scene::Width();
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
	Circle{ ConvertToView(pos),rad * GetScreenHeight()}.draw(color);
}

void DrawRect(Vec2 pos, float width, float height, ColorF color) {
	RectF(Arg::center(ConvertToView(pos)),
		GetScreenWidth() * width / 2,
		GetScreenHeight() * height / 2).draw(color);
}

void DrawRotateRect(Vec2 pos, float width, float height, float radian, ColorF color) {
	RectF(GetScreenWidth() * width / 2,
		GetScreenHeight() * height / 2)
		.setCenter(ConvertToView(pos))
		.rotate90(radian)
		.draw(color);
}

void DrawRoundRect(Vec2 pos, float width, float height, float round, ColorF color) {
	s3d::RoundRect(Arg::center(ConvertToView(pos)),
		GetScreenWidth() * width / 2.0f,
		GetScreenHeight() * height / 2.0f,
		GetScreenHeight() * round).draw(color);
}

void DrawRectFrame(Vec2 pos, float width, float height, float innerlinewidth,float outerlinewidth, ColorF color) {
	RectF(Arg::center(ConvertToView(pos)),
		GetScreenWidth() * width / 2,
		GetScreenHeight() * height / 2).drawFrame(innerlinewidth * GetScreenHeight(),outerlinewidth*GetScreenHeight(), color);
}

void DrawRoundRectFrame(Vec2 pos, float width, float height, float round, float innerlinewidth, float outerlinewidth, ColorF color) {
	s3d::RoundRect(Arg::center(ConvertToView(pos)),
		GetScreenWidth() * width / 2.0f,
		GetScreenHeight() * height / 2.0f,
		GetScreenHeight() * round).drawFrame(innerlinewidth * GetScreenHeight(), outerlinewidth * GetScreenHeight(), color);
}


void DrawSquareDotLine(Vec2 pos1, Vec2 pos2, float linewidth, ColorF color) {
	Line{ConvertToView(pos1),ConvertToView(pos2)}
	.draw(LineStyle::SquareDot, linewidth * GetScreenHeight(),color);
}

void DrawLine(Vec2 pos1, Vec2 pos2, float lineWidth, ColorF color) {
	Line{ ConvertToView(pos1),ConvertToView(pos2) }
	.draw(lineWidth * GetScreenHeight(), color);
}

void DrawArrow(Vec2 from, Vec2 to, float width, Vec2 headSize,ColorF color) {
	Shape2D::Arrow(ConvertToView(from), ConvertToView(to), GetScreenHeight() * width, ConvertToView(headSize)).draw(color);
}

void DrawTriangle(Vec2 pos, float length,float deg,ColorF color) {
	Triangle{ ConvertToView(pos),length*GetScreenHeight(),deg}.draw(color);
}

void DrawTriangle_pos(Vec2 pos0, Vec2 pos1, Vec2 pos2,ColorF color0,ColorF color1,ColorF color2) {
	Triangle{ ConvertToView(pos0),ConvertToView(pos1),ConvertToView(pos2) }.draw(color0, color1, color2);
}

void DrawPlus(float height, float width, Vec2 pos, float angle,ColorF color) {
	Shape2D::Plus(height * GetScreenHeight(), width * GetScreenHeight(), ConvertToView(pos), angle).draw(color);
}

void DrawGradiationRect(Vec2 pos, float width, float height, ColorF top, ColorF bottom) {
	RectF(Arg::center(ConvertToView(pos)),
		GetScreenWidth() * width / 2,
		GetScreenHeight() * height / 2).draw(Arg::top (top),Arg::bottom (bottom));
}

void DrawTexture(TextureAsset texture, Vec2 pos, float width, float height, float rot = 0.0) {
	Texture(texture).resized(width * GetScreenWidth(), height * GetScreenHeight()).rotated(rot).drawAt(ConvertToView(pos));
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
	return Circle{ ConvertToView(pos),GetScreenHeight() * rad };
}


int ConvertToInt(float f) {
	return (int)f;
}
