#include"Player.h"
#include"SquareComponent.h"
#include"CreateStage.h"
#include"Stage.h"
#include"StageMenu.h"
#include<Siv3D.hpp>

Player::Player(Vec2 pos)
	:mIsGripen(false)
{
	SetPosition(pos);
}

Player::~Player() {

}

void Player::InitializeActor_CreateStage(CreateStage* createStage) {
	Initialize_CreateStage(createStage);

}

void Player::InitializePlayer_CreateStage(CreateStage* createStage) {

}

void Player::UpdateActor_CreateStage(float deltaTime) {

}

void Player::UpdatePlayer_CreateStage(float deltaTime) {

}

void Player::ActorInput(std::vector<Input> keyStage) {

}
