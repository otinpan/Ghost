#include"Wall.h"

Wall::Wall(Vec2 pos, float width, float height)
	:StageObject(pos, width, height)
{
	SetAttribute(Attribute::Wall);
}


Wall::~Wall() {

}

void Wall::InitializeStageObject_CreateStage(class CreateStage* createStage) {
	InitializeActor_CreateStage(createStage);
	GetSquareComponent()->SetDrawingState_CreateStage(DrawingComponent::DrawingState::UNAFFECTED,createStage);
}

void Wall::InitializeStageObject_Game(class Game* game) {
	InitializeActor_Game(game);
}
