#pragma once
#include<Siv3D.hpp>
#define INCLUDED_SEQUENCE_PARENT_H

class Parent {
public:
	enum SeqID {
		SEQ_MAINMENU,
		SEQ_STAGESELECT,
		SEQ_GAME,
		SEQ_CREATESTAGE,
		SEQ_NONE,
	};

	Parent();
	~Parent();
	void update();

	void moveTo(SeqID next,SeqID pre);

	class MainMenu*& GetMainMenu() { return mMainMenu; }
	class StageSelect* &GetStageSelect() { return mStageSelect; }
	class Game*& GetGame() { return mGame; }
	class CreateStage*& GetCreateStage() { return mCreateStage; }

	SeqID GetNextSeq() { return mNext; }
	SeqID GetPreSeq() { return mPre; }

private:
	class MainMenu* mMainMenu;
	class StageSelect* mStageSelect;
	class Game* mGame;
	class CreateStage* mCreateStage;

	SeqID mNext;
	SeqID mPre;
};


Vec2 ConvertToView(Vec2 pos);
Vec2 ConvertToWorld(Vec2 pos);
void DrawCircle(Vec2 pos, float rad, ColorF color);
void DrawRect(Vec2 pos, float width, float height, ColorF color);  //posは中心の座標
void DrawRoundRect(Vec2 pos, float width, float height, float round, ColorF color);  //roundの半径の円だけけどを丸める
void DrawRectFrame(Vec2 pos, float width, float height, float innerlinewidth,float outerlinewidth, ColorF color);
void DrawRoundRectFrame(Vec2 pos, float width, float height, float round, float innerline, float outerline, ColorF color);
void DrawSquareDotLine(Vec2 pos1, Vec2 pos2, float linewidth, ColorF color);
void DrawLine(Vec2 pos1, Vec2 pos2, float lineWidth, ColorF color);
float GetMagnification();
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
