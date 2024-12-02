#include"Ghost_Game.h"
#include"InputComponent_Keyboard.h"

Ghost_Game::Ghost_Game(Vec2 pos,float speed)
	:Player(pos,speed)
	,ic(nullptr)
	,StandardSpeed(0.3f)
{
	SetPosition(pos);
	SetSpeed(speed);
	SetAttribute(Player::Attribute::Ghost);
}

Ghost_Game::~Ghost_Game() {

}


void Ghost_Game::InitializePlayer_Game(class Game* game) {
	InitializeActor_Game(game);

	inputUp = KeyW;
	inputDown = KeyS;
	inputLeft = KeyA;
	inputRight = KeyD;

	ic = new InputComponent_Keyboard(this);
	ic->SetUpKey(inputUp);
	ic->SetDownKey(inputDown);
	ic->SetRightKey(inputRight);
	ic->SetLeftKey(inputLeft);
	ic->SetMaxXSpeed(StandardSpeed);
	ic->SetMaxYSpeed(StandardSpeed);
}


void Ghost_Game::UpdatePlayer_Game(float deltaTime) {
	UpdatePos_Game(deltaTime);
}
