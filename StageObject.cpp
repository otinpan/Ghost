#include"StageObject.h"
#include"SquareComponent.h"
#include"CreateStage.h"
#include"Hand.h"

StageObject::StageObject()
	:sqc(nullptr)
	,mIsGripen(false)
{

}

StageObject::~StageObject() {

}

void StageObject::InitializeActor_CreateStage
(class CreateStage* createstage){
	Initialize_CreateStage(createstage);
	GetCreateStage()->AddStageObject(this);
	sqc = new SquareComponent(this);
}


void StageObject::UpdateActor_CreateStage(float deltaTime) {
	if (GetIsGripen()) {
		sqc->SetCenter(GetCreateStage()->GetHand()->GetPosition());
	}

}

void StageObject::ActorInput(std::vector<Input> keyState) {

}
