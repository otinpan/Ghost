#include"GhostClone_Game.h"
#include"InputComponent_Keyboard.h"

GhostClone_Game::GhostClone_Game(Vec2 pos, float speed)
	:Player(pos, speed)
	, ic(nullptr)
	, StandardSpeed(0.3f)
{
	SetAttribute(Player::Attribute::GhostClone);
	SetPosition(pos);
	SetSpeed(StandardSpeed+speed/100.0f*StandardSpeed);
}

GhostClone_Game::~GhostClone_Game() {

}

void GhostClone_Game::InitializePlayer_Game(class Game* game) {
	InitializeActor_Game(game);

	inputUp = KeyUp;
	inputDown = KeyDown;
	inputRight = KeyRight;
	inputLeft = KeyLeft;

	ic = new InputComponent_Keyboard(this);
	ic->SetUpKey(inputUp);
	ic->SetDownKey(inputDown);
	ic->SetRightKey(inputRight);
	ic->SetLeftKey(inputLeft);
	ic->SetMaxXSpeed(GetSpeed());
	ic->SetMaxYSpeed(GetSpeed());
}

void GhostClone_Game::UpdatePlayer_Game(float deltaTime) {
	UpdatePos_Game(deltaTime);
}
