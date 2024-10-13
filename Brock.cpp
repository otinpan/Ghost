#include"Brock.h"

Brock::Brock(Vec2 pos,float width, float height)
	:StageObject(pos,width,height)
{
	SetAttribute(Attribute::Brock);
}

void Brock::InitializeStageObject_CreateStage(class CreateStage* createStage) {
	InitializeActor_CreateStage(createStage);
}

void Brock::UpdateStageObject_CreateStage(float deltaTime) {
}

Brock::~Brock() {
	
}




