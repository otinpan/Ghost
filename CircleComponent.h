#pragma once
#include"Component.h"
#include"Siv3D.hpp"


class CircleComponent :public Component {
public:
	CircleComponent(class Actor* owner);
	~CircleComponent();

	//void Update(float deltaTime)override;

	void Initialize_Game();
	void Initialize_CreateStage();

	const Circle GetCircle();
	const Circle GetViewCircle();

	void SetRadius(float radius) { mRadius = radius; }
	void SetCenter(Vec2 pos) { mCenter = pos; }
	void SetColor(ColorF color) { mColor = color; }

	float GetRadius()const;
	const Vec2& GetCenter() const;

	void Draw();


private:
	Vec2 mCenter;
	float mRadius;
	ColorF mColor;
};

bool IsIntersect_CC(class CircleComponent* a, class CircleComponent* b);
