#include"StageObjectLight.h"
#include"TriangleComponent.h"

StageObjectLight::StageObjectLight(class StageObject* owner)
	:mOwner(owner)
	, Pi(3.141592)
{
	if (owner->GetClockwise() == 0 || owner->GetClockwise() == 2) {
		mHandRange = owner->GetHeight() / 2.0f;
	}
	else {
		mHandRange = owner->GetHeight() / 2.0f;
	}
	mLightRange = mHandRange * 2.0f;
	mLightRad = (float)30.0f / 180.0f * Pi;
}

StageObjectLight::~StageObjectLight() {

}

void StageObjectLight::Initialize_Game() {
	mLightTri = new TriangleComponent(mOwner,200, DrawingComponent::DrawingState::FRONT);
	SetLightPos0();
	SetLightPos1();
	SetLightPos2();
	mLightTri->InitializeDrawing_Game(mPos0, mPos1, mPos2);
	mLightTri->SetColor0(ColorF(1, 1, 1));
	mLightTri->SetColor1(ColorF(245.0f / 255.0f, 1, 87.0f / 255.0f));
	mLightTri->SetColor2(ColorF(245.0f / 255.0f, 1, 87.0f / 255.0f));
	mLightTri->SetIsDraw(true);
}

void StageObjectLight::Initialize_CreateStage() {

}

void StageObjectLight::Update_Game(float deltaTime) {
	SetLightPos0();
	SetLightPos1();
	SetLightPos2();
	mLightTri->SetPos0(mPos0);
	mLightTri->SetPos1(mPos1);
	mLightTri->SetPos2(mPos2);
}



void StageObjectLight::SetLightPos0() {
	mPos0 = Vec2(mOwner->GetPosition().x + mHandRange * cos(mOwner->GetRotation()),
		mOwner->GetPosition().y + mHandRange * sin(mOwner->GetRotation()));
}
void StageObjectLight::SetLightPos1() {
	mPos1 = Vec2(mPos0.x + mLightRange * cos(mOwner->GetRotation() + mLightRad),
	    mPos0.y + mLightRange * sin(mOwner->GetRotation() + mLightRad));
}
void StageObjectLight::SetLightPos2() {
	mPos2 = Vec2(mPos0.x + mLightRange * cos(mOwner->GetRotation() - mLightRad),
		mPos0.y + mLightRange * sin(mOwner->GetRotation() - mLightRad));
}
