#pragma once
#include"DrawingComponent.h"
#include"Siv3D.hpp"


class CircleComponent :public DrawingComponent {
public:
	CircleComponent(class Actor* owner,int drawOrder,bool isBackground);
	~CircleComponent();

	//void Update(float deltaTime)override;

	void InitializeDrawing_Game();
	void InitializeDrawing_CreateStage();

	const Circle GetCircle();
	const Circle GetViewCircle();

	void SetRadius(float radius) { mRadius = radius; }
	void SetCenter(Vec2 pos) { mCenter = pos; }
	void SetColor(ColorF color) { mColor = color; }

	float GetRadius()const;
	const Vec2& GetCenter() const;

	void Draw() override;


private:
	Vec2 mCenter;
	float mRadius;
	ColorF mColor;
};

bool IsIntersect_CC(class CircleComponent* a, class CircleComponent* b);
