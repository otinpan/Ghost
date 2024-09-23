#pragma once
#include"Component.h"
#include<Siv3D.hpp>


class SquareComponent :public Component {
public:
	SquareComponent(class Actor* owner);
	~SquareComponent();

	void Initialize_CreateStage();
	void Initialize_Game();

	void SetWidth(float width) { mWidth = width; }
	void SetHeight(float height) { mHeight = height; }
	void SetCenter(Vec2 pos) { mCenter = pos; }
	void SetColor(ColorF color) { mColor = color; }

	float GetWidth() const;
	float GetHeight() const;
	const Vec2& GetCenter() const;

	void Draw();

private:
	float mWidth;
	float mHeight;
	Vec2 mCenter;
	ColorF mColor;
};
