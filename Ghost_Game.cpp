#include"Ghost_Game.h"

Ghost_Game::Ghost_Game(Vec2 pos,float speed)
	:Player(pos,speed)
{
	SetPosition(pos);
	SetSpeed(speed);
	SetAttribute(Player::Attribute::Ghost);
}

Ghost_Game::~Ghost_Game() {

}


void Ghost_Game::InitializePlayer_Game(class Game* game) {
	InitializeActor_Game(game);
}


void Ghost_Game::UpdatePlayer_Game(float deltaTime) {

}
