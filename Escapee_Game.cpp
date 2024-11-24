#include"Escapee_Game.h"
#include"Flashlight.h"

Escapee_Game::Escapee_Game(Vec2 pos, float speed, int num)
	:Player(pos, speed)
	, mFlashlight(nullptr)
{
	SetPosition(pos);
	SetSpeed(speed);
	switch (num) {
	case 1:
		SetAttribute(Attribute::Escapee1);
		break;
	case 2:
		SetAttribute(Attribute::Escapee2);
		break;
	case 3:
		SetAttribute(Attribute::Escapee3);
		break;
	
	}
}

Escapee_Game::~Escapee_Game() {

}

void Escapee_Game::InitializePlayer_Game(class Game* game) {
	InitializeActor_Game(game);
}

void Escapee_Game::UpdatePlayer_Game(float deltaTime) {

}
