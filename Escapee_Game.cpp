#include"Escapee_Game.h"

Escapee_Game::Escapee_Game(Vec2 pos,float speed)
{
	SetPosition(pos);
	SetSpeed(speed);
}

Escapee_Game::~Escapee_Game() {

}

void Escapee_Game::InitializeActor_Game(class Game* game) {
	Initialize_Game(game);
}

void Escapee_Game::UpdateActor_Game(float deltaTime) {

}
