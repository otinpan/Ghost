#pragma once
#include<Siv3D.hpp>
#include "Controller.h"
#define INCLUDED_SEQUENCE_PARENT_H

class Parent {
public:
	enum SeqID {
		SEQ_MAINMENU,
		SEQ_SUBMENU,
		SEQ_REGISTERCONTROLLER,
		SEQ_STAGESELECT,
		SEQ_GAME,
		SEQ_CREATESTAGE,
		SEQ_GAMERESULT,
		SEQ_CHANGEWINDOWSIZE,
		SEQ_NONE,
	};

	enum GameJudgement {
		GHOST_WIN,
		ESCAPEES_WIN,
		DRAW,
		NONE,
	};

	Parent();
	~Parent();
	void update();

	void moveTo(SeqID next, SeqID pre);
	void setStageName(String stageName);
	void setStageSelectGame(bool isStageSelectGame) { mIsStageSelectGame = isStageSelectGame; }

	void setGameJudgement(GameJudgement judge) { mGameJudgement = judge; }
	void setControllers(const std::vector<Controller::ControllerType> controllers) { mControllers = controllers; }

	class MainMenu*& GetMainMenu() { return mMainMenu; }
	class SubMenu*& GetSubMenu() { return mSubMenu; }
	class StageSelect*& GetStageSelect() { return mStageSelect; }
	class Game*& GetGame() { return mGame; }
	class CreateStage*& GetCreateStage() { return mCreateStage; }
	class GameResult*& GetGameResult() { return mGameResult; }
	class ChangeWindowSize*& GetChangeWindowSize() { return mChangeWindowSize;}

	SeqID GetNextSeq() { return mNext; }
	SeqID GetPreSeq() { return mPre; }


private:
	class MainMenu* mMainMenu;
	class SubMenu* mSubMenu;
	class RegisterController* mRegisterController;
	class StageSelect* mStageSelect;
	class Game* mGame;
	class CreateStage* mCreateStage;
	class GameResult* mGameResult;
	class ChangeWindowSize* mChangeWindowSize;

	SeqID mNext;
	SeqID mPre;

	String mSelectedStageName;
	bool mIsStageSelectGame;

	// Controller
	std::vector<Controller::ControllerType> mControllers;

	// gameの勝敗
	GameJudgement mGameJudgement = NONE;

	void SafeDelete();
	
};

Vec2 ConvertToView(Vec2 pos);
Vec2 ConvertToWorld(Vec2 pos);
void DrawCircle(Vec2 pos, float rad, ColorF color);
void DrawRect(Vec2 pos, float width, float height, ColorF color);  //posは中心の座標
void DrawRotateRect(Vec2 pos, float width, float height, float radian, ColorF color);
void DrawRoundRect(Vec2 pos, float width, float height, float round, ColorF color);  //roundの半径の円だけけどを丸める
void DrawRectFrame(Vec2 pos, float width, float height, float innerlinewidth,float outerlinewidth, ColorF color);
void DrawRoundRectFrame(Vec2 pos, float width, float height, float round, float innerline, float outerline, ColorF color);
void DrawSquareDotLine(Vec2 pos1, Vec2 pos2, float linewidth, ColorF color);
void DrawLine(Vec2 pos1, Vec2 pos2, float lineWidth, ColorF color);
float GetScreenHeight();
float GetScreenWidth();
void DrawArrow(Vec2 from, Vec2 to, float width, Vec2 headSize,ColorF color);
void DrawTriangle(Vec2 pos, float length,float deg,ColorF color);
void DrawTriangle_pos(Vec2 pos0, Vec2 pos1, Vec2 pos2,ColorF color0,ColorF color1,ColorF color2);
void AddDeltaTime(bool&mIsLasting,float &mTime,float mLastTime,float deltaTime);
void DrawPlus(float hegiht, float width, Vec2 pos, float angle, ColorF color);
void DrawGradiationRect(Vec2 pos, float width, float height, ColorF top, ColorF bottom);
RectF GetViewRect(Vec2 pos, float width, float height);
Circle GetViewCircle(Vec2 pos, float rad);
int ConvertToInt(float f);
