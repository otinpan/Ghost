#include"StageObject.h"
#include"SquareComponent.h"

StageObject::StageObject()
	:sqc(nullptr)
{

}

StageObject::~StageObject() {

}

void StageObject::InitializeActor_CreateStage
(class CreateStage* createstage){
	Initialize_CreateStage(createstage);

	sqc = new SquareComponent(this);
	sqc->Initialize_CreateStage();
	sqc->SetHeight(0.1f);
	sqc->SetWidth(0.1f);
	sqc->SetCenter(Vec2{ -0.8,-0.8 });
	sqc->SetColor(ColorF({ 0,0,0 }));
}


void StageObject::UpdateActor_CreateStage(float deltaTime) {

}

void StageObject::ActorInput(std::vector<Input> keyState) {

}
