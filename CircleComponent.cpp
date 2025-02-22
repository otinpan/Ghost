#include "CircleComponent.h"
#include "Actor.h"
#include "Game.h"

CircleComponent::CircleComponent(class Actor* owner,int drawOrder,bool isBackground)
	:DrawingComponent(owner,drawOrder,isBackground)
	, mRadius(0.0f)
	, mCenter(owner->GetPosition())
	, mColor(ColorF({ 0.0,0.0,0.0 }))
{
}

CircleComponent::~CircleComponent() {
	if (mOwner->GetCreateStage()) {
		mOwner->GetCreateStage()->RemoveCircle(this);
	}
	if (mOwner->GetGame()) {
		mOwner->GetGame()->RemoveCircle(this);
	}
}

void CircleComponent::InitializeDrawing_CreateStage() {
	Initialize_CreateStage();
	mOwner->GetCreateStage()->AddCircle(this);
}

void CircleComponent::InitializeDrawing_Game() {
	Initialize_Game();
	mOwner->GetGame()->AddCircle(this);
}



float CircleComponent::GetRadius()const {
	return mOwner->GetScale() * mRadius;
}

const Vec2& CircleComponent::GetCenter()const {
	return mCenter;
}


void CircleComponent::Draw() {
	if (!GetIsDraw())return;
	DrawCircle(mCenter, mRadius, mColor);
}

const Circle CircleComponent::GetCircle() {
return Circle{ mCenter,mRadius };
}

const Circle CircleComponent::GetViewCircle() {
	return Circle{ ConvertToView(mCenter),GetMagnification() * mRadius };
}


bool IsIntersect_CC(class CircleComponent* a, class CircleComponent* b) {
	Circle aCircle = Circle{ a->GetCenter(), a->GetRadius() };
	Circle bCircle = Circle{ b->GetCenter(),b->GetRadius() };
	if (aCircle.intersects(bCircle))return true;
	else return false;
}
