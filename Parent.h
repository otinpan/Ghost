#pragma once
#include<Siv3D.hpp>
#define INCLUDED_SEQUENCE_PARENT_H

class Parent {
public:
	enum SeqID {
		SEQ_GAME,
		SEQ_CREATESTAGE,
		SEQ_NONE,
	};

	Parent();
	~Parent();
	void update();

	void moveTo(SeqID);

private:
	class Game* mGame;
	class CreateStage* mCreateStage;

	SeqID mNext;
};


Vec2 ConvertToView(Vec2 pos);
Vec2 ConvertToWorld(Vec2 pos);
void DrawRect(Vec2 pos, float width, float height, ColorF color);  //posは中心の座標
void DrawRectFrame(Vec2 pos, float width, float height, float innerlinewidth,float outerlinewidth, ColorF color);
void DrawSquareDotLine(Vec2 pos1, Vec2 pos2, float linewidth, ColorF color);
float GetMagnification();
float GetScreenHeight();
float GetScreenWidth();
void DrawArrow(Vec2 from, Vec2 to, float width, Vec2 headSize,ColorF color);
void DrawTriangle(Vec2 pos, float length,float deg,ColorF color);
