#include"TreasureChest.h"

TreasureChest::TreasureChest(Vec2 pos, float width, float height)
	:StageObject(pos,width,height)
{
	SetAttribute(Attribute::TreasureChest);
}

TreasureChest::~TreasureChest() {

}

void TreasureChest::InitializeStageObject_CreateStage(class CreateStage* createStage) {
	InitializeActor_CreateStage(createStage);
}

void TreasureChest::UpdateStageObject_CreateStage(float deltaTime) {

}
