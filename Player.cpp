#include"Player.h"
#include"Stage.h"

Player::Player(Vec2 pos, float speed)
	:cc(nullptr)
	, mObjectLeft(0)
	, mObjectRight(0)
	, mObjectDown(0)
	, mObjectUp(0)
	, mSpeedMagnification(speed)
	,StandardSpeed(0.3f)
{
	SetPosition(pos);
}

Player::~Player() {
	if (GetGame()) {
		GetGame()->RemovePlayer(this);
	}
	if (GetCreateStage()) {
		
	}
}

void Player::InitializeActor_Game(class Game* game) {
	Initialize_Game(game);
	GetGame()->AddPlayer(this);
	cc = new CircleComponent(this,170,false);
	cc->InitializeDrawing_Game();
	cc->SetCenter(GetPosition());
	mRadius = GetGame()->GetStage()->GetRectWidth() * 2.0f / 5.0f;
	cc->SetRadius(mRadius);
	switch (GetAttribute()) {
	case Attribute::Ghost:
		cc->SetColor(ColorF(76.0f / 255.0f, 0, 204.0f / 255.0f));
		break;
	case Attribute::GhostClone:
		cc->SetColor(ColorF(43.0f / 255.0f, 0, 110.0f / 255.0f));
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

	mVerticalSize = GetGame()->GetStage()->GetVerticalSize();
	mSideSize = GetGame()->GetStage()->GetSideSize();
}

void Player::InitializePlayer_Game(class Game* game) {
	InitializeActor_Game(game);
}

void Player::UpdateActor_Game(float deltaTime) {
	UpdatePlayer_Game(deltaTime);
}

void Player::UpdatePlayer_Game(float deltaTime) {
}

void Player::UpdatePos_Game(float deltaTime) {
	UpdatePlayerPos_Game(deltaTime);
	mPos = GetPosition();

	//端
	if (mPos.x + mRadius > GetGame()->GetStage()->GetRight())
		mPos.x = GetGame()->GetStage()->GetRight() - mRadius - 0.008;
	if (mPos.x - mRadius < GetGame()->GetStage()->GetLeft())
		mPos.x = GetGame()->GetStage()->GetLeft() + mRadius + 0.008;
	if (mPos.y + mRadius > GetGame()->GetStage()->GetUp())
		mPos.y = GetGame()->GetStage()->GetUp() - mRadius - 0.008;
	if (mPos.y - mRadius < GetGame()->GetStage()->GetDown())
		mPos.y = GetGame()->GetStage()->GetDown() + mRadius + 0.008;

	SetPosition(mPos);
	cc->SetCenter(mPos);
}

void Player::UpdatePlayerPos_Game(float deltaTime) {

}

