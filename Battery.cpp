#include"Battery.h"

Battery::Battery(Vec2 pos, float width, float height)
	:StageObject(pos, width, height)
{
	SetAttribute(StageObject::Attribute::Battery);
}

Battery::~Battery() {

}

void Battery::InitializeStageObject_CreateStage(class CreateStage* createStage) {
	InitializeActor_CreateStage(createStage);
}

void Battery::UpdateStageObject_CreateStage(float deltaTime) {

}
