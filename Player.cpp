#include"Player.h"
#include"Stage.h"
#include"InputComponent_JoyCon.h"
#include"InputComponent_Keyboard.h"
#include"SpriteComponent.h"
#define _USE_MATH_DEFINES
#include<math.h>

Player::Player(Vec2 pos, float speed,Controller::ControllerType controller)
	:cc(nullptr)
	, mObjectLeft(0)
	, mObjectRight(0)
	, mObjectDown(0)
	, mObjectUp(0)
	, mSpeedMagnification(speed)
	,StandardSpeed(0.3f)
	,mIsAlive(true)
	,mIsLighted(false)
	,mGhostColor(ColorF(76.0f / 255.0f, 0, 204.0f / 255.0f))
	,mEscapee1Color(ColorF(204.0f / 255.0f, 0, 204.0f / 255.0f))
	,mEscapee2Color(ColorF(102.0f / 255.0f, 178.0f / 255.0f, 1))
	,mEscapee3Color(ColorF(153.0f / 255.0f, 1.0f, 153.0f / 255.0f))
	, mControllerType(controller)
	, icKeyboard(nullptr)
	, icJoyCon(nullptr)
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

	sc = new SpriteComponent(this, 70, DrawingComponent::DrawingState::UNAFFECTED);
	sc->InitializeDrawing_Game(
		GetPosition(),
		game->GetStage()->GetRectWidth(),
		game->GetStage()->GetRectHeight()
	);
	switch (GetAttribute()) {
	case Attribute::Ghost:
		sc->SetTexture(TextureAsset(U"ghost"));
		sc->SetDrawingState_Game(DrawingComponent::DrawingState::UNAFFECTED, game);
		cc = new CircleComponent(this, 70, DrawingComponent::DrawingState::UNAFFECTED);
		cc->SetColor(mGhostColor);
		break;
	case Attribute::GhostClone:
		sc->SetIsDraw(false);
		sc->SetDrawingState_Game(DrawingComponent::DrawingState::BACK,game);
		cc = new CircleComponent(this, 70, DrawingComponent::DrawingState::BACK);
		cc->SetColor(mGhostColor);
		break;
	case Attribute::Escapee1:
		sc->SetTexture(TextureAsset(U"escapee1"));
		sc->SetDrawingState_Game(DrawingComponent::DrawingState::BACK, game);
		cc = new CircleComponent(this, 70, DrawingComponent::DrawingState::BACK);
		cc->SetColor(mEscapee1Color);
		break;
	case Attribute::Escapee2:
		sc->SetTexture(TextureAsset(U"escapee2"));
		sc->SetDrawingState_Game(DrawingComponent::DrawingState::BACK, game);
		cc = new CircleComponent(this, 70, DrawingComponent::DrawingState::BACK);
		cc->SetColor(mEscapee2Color);
		break;
	case Attribute::Escapee3:
		sc->SetTexture(TextureAsset(U"escapee3"));
		sc->SetDrawingState_Game(DrawingComponent::DrawingState::BACK, game);
		cc = new CircleComponent(this, 70, DrawingComponent::DrawingState::BACK);
		cc->SetColor(mEscapee3Color);
		break;
	}

	cc->InitializeDrawing_Game();
	cc->SetCenter(GetPosition());
	mRadius = GetGame()->GetStage()->GetRectWidth() * 2.0f / 5.0f;
	cc->SetRadius(mRadius);
	cc->SetIsDraw(false);

	// controller
	if (mControllerType == Controller::ControllerType::KEYBOARD) {
		icKeyboard = new InputComponent_Keyboard(this);
		icKeyboard->Initialize();
		icKeyboard->SetMaxXSpeed(GetSpeed());
		icKeyboard->SetMaxYSpeed(GetSpeed());
		icKeyboard->SetMaxSpeed(GetSpeed());
	}
	else if (mControllerType == Controller::ControllerType::NONE) {

	}
	else {
		icJoyCon = new InputComponent_JoyCon(this, mControllerType);
		icJoyCon->Initialize();
		icJoyCon->SetMaxXSpeed(GetSpeed());
		icJoyCon->SetMaxYSpeed(GetSpeed());
		icJoyCon->SetMaxSpeed(GetSpeed());
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

	float offset = 0.008f;
	//端
	if (mPos.x + mRadius > GetGame()->GetStage()->GetRight())
		mPos.x = GetGame()->GetStage()->GetRight() - mRadius - offset;
	if (mPos.x - mRadius < GetGame()->GetStage()->GetLeft())
		mPos.x = GetGame()->GetStage()->GetLeft() + mRadius + offset;
	if (mPos.y + mRadius * 3.0f > GetGame()->GetStage()->GetUp())
		mPos.y = GetGame()->GetStage()->GetUp() - mRadius * 3.0f - offset;
	if (mPos.y - mRadius * 3.0f < GetGame()->GetStage()->GetDown())
		mPos.y = GetGame()->GetStage()->GetDown() + mRadius * 3.0f + offset;

	SetPosition(mPos);
	cc->SetCenter(mPos);
	sc->SetCenter(mPos);
	// 元の画像に合わせる
	sc->SetRotation(-M_PI/2.0f+GetRotation());
}



void Player::UpdatePlayerPos_Game(float deltaTime) {

}


void Player::SetIsAlive_Game(bool isAlive,Game* game) {
	if (isAlive) {
		mIsAlive = true;
		GetCircleComponent()->SetDrawingState_Game(DrawingComponent::DrawingState::BACK,game);
		GetCircleComponent()->SetColor(GetCircleColor());
	}
	else {
		mIsAlive = false;
		GetCircleComponent()->SetDrawingState_Game(DrawingComponent::DrawingState::UNAFFECTED,game);
		GetCircleComponent()->SetColor(ColorF(0.5f));
	}
}

ColorF Player::GetCircleColor() {
	switch (mAttribute) {
	case Ghost:
		return mGhostColor;
		break;
	case Escapee1:
		return mEscapee1Color;
		break;
	case Escapee2:
		return mEscapee2Color;
		break;
	case Escapee3:
		return mEscapee3Color;
		break;
	default:
		return ColorF(1.0f);
		break;
	}
}
