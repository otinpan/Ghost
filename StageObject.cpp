#include"StageObject.h"
#include"SquareComponent.h"
#include"CreateStage.h"
#include"Hand.h"

StageObject::StageObject(Vec2 pos,float width,float height)
	:sqc(nullptr)
	,mIsGripen(false)
	,mCenter(pos)
	,mWidth(width)
	,mHeight(height)
{

}

StageObject::~StageObject() {

}

void StageObject::InitializeActor_CreateStage(class CreateStage* createstage){
	Initialize_CreateStage(createstage);
	GetCreateStage()->AddStageObject(this);
	sqc = new SquareComponent(this);
	sqc->Initialize_CreateStage(mCenter,mWidth,mHeight);
}


void StageObject::UpdateActor_CreateStage(float deltaTime) {
	if (GetIsGripen()) {
		SetPosition(GetCreateStage()->GetHand()->GetPosition());
	}
	
	sqc->SetCenter(GetPosition());
}

void StageObject::ActorInput(std::vector<Input> keyState) {

}
