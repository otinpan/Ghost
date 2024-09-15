#include "CircleComponent.h"
#include "Actor.h"
#include "Game.h"

CircleComponent::CircleComponent(class Actor* owner)
	:Component(owner)
	, mRadius(0.0f)
	, mCenter(owner->GetPosition())
{
	mOwner->GetGame()->AddCircle(this);
}

CircleComponent::~CircleComponent() {
	mOwner->GetGame()->RemoveCircle(this);
}



float CircleComponent::GetRadius()const {
	return mOwner->GetScale() * mRadius;
}

const Vec2& CircleComponent::GetCenter()const {
	return mCenter;
}




bool Intersect(const CircleComponent& a, const CircleComponent& b) {
	Circle aCircle = Circle{ a.GetCenter(), a.GetRadius() };
	Circle bCircle = Circle{ b.GetCenter(),b.GetRadius() };
	if (aCircle.intersects(bCircle))return true;
	else return false;
}


void CircleComponent::Draw() {
	float mg = GetMagnification();
	Circle{ ConvertToView(mCenter),mRadius * mg }.draw(mColor);
}
