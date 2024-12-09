#include"SquareComponent.h"
#include"CircleComponent.h"
#include"Actor.h"

SquareComponent::SquareComponent(class Actor* owner)
	:Component(owner)
	,mWidth(0.0f)
	,mHeight(0.0f)
	,mCenter(Vec2{0,0})
	,mColor(ColorF({0,0,0}))
{

}

SquareComponent::~SquareComponent() {
	if (mOwner->GetCreateStage()) {
		mOwner->GetCreateStage()->RemoveSquare(this);
	}
	if (mOwner->GetGame()) {
		mOwner->GetGame()->RemoveSquare(this);
	}

}

void SquareComponent::Initialize_Game
(Vec2 pos,float width,float height) {
	mOwner->GetGame()->AddSquare(this);
	mCenter = pos;
	mWidth = width;
	mHeight = height;
}

void SquareComponent::Initialize_CreateStage
(Vec2 pos,float width,float height) {
	mOwner->GetCreateStage()->AddSquare(this);
	mCenter = pos;
	mWidth = width;
	mHeight = height;
}

float SquareComponent::GetWidth() const{
	return mOwner->GetScale() * mWidth;
}

float SquareComponent::GetHeight() const {
	return mOwner->GetScale() * mHeight;
}

const Vec2& SquareComponent::GetCenter()const {
	return mCenter;
}


void SquareComponent::Draw() {
	DrawRect(mCenter, mWidth, mHeight, mColor);
}

const RectF SquareComponent::GetRect() {
	return RectF{ Arg::center(mCenter),mWidth,mHeight };
}

const RectF SquareComponent::GetViewRect() {
	return RectF{ Arg::center(ConvertToView(mCenter)),GetScreenWidth() * mWidth/2.0f,GetScreenHeight() * mHeight/2.0f };
}

bool IsIntersect_SC(class SquareComponent* a, class CircleComponent* b) {
	RectF aRect = RectF{ Arg::center(a->GetCenter()),a->GetWidth(),a->GetHeight() };
	Circle bCircle = Circle{ b->GetCenter(),b->GetRadius() };
	if (aRect.intersects(bCircle))return true;
	else return false;
}

bool IsIntersect_SS(class SquareComponent* a, class SquareComponent* b) {
	RectF aRect = RectF{ Arg::center(a->GetCenter()),a->GetWidth(),a->GetHeight() };
	RectF bRect = RectF{ Arg::center(b->GetCenter()),a->GetWidth(),b->GetHeight() };
	if (aRect.intersects(bRect))return true;
	else return false;
}

