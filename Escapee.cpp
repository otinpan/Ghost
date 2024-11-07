#include"Escapee.h"
#include"Player.h"
#include"Hand.h"
#include"CreateStage.h"

Escapee::Escapee(Vec2 pos)
	:Player(pos) {

}

Escapee::~Escapee() {

}

void Escapee::InitializePlayer_CreateStage(CreateStage* createStage) {
	InitializeActor_CreateStage(createStage);
}

void Escapee::UpdatePlayer_CreateStage(float deltaTime) {

}

