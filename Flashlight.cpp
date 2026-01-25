#include"Flashlight.h"
#include"TriangleComponent.h"

Flashlight::Flashlight(class Escapee_Game* owner)
	:mOwner(owner)
	,Pi(3.141592)
{
	mHandRange = owner->GetCircleComponent()->GetRadius()*1.5f;
	mLightRad = (float)22.0f / 180.0f * Pi;
}

Flashlight::~Flashlight() {

}



void Flashlight::Initialize_Game() {
	mLightTri = new TriangleComponent(mOwner,200,DrawingComponent::DrawingState::FRONT);
	SetLightSize(LightSize::LightLarge);
	SetLightPos0();
	SetLightPos1();
	SetLightPos2();
	mLightTri->InitializeDrawing_Game(mPos0,mPos1,mPos2);
	mLightTri->SetColor1(ColorF(1, 1, float(220 / 255), 0.2));
	mLightTri->SetColor2(ColorF(1, 1, 1, 0.2));
}

void Flashlight::Initialize_CreateStage() {

}


void Flashlight::Update_Game(float deltaTime) {
	SetLightPos0();
	SetLightPos1();
	SetLightPos2();
	mLightTri->SetPos0(mPos0);
	mLightTri->SetPos1(mPos1);
	mLightTri->SetPos2(mPos2);
	mLightTri->SetIsDraw(mIsLightOn);

}


void Flashlight::SetLightPos0() {
	mPos0= Vec2(mOwner->GetPosition().x + mHandRange *cos( mOwner->GetRotation()),
		mOwner->GetPosition().y + mHandRange * sin(mOwner->GetRotation()));
}
void Flashlight::SetLightPos1() {
	mPos1=Vec2(mPos0.x + mLightRange * cos(mOwner->GetRotation()+mLightRad),
		mPos0.y + mLightRange * sin(mOwner->GetRotation()+mLightRad));
}
void Flashlight::SetLightPos2() {
	mPos2 = Vec2(mPos0.x + mLightRange * cos(mOwner->GetRotation() - mLightRad),
		mPos0.y + mLightRange * sin(mOwner->GetRotation() - mLightRad));
}


void Flashlight::SetLightSize(LightSize lightSize) {
	mLightSize = lightSize;
	switch (mLightSize) {
	case LightLarge:
		mLightRange = mHandRange * 4.0f;
		break;
	case LightMid:
		mLightRange = mHandRange * 3.0f;
		break;
	case LightSmall:
		mLightRange = mHandRange*2.0f;
		break;
	}

	return;
}
