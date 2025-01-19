#pragma once
#include"DrawingComponent.h"
#include<Siv3D.hpp>


class SquareComponent :public DrawingComponent {
public:
	SquareComponent(class Actor* owner, int drawOrder, bool isBackground);
	~SquareComponent();

	void InitializeDrawing_Game(Vec2 pos, float width, float height);
	void InitializeDrawing_CreateStage(Vec2 pos, float width, float height);

	void SetWidth(float width) { mWidth = width; }
	void SetHeight(float height) { mHeight = height; }
	void SetCenter(Vec2 pos) { mCenter = pos; }
	void SetColor(ColorF color) { mColor = color; }
	const float GetLeft();
	const float GetRight();
	const float GetUp();
	const float GetDown();

	const RectF GetRect();
	const RectF GetViewRect();

	float GetWidth() const;
	float GetHeight() const;
	const Vec2& GetCenter() const;

	void Draw() override;

private:
	float mWidth;
	float mHeight;
	Vec2 mCenter;
	ColorF mColor;
};

bool IsIntersect_SC(class SquareComponent* a, class CircleComponent* b);
bool IsIntersect_SS(class SquareComponent* a, class SquareComponent* b);
