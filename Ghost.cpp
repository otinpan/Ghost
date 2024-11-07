#include"Ghost.h"
#include"CreateStage.h"
#include"Hand.h"

Ghost::Ghost(Vec2 pos)
	:Player(pos)
{

}

Ghost::~Ghost() {

}

void Ghost::InitializePlayer_CreateStage(CreateStage* createStage) {
	InitializeActor_CreateStage(createStage);
}

void Ghost::UpdatePlayer_CreateStage(float deltaTime) {

}
