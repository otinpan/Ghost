#include"Ghost_Game.h"

Ghost_Game::Ghost_Game(Vec2 pos,float speed)
{
	SetPosition(pos);
	SetSpeed(speed);
}

Ghost_Game::~Ghost_Game() {

}


void Ghost_Game::InitializeActor_Game(class Game* game) {
	Initialize_Game(game);
}


void Ghost_Game::UpdateActor_Game(float deltaTime) {

}
