#include"StageObject.h"
#include"SquareComponent.h"
#include"CircleComponent.h"
#include"CreateStage.h"
#include"Hand.h"
#include"Stage.h"
#include"math.h"

StageObject::StageObject(Vec2 pos, float width, float height)
	:sqc(nullptr)
	, mIsGripen(false)
	, mCenter(pos)
	, mWidth(width)
	, mHeight(height)
	, mIteration({ -1,-1 })
	, mAttribute(Attribute::None)
	, mClockwise(0)
	, mPatrolRange(1)
{
	SetPosition(pos);
}

StageObject::~StageObject() {
	if (GetCreateStage()) {
		GetCreateStage()->RemoveStageObject(this);
		if (mIsInStage) {
			GetCreateStage()->GetStage()->SetStageObject(GetIteration().first, GetIteration().second,0);
		}
	}

	DeleteComponents();
}

void StageObject::InitializeActor_CreateStage(class CreateStage* createstage){
	Initialize_CreateStage(createstage);
	GetCreateStage()->AddStageObject(this);
	sqc = new SquareComponent(this);
	sqc->Initialize_CreateStage(mCenter,mWidth,mHeight);
	switch (mAttribute) {
	case Attribute::Wall:
		sqc->SetColor(ColorF(0, 0, 0));
		break;
	case Attribute::Brock:
		sqc->SetColor(ColorF(0, 0, 0));
		break;
	case Attribute::Door:
		sqc->SetColor(ColorF(0, 0, 0));
		break;
	case Attribute::Patrol:
		sqc->SetColor(ColorF(0, (float)102/255, 0));
		break;
	case Attribute::Key:
		sqc->SetColor(ColorF((float)204, (float)204 / 255, 0));
		break;
	case Attribute::Battery:
		sqc->SetColor(ColorF(0, 1, 0));
		break;
	}

	cc.resize(4);
	for (int i = 0; i < 4; i++) {
		cc[i] = new CircleComponent(this);
		cc[i]->Initialize_CreateStage();
		cc[i]->SetRadius((float)mWidth / 6.0f);
		cc[i]->SetColor(ColorF(0, 0, 1));
	}

	float dw = (float)mWidth / 2.0f - cc[0]->GetRadius();
	float dh = (float)mHeight / 2.0f - cc[0]->GetRadius() * mHeight / mWidth;
	dx = { -dw,dw,dw,-dw };
	dy = { dh,dh,-dh,-dh };
}

void StageObject::InitializeStageObject_CreateStage(class CreateStage* createstage) {

}


void StageObject::UpdateActor_CreateStage(float deltaTime) {
	if (GetIsGripen()) {
		SetPosition(GetCreateStage()->GetHand()->GetPosition());
	}

	UpdateStageObject_CreateStage(deltaTime);
	
	sqc->SetCenter(GetPosition());
	for (int i = 0; i < 4; i++) {
		cc[i]->
			SetCenter(Vec2
			(GetPosition().x + dx[i],
				GetPosition().y + dy[i]));
	}
}

void StageObject::UpdateStageObject_CreateStage(float deltaTime) {

}


void StageObject::ActorInput(std::vector<Input> keyState) {

}


void StageObject::RotateClockwise(bool isClockwise) {
	if (isClockwise) {
		mClockwise++;
	}
	else {
		mClockwise--;
	}

	if (mClockwise < 0)mClockwise += 4;
	mClockwise %= 4;
	AdjustPatrolRange();
}

void StageObject::AddPatrolRange(bool isPlus) {
	if (isPlus)mPatrolRange++;
	else mPatrolRange--;
	mPatrolRange = std::max(1, mPatrolRange);
	AdjustPatrolRange();
}

void StageObject::AdjustPatrolRange() {
	switch (mClockwise) {
	case 0:
		mPatrolRange = std::min(mPatrolRange,mIteration.first);
		break;
	case 1:
		mPatrolRange = std::min(mPatrolRange,
			GetCreateStage()->GetStage()->GetSideSize()- mIteration.second);
		break;
	case 2:
		mPatrolRange = std::min(mPatrolRange,
			GetCreateStage()->GetStage()->GetVerticalSize() - mIteration.first+1);
		break;
	case 3:
		mPatrolRange = std::min(mPatrolRange, mIteration.second+1);
		break;
	}
}



Vec2 StageObject::GetLeftTop() {
	return Vec2({ GetPosition().x - mWidth / 2.0f - 0.001f,GetPosition().y + mHeight / 2.0f + 0.001f });
}

Vec2 StageObject::GetRightTop() {
	return Vec2({ GetPosition().x + mWidth / 2.0f + 0.001f,GetPosition().y + mHeight / 2.0f + 0.001f });
}

Vec2 StageObject::GetRightBottom() {
	return Vec2({ GetPosition().x + mWidth / 2.0f + 0.001f,GetPosition().y - mHeight / 2.0f - 0.001f });
}

Vec2 StageObject::GetLeftBottom() {
	return Vec2({ GetPosition().x - mWidth / 2.0f - 0.001f,GetPosition().y - mHeight / 2.0f - 0.001f });
}

Vec2 StageObject::GetExpandFulcrum(int i) {
	if (i == 0)return GetRightBottom();
	else if (i == 1)return GetLeftBottom();
	else if (i == 2)return GetLeftTop();
	else return GetRightTop();
}
