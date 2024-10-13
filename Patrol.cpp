#include"Patrol.h"

Patrol::Patrol(Vec2 pos, float width, float height)
	:StageObject(pos, width, height)
{
	SetAttribute(Attribute::Patrol);
}

void Patrol::InitializeStageObject_CreateStage(class CreateStage* createStage) {
	InitializeActor_CreateStage(createStage);
}

void Patrol::UpdateStageObject_CreateStage(float deltaTime) {
}

Patrol::~Patrol() {

}
