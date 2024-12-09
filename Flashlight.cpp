#include"Flashlight.h"
#include"TriangleComponent.h"

Flashlight::Flashlight(class Escapee_Game* owner)
	:mOwner(owner)
	,Pi(3.141592)
{
	mHandRange = owner->GetCircleComponent()->GetRadius();
	mLightRange = mHandRange * 2.0f;
	mLightRad = (float)25.0f / 180.0f / Pi;
}

Flashlight::~Flashlight() {

}



void Flashlight::Initialize_Game() {
	mLightTri = new TriangleComponent(mOwner);
	//mLightTri->Initialize_Game()
}


void Flashlight::Update_Game(float deltaTime) {

}


void Flashlight::SeekPos0() {
	mPos0= Vec2(mOwner->GetPosition().x + mHandRange *cos( mOwner->GetRotation()),
		mOwner->GetPosition().y + mHandRange * sin(mOwner->GetRotation()));
}
void Flashlight::SeekPos1() {
	mPos1=Vec2(mPos0.x + mLightRange * cos(mLightRad), mPos0.y + mLightRange * sin(mLightRad));
}
void Flashlight::SeekPos2() {
	mPos2 = Vec2(mPos0.x + mLightRange * cos(-mLightRad), mPos0.y + mLightRange * sin(-mLightRad));
}
