#include"MoveComponent.h"
#include"Actor.h"

MoveComponent::MoveComponent(class Actor* owner, int updateOrder)
	:Component(owner, updateOrder)
	, mAngularSpeed(0.0f)
	, mXSpeed(0.0f)
	, mYSpeed(0.0f)
	,mForwardSpeed(0.0f)
{

}

void MoveComponent::Update(float deltaTime) {
	if (mAngularSpeed != 0.0f) {
		float rot = mOwner->GetRotation();
		rot += mAngularSpeed * deltaTime;
		mOwner->SetRotation(rot);
	}

	Vec2 pos=mOwner->GetPosition();
	/*if (Cursor::PosF() != Cursor::PreviousPosF()) {
		pos = ConvertToWorld(Cursor::PosF());
	}*/
	if (mXSpeed != 0.0f) {
		pos.x += mXSpeed * deltaTime;
	}
	if (mYSpeed != 0.0f) {
		pos.y += mYSpeed * deltaTime;
	}

	mOwner->SetPosition(pos);
}
