#pragma once
#include"DrawingComponent.h"
#include<Siv3D.hpp>

class TriangleComponent :public DrawingComponent {
public:
	TriangleComponent(class Actor* owner, int drawOrder, DrawingState drwaState);
	~TriangleComponent();

	void InitializeDrawing_CreateStage(Vec2 pos0, Vec2 pos1, Vec2 pos2);
	void InitializeDrawing_Game(Vec2 pos0, Vec2 pos1, Vec2 pos2);

	void SetPos0(Vec2 pos0) { mPos0 = pos0; }
	Vec2 GetPos0() { return mPos0; }
	void SetPos1(Vec2 pos1) { mPos1 = pos1; }
	Vec2 GetPos1() { return mPos1; }
	void SetPos2(Vec2 pos2) { mPos2 = pos2; }
	Vec2 GetPos2() { return mPos2; }

	void SetColor0(ColorF color0) { mColor0 = color0; }
	void SetColor1(ColorF color1) { mColor1 = color1; }
	void SetColor2(ColorF color2) { mColor2 = color2; }

	void Draw();
private:
	Vec2 mPos0;
	Vec2 mPos1;
	Vec2 mPos2;

	ColorF mColor0;
	ColorF mColor1;
	ColorF mColor2;

};

bool IsIntersect_TT(class TriangleComponent* t1, class TriangleComponent* t2);
bool IsIntersect_TC(class TriangleComponent* t, class CircleComponent* c);
bool IsIntersect_TS(class TriangleComponent* t, class SquareComponent* s);
