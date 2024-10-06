#include"StageObject.h"
#include"SquareComponent.h"
#include"CircleComponent.h"
#include"CreateStage.h"
#include"Hand.h"

StageObject::StageObject(Vec2 pos, float width, float height)
	:sqc(nullptr)
	, LeftTopCC(nullptr)
	, RightBottomCC(nullptr)
	,mIsGripen(false)
	,mCenter(pos)
	,mWidth(width)
	,mHeight(height)
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

	LeftTopCC = new CircleComponent(this);
	LeftTopCC->Initialize_CreateStage();
	LeftTopCC->SetRadius((float)mWidth / 3.5);

	RightBottomCC = new CircleComponent(this);
	RightBottomCC->Initialize_CreateStage();
	RightBottomCC->SetRadius((float)mWidth / 3.5);

}


void StageObject::UpdateActor_CreateStage(float deltaTime) {
	if (GetIsGripen()) {
		SetPosition(GetCreateStage()->GetHand()->GetPosition());
	}
	
	sqc->SetCenter(GetPosition());
	LeftTopCC->SetCenter
	(Vec2(GetPosition().x - mWidth / 3, GetPosition().y + mHeight / 3));
	RightBottomCC->SetCenter
	(Vec2(GetPosition().x + mWidth / 3, GetPosition().y - mHeight / 3));
}

void StageObject::ActorInput(std::vector<Input> keyState) {

}
