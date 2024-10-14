#include"Door.h"

Door::Door(Vec2 pos, float width, float height)
	:StageObject(pos, width, height)
{

}

Door::~Door() {

}


void Door::InitializeStageObject_CreateStage(class CreateStage* createStage) {
	InitializeActor_CreateStage(createStage);
}

void Door::UpdateStageObject_CreateStage(float deltaTime) {

}
