#include"Player.h"
#include"Stage.h"

Player::Player(Vec2 pos, float speed)
	:cc(nullptr)
{
	SetPosition(pos);
	SetSpeed(speed);
}

Player::~Player() {

}

void Player::InitializeActor_Game(class Game* game) {
	Initialize_Game(game);
	cc = new CircleComponent(this);
	cc->Initialize_Game();
	cc->SetCenter(GetPosition());
	cc->SetRadius(GetGame()->GetStage()->GetRectWidth()/2.0f);
	switch (GetAttribute()) {
	case Attribute::Ghost:
		cc->SetColor(ColorF(76.0f / 255.0f, 0, 204.0f / 255.0f));
		break;
	case Attribute::Escapee1:
		cc->SetColor(ColorF(204.0f / 255.0f, 0, 204.0f / 255.0f));
		break;
	case Attribute::Escapee2:
		cc->SetColor(ColorF(102.0f / 255.0f, 178.0f / 255.0f, 1));
		break;
	case Attribute::Escapee3:
		cc->SetColor(ColorF(153.0f / 255.0f, 1.0f, 153.0f / 255.0f));
		break;
	}
}

void Player::InitializePlayer_Game(class Game* game) {
	InitializeActor_Game(game);
}

void Player::UpdateActor_Game(float deltaTime) {
	UpdatePlayer_Game(deltaTime);
}

void Player::UpdatePlayer_Game(float deltaTime) {

}

