#include"StageObject.h"
#include"SquareComponent.h"
#include"CircleComponent.h"
#include"CreateStage.h"
#include"Hand.h"

StageObject::StageObject(Vec2 pos, float width, float height)
	:sqc(nullptr)
	,mIsGripen(false)
	,mCenter(pos)
	,mWidth(width)
	,mHeight(height)
	,mIteration({-1,-1})
{
	SetPosition(pos);
}

StageObject::~StageObject() {
	if (GetCreateStage()) {
		GetCreateStage()->RemoveStageObject(this);
	}

	DeleteComponents();
}

void StageObject::InitializeActor_CreateStage(class CreateStage* createstage){
	Initialize_CreateStage(createstage);
	GetCreateStage()->AddStageObject(this);
	sqc = new SquareComponent(this);
	sqc->Initialize_CreateStage(mCenter,mWidth,mHeight);

	cc.resize(4);
	for (int i = 0; i < 4; i++) {
		cc[i] = new CircleComponent(this);
		cc[i]->Initialize_CreateStage();
		cc[i]->SetRadius((float)mWidth / 6.0f);
		cc[i]->SetColor(ColorF(0, 0, 1));
	}

	float dw = (float)mWidth / 2.0f - cc[0]->GetRadius();
	float dh = (float)mHeight / 2.0f - cc[0]->GetRadius()*mHeight/mWidth;
	dx = {-dw,dw,dw,-dw};
	dy = {dh,dh,-dh,-dh};

}


void StageObject::UpdateActor_CreateStage(float deltaTime) {
	if (GetIsGripen()) {
		SetPosition(GetCreateStage()->GetHand()->GetPosition());
	}
	
	sqc->SetCenter(GetPosition());
	for (int i = 0; i < 4; i++) {
		cc[i]->
			SetCenter(Vec2
			(GetPosition().x + dx[i],
			GetPosition().y + dy[i]));
	}
}

void StageObject::ActorInput(std::vector<Input> keyState) {

}


Vec2 StageObject::GetLeftTop() {
	return Vec2({ GetPosition().x - mWidth / 2.0f-0.001f,GetPosition().y + mHeight/2.0f+0.001f});
}

Vec2 StageObject::GetRightTop() {
	return Vec2({ GetPosition().x + mWidth / 2.0f+0.001f,GetPosition().y + mHeight / 2.0f+0.001f });
}

Vec2 StageObject::GetRightBottom() {
	return Vec2({ GetPosition().x + mWidth / 2.0f+0.001f,GetPosition().y - mHeight / 2.0f-0.001f });
}

Vec2 StageObject::GetLeftBottom() {
	return Vec2({ GetPosition().x - mWidth / 2.0f-0.001f,GetPosition().y - mHeight / 2.0f-0.001f });
}

Vec2 StageObject::GetExpandFulcrum(int i) {
	if (i == 0)return GetRightBottom();
	else if (i == 1)return GetLeftBottom();
	else if (i == 2)return GetLeftTop();
	else return GetRightTop();
}
