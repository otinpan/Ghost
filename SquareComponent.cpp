#include"SquareComponent.h"
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

}

void SquareComponent::Initialize_Game() {
	mOwner->GetGame()->AddSquare(this);
}

void SquareComponent::Initialize_CreateStage() {
	mOwner->GetCreateStage()->AddSquare(this);
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
