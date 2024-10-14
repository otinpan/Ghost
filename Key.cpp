#include"Key.h"

Key::Key(Vec2 pos, float width, float height)
	:StageObject(pos, width, height)
{
	SetAttribute(StageObject::Attribute::Key);
}

Key::~Key() {

}

void Key::InitializeStageObject_CreateStage(class CreateStage* createStage) {
	InitializeActor_CreateStage(createStage);
}

void Key::UpdateStageObject_CreateStage(float deltaTime) {

}
